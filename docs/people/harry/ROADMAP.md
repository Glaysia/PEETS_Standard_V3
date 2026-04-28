# 2주 Bring-Up 로드맵: 새 컨트롤보드 + EV 보드 교차 테스트

## Summary

목표는 2주 안에 제품 완성이 아니라, 새 PCB에서 CPU1/CPU2/CM, 주요 I/O, PWM, ADC, 보호 체인, 저전압 open-loop까지 전부 smoke/bench 검증하는 것이다. 부사수에게는 기능 하나당 “예제 출
처, 코드 변경, 실제 관측, 성공 조건”을 남기게 한다.

순서는 CPU1 기준선 -> CM -> CPU2 -> GPIO/통신 smoke -> PWM -> ADC -> CMPSS/TZ -> 저전압 open-loop로 고정한다. EtherCAT은 PHY가 없으므로 이번 2주 범위에서 제외한다.

## Key Changes

- CPU1은 시스템 마스터로 유지한다: boot, pinmux, safe GPIO, CPU2/CM release, fault latch.
- CPU2는 fast control 준비용으로 살린다: boot handshake, timer/ISR heartbeat, 이후 PWM/ADC update skeleton.
- CM은 먼저 UART smoke까지만 한다: CPU1 -> CM handshake 성공 뒤 UARTA TX/RX 확인.
- PWM은 제품 제어기 완성이 아니라 무전력 scope 검증을 목표로 한다: EPWM1~12, A/B 출력, deadtime, phase shift, trip safe-off.
- ADC/CMPSS/TZ는 저전압 실험 전에 반드시 닫는다: EPWM SOCA/SOCB -> ADCINT, CMPSS/DAC -> ePWM XBAR -> TZ/DC -> PWM safe state.
- 모든 실질 변경은 docs/specs/NNN-*에 요구사항, 설계, 작업, 검증 결과를 남긴다.

## 2주 작업 목록

### 기준선 고정

- 세 프로젝트 CPU1_RAM, CPU2_RAM, CM_RAM clean build 확인.
- 새 컨트롤보드와 EV 보드에서 CPU1 단독 debug/run 확인.
- CPU1 heartbeat GPIO, main loop 진입, watchdog/clock 기본 상태 기록.
- 현재 구현된 CPU1 -> CM MSGRAM handshake를 실제 보드에서 검증하고 docs/specs/001-cpu1-cm-handshake/verification.md를 PENDING에서 결과 기록 상태로 바꾼다.
- 실패 시 CM UART나 PWM으로 넘어가지 않는다.

### CM 최소 통신

- CPU1 -> CM handshake 성공 조건을 gate로 둔다.
- CM main() 진입, ACK token, timeout failure case를 각각 관측한다.
- CM UARTA GPIO84/85 기준으로 TX smoke를 먼저 한다.
- 이후 loopback 또는 PC serial RX/TX 왕복을 확인한다.
- 성공 조건: CPU1 heartbeat 유지, CM ACK 유지, UART 송수신 중 CPU1/CM hang 없음.

### CPU2 살리기

- CPU1에서 CPU2 release 경로를 추가한다.
- CPU1 <-> CPU2 MSGRAM token 왕복을 만든다.
- CPU2 main() 진입 flag, heartbeat 또는 timer tick counter를 debugger로 관측한다.
- CPU2에는 아직 PWM 제어권을 넘기지 않는다.
- 성공 조건: CPU1, CPU2, CM 세 코어가 동시에 debug attach 가능하고 각자 상태 변수가 살아 있다.

### GPIO와 보드 I/O smoke

- pinmux 문서와 실제 핀을 대조한다.
- Buffer OE GPIO42/43/46/50/100 safe default를 확인한다.
- Buffer DIR GPIO58/59/107/120 방향 기본값을 확인한다.
- INPUTXBAR1~8 GPIO60~67 입력 토글 또는 강제 상태 관측을 한다.
- SCIA, SCIB, MCAN, I2C는 “핀/클럭/기본 loopback 가능성”까지만 smoke한다.
- EtherCAT은 제외한다. Ethernet은 PHY가 실장되어 있고 장비가 있으면 link/reset smoke만 선택으로 한다.

### 무전력 PWM bring-up

- CPU1/include_editable/pwm.h, CPU1/source_editable/pwm.cpp의 현재 C++ smoke를 실제 ePWM driverlib 기반으로 교체하는 계획을 세운다.
- EPWM1~12 전체를 safe-off first로 초기화한다.
- TBCLKSYNC off -> profile apply -> trip/safe state -> TBCLKSYNC on 순서를 지킨다.
- Scope로 EPWM1~12 A/B가 핀에 나오는지 확인한다.
- 기본 케이스는 3개로 충분하다: independent, complementary + deadtime, master/slave phase shift.
- 성공 조건: 전력부 미인가 상태에서 주파수, duty, deadtime, phase shift가 재현된다.

### ADC trigger chain

- ePWM SOCA/SOCB를 ADC trigger source로 잡는다.
- ADCINT 기준 ISR cadence를 만든다.
- ADC raw result buffer를 CPU2 또는 CPU1에서 읽고 debugger로 확인한다.
- Scope marker 또는 GPIO toggle로 trigger 시점과 ISR 시점을 확인한다.
- 성공 조건: PWM 주기와 ADC sample cadence가 고정되고, ADC 값이 안정적으로 갱신된다.

### CMPSS/TZ 보호 체인

- CMPSS + DAC threshold를 구성한다.
- CMPSS output을 ePWM XBAR/TZ/DC로 연결한다.
- CBC와 one-shot을 각각 검증한다.

- current-limited 저전압 조건에서만 진행한다.
- power stage enable은 CPU1 supervisor가 담당한다.
- CPU2는 fixed phase shift 또는 duty update만 수행한다.
- startup, shutdown, fault injection, repeated restart를 반복한다.
- 성공 조건: 저전압 open-loop에서 PWM, ADC, fault latch, trip recovery가 동시에 동작한다.

### 교차 테스트와 정리

- 새 컨트롤보드와 EV 보드에서 같은 체크리스트를 반복한다.
- 보드별 차이, 실패 조건, pin mismatch, timing mismatch를 표로 남긴다.
- 실패한 항목은 “코드 문제 / 보드 문제 / 계측 문제 / 미실장 기능”으로 분류한다.
- 다음 2주 backlog를 만든다: 폐루프, Ethernet, EtherCAT PHY 이후 작업, 고전력 시험.

## Test Plan

- Build: 세 프로젝트 RAM build 성공.
- Debug: CPU1 단독, CPU1+CM, CPU1+CPU2+CM attach/run 확인.
- Memory: MSGRAM token 왕복, timeout latch, 상태 변수 관측.
- Scope: heartbeat, UART TX, EPWM A/B, deadtime, phase shift, ADC trigger marker, trip event.
- Bench: 무전력 PWM 전 채널 확인 후, current-limited 저전압 open-loop만 진행.
- Documentation: 각 기능별로 사용 예제, 검증 방법, 성공/실패 결과를 docs/specs/에 기록.

## Assumptions

- 2주 목표는 “모든 기능의 1차 smoke/bench 검증”이지 제품용 제어기 완성이 아니다.
- EtherCAT은 PHY 미실장으로 제외한다.
- 전력 테스트는 무전력 검증과 저전압 current-limited 조건까지만 한다.
- CM UART는 CPU1 -> CM handshake 성공 후에만 붙인다.
- PWM/ADC/CMPSS/TZ는 한 커밋에 섞지 않고 기능별로 나눈다.