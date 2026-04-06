# DAB Control Bring-Up Plan

기준 자료: `AGENTS.md`, `README.md`, `docs/board/board-io-reference.md`, `docs/board/pwm-architecture.md`, `CPU1/source_editable/main_cpu1.c`

## 목적

- 이 문서는 전력전자 연구실 관점에서 F28388D 워크스페이스를 DAB 중심 제어 플랫폼으로 bring-up 하기 위한 4주 계획서다.
- 목표는 4주 안에 `safe open-loop -> ADC 동기 샘플링 -> 하드웨어 보호 -> 단일 폐루프`까지 bench 검증을 끝내는 것이다.
- 이 문서는 범용 프레임워크 설계서가 아니라, 실제 하드웨어 시험을 기준으로 한 단계별 실행 계획서다.

## 현재 상태 요약

- 현재 보드 문서 기준으로 외부 제어 출력은 `EPWM1~12`가 열려 있다.
- `INPUTXBAR1~8`은 pinmux에 보인다.
- `main_cpu1.c`는 이미 초기화 호출 중심 구조로 정리할 수 있는 상태다.
- 반면 전력전자 bring-up에 핵심인 `ADC trigger chain`, `CMPSS -> ePWM XBAR -> TZ/DC 보호 체인`, `CPU1/CPU2 ownership`, `OUTPUTXBAR debug tap`은 아직 시스템 수준으로 구성되지 않았다.
- 주변장치 클럭은 넓게 켜져 있지만, 클럭이 켜져 있다는 사실과 실제로 검증 가능한 route가 열려 있다는 것은 다르다.

## 코어 역할 고정

- `CPU1`은 system master다.
- `CPU1`은 boot, safe GPIO, pinmux, power-stage enable sequence, CPU2 boot, fault latch, supervisor state machine만 맡는다.
- `CPU2`는 fast ISR control core로 고정한다.
- `CPU2`는 PWM update, ADC result latch, control law, phase-shift update를 맡는다.
- `CM`은 통신과 진단 후순위다.
- 4주 계획에서 `CM`은 필수 성공 조건이 아니다.

## 코드 구조 원칙

- `main_cpu1.c`에는 오케스트레이션용 함수 호출만 둔다.
- 세부 register 설정, profile table, plan object는 C++ 쪽에 둔다.
- `main_cpu1.c` 권장 흐름은 `PlatformInit() -> BoardSafeInit() -> PwmTriggerInit() -> ProtectionInit() -> Cpu2BootAndHandshake() -> CmBootOptional()`이다.
- fast loop와 hardware-facing spec은 `CPU2` 쪽 C++에 둔다.
- CPU1은 “대부분의 명세를 가진 제어 코어”가 아니라 “명시적 초기화와 supervisor 정책을 가진 시스템 코어”로 둔다.

## 전력전자 v1 필수 블록

| 블록 | 현재 상태 | 4주 내 우선순위 | 비고 |
| --- | --- | --- | --- |
| EPWM1~12 | 외부 출력 pinmux 확인 | 필수 | DAB phase-shift, complementary pair, deadtime |
| ADCA~ADCD | 클럭만 켜짐 | 필수 | SOCA/SOCB와 ADCINT cadence 구성 필요 |
| CMPSS1~8 | 클럭만 켜짐 | 필수 | 하드웨어 보호 핵심 |
| DACA~DACC | 클럭만 켜짐 | 필수 | CMPSS threshold에 사용 |
| ePWM XBAR / TZ / DC | route 미구성 | 필수 | CBC/OST 보호 경로 |
| INPUTXBAR1~8 | pinmux 확인 | 필수 | 외부 fault 또는 디지털 입력 수집 |
| CPU1 <-> CPU2 IPC | boot path만 있음 | 필수 | 상태 공유와 fault latch 연계 |
| OUTPUTXBAR | 미구성 | 권장 | debug 관측용 1~2채널 reserve |
| CLB | 클럭만 켜짐 | 선택 | v1 필수 아님 |
| FSI | 클럭만 켜짐, 현재 pinmux 기준 비활성 | 선택 | 외부 고속 동기 필요 시만 |
| ECAP/EQEP | 클럭만 켜짐 | 후순위 | DAB v1 필수 아님 |

## 트리거와 보호 계획

### 트리거는 별도 축으로 다룬다

- PWM은 단순 파형 발생기만이 아니라 시스템의 시간 기준이다.
- `ePWM SOCA/SOCB`는 ADC 샘플링 트리거로 사용한다.
- 제어 ISR cadence는 `ADCINT` 기준으로 고정한다.
- `ePWM INT`는 debug 또는 housekeeping으로만 남긴다.
- 보호 트리거는 `CMPSS + ePWM XBAR + TZ/DC`로 분리한다.

### 보호는 CPU보다 먼저 닫는다

- overcurrent나 abnormal comparator event는 CPU 개입 없이 power stage를 멈출 수 있어야 한다.
- 최소 경로는 `CMPSS + DAC threshold -> ePWM XBAR -> TZ/DC -> PWM safe state`다.
- CPU는 fault latch, 원인 기록, 재기동 정책만 맡는다.

### OUTPUTXBAR 평가

- `OUTPUTXBAR`는 필수는 아니다.
- DAB 1차 bring-up과 첫 폐루프는 `EPWM + ADC trigger + CMPSS/TZ`만으로 가능하다.
- 하지만 scope 관측 생산성은 크게 높여 준다.
- v1 권장 사용법은 debug 용도 1~2채널 reserve다.
- 추천 신호는 `CMPSS CTRIP`, `trip latched state`, `PWM sync pulse`다.
- 처음부터 제어 기능의 필수 의존성으로 두지는 않는다.

## 제어 목표 고정

- 첫 4주 목표는 `unidirectional output-voltage loop + hardware current limit`로 고정한다.
- bidirectional full control, power optimization, mode switching, advanced experimental features는 후순위다.
- 첫 폐루프에서 중요한 것은 “제어기의 화려함”이 아니라 “startup, shutdown, fault recovery가 안정적으로 반복되는지”다.

## 4주 실행 계획

### 1주차: 코어 역할과 무전력 PWM 기준선 고정

- CPU1/CPU2 ownership을 잠근다.
- CPU1은 safe GPIO, buffer OE/DIR safe default, peripheral init, CPU2 boot path를 먼저 완성한다.
- CPU2는 fast ISR skeleton만 만든다.
- DAB용 PWM bank는 처음부터 `complementary pair`, `deadtime`, `phase-shift`, `global load`, `TBCLKSYNC discipline`, `safe-off first`를 포함해 설계한다.
- 무전력 상태에서 scope로 `PWM pair`, `deadtime`, `phase shift`, `sync marker`를 검증한다.
- 1주차 성공 기준은 “전원이 없어도 timing structure가 재현 가능하다”다.

### 2주차: ADC 동기 샘플링과 보호 체인 고정

- `SOCA/SOCB` 위치를 deadtime과 switching edge를 고려해 정한다.
- 전압/전류 샘플을 같은 time base 위에서 읽는다.
- ISR cadence는 `ADCINT` 기준으로 고정한다.
- `CMPSS + DAC threshold -> ePWM XBAR -> TZ/DC` 보호 체인을 붙인다.
- CBC와 one-shot을 둘 다 bench에서 검증한다.
- 필요 시 `OUTPUTXBAR` 1~2채널로 comparator/trip을 scope에 뽑는다.
- 저전압, current-limited 환경에서 DAB open-loop phase shift sweep과 startup/shutdown을 확인한다.

### 3주차: 첫 폐루프와 supervisor 정책 정착

- 첫 폐루프는 `output-voltage loop` 하나만 넣는다.
- fast loop는 CPU2에서 phase shift를 갱신한다.
- CPU1은 soft-start, parameter apply, state machine, latched fault recovery만 맡는다.
- CM 통신은 최소 telemetry가 꼭 필요할 때만 붙인다.
- CM 문제로 fast loop가 멈추는 구조는 금지한다.
- 3주차 성공 기준은 “폐루프가 동작하고 fault recovery가 재현된다”다.

### 4주차: fault regression과 operating window 고정

- overcurrent, ADC saturation, sensor loss, startup abort, repeated restart, load step, thermal dwell을 확인한다.
- 이 주의 목표는 기능 추가가 아니라 안전한 operating map을 고정하는 것이다.
- core loop가 이미 안정적일 때만 advanced block 하나를 추가한다.
- 우선순위는 `OUTPUTXBAR debug 확장 > FSI > CLB`다.

## 시험 항목

### 무전력 bench

- PWM A/B 상보 동작
- deadtime
- phase shift
- sync/global load
- trigger timing marker

### 저전압 power stage

- fixed phase shift sweep
- startup
- shutdown
- current-limited source 조건의 안전성

### 보호

- CMPSS threshold hit 시 CPU 없이 safe state 전환
- CBC 동작
- one-shot 동작
- clear 후 재기동 정책

### 폐루프

- output-voltage setpoint step
- load step
- startup overshoot
- fault recovery

### 시스템

- `CPU1 boot -> CPU2 handshake -> fast ISR running -> optional CM telemetry`
- CM 실패가 power stage control을 막지 않는지 확인

## 구현 우선순위

1. CPU1 init/supervisor 구조 고정
2. CPU2 fast ISR skeleton
3. PWM bank와 phase-shift 구조
4. ADC trigger chain
5. CMPSS/TZ 보호 체인
6. 저전압 open-loop DAB
7. 단일 output-voltage loop
8. OUTPUTXBAR debug tap
9. CM telemetry 최소화

## 범위 밖

- bidirectional full control
- 다중 토폴로지 범용 프레임워크
- CLB 기반 고급 interlock
- FSI 기반 외부 보드 동기
- ECAP/EQEP 기반 부가 측정 기능

## 결론

- 현재 워크스페이스는 전력전자에 필요한 주변장치 클럭은 충분히 열려 있지만, 실제로 필요한 trigger/protection route는 아직 거의 비어 있다.
- 4주 안에 성공하려면 `CPU1 init/supervisor`, `CPU2 fast ISR`, `PWM + ADC trigger + CMPSS/TZ`를 먼저 닫아야 한다.
- `OUTPUTXBAR`는 필수는 아니지만, debug 관측용으로는 매우 가치가 크므로 최소 채널만 reserve하는 전략이 가장 현실적이다.
