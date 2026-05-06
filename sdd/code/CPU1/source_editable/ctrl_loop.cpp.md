# CPU1 source_editable/ctrl_loop.cpp

## 소스 경로

- planned path: `CPU1/source_editable/ctrl_loop.cpp`
- project: `CPU1`
- language: `C++`

## 단일 책임

- 테스트 단계의 제어 루프와 PWM command 생성을 맡는다.
- duty control, frequency/period control, phase control, PLL 기반 phase command 후보를 표현한다.
- EPWM register write는 하지 않고 `epwm_ctrl.cpp`의 commit API로 command를 넘긴다.

## 실행 코어와 초기화 순서

- 현재 테스트 실행 코어: `CPU1`
- 최종 후보 실행 코어: `CPU2`
- CPU1 단계에서는 debugger 변수 또는 고정 test profile 기반으로 command를 만든다.
- CPU2 이관은 CPU1/CPU2 handshake와 EPWM ownership 검증 후 별도 spec에서 수행한다.

## 주요 입력과 출력

- 입력: test 변수, ADC result 후보, PLL/reference phase 후보, enable 상태
- 출력: EPWM command: duty, period, phase, deadband, update mask
- shared state: ISR/background 공유가 생기면 `volatile`, critical section, ring buffer 중 명시 정책을 둔다.
- 외부 관측값: command debug 변수, EPWM waveform 변화, loop tick counter

## Hardware / Driverlib 의존성

- 직접 peripheral register write: 없음
- driverlib/API: 직접 의존하지 않는 것을 기본으로 한다.
- CPUSEL / pinmux 의존성: 없음. 실제 반영은 `epwm_ctrl.cpp`가 담당한다.

## Interrupt / Trigger / Timing

- 초기 CPU1 테스트: background loop 또는 debugger-triggered update
- 최종 CPU2 방향: ADC trigger 기반 fast ISR에서 bounded 계산
- ISR에서는 logging, printf, 긴 spin wait, dynamic allocation을 사용하지 않는다.

## 핵심 invariant

- 제어 law와 EPWM hardware write를 분리한다.
- command는 duty, period, phase를 동시에 표현할 수 있어야 한다.
- 여러 EPWM이 한 topology를 구성하면 group commit 타이밍을 `epwm_ctrl.cpp`에 위임한다.

## 관련 문서

- architecture:
  - [epwm-bringup-boundary](../../../architecture/epwm-bringup-boundary.md)
  - [multicore-ownership](../../../architecture/multicore-ownership.md)
- plan:
  - [epwm-control-source-split](../../../plans/epwm-control-source-split.md)
- code collaborators:
  - [CPU1 epwm_ctrl.cpp planned](epwm_ctrl.cpp.md)

## 변경 시 주의점

- `ctrl_loop.cpp`에 EPWM register write를 넣지 않는다.
- topology별 helper는 필요해질 때 분리한다. 예: three-phase, phase-shift bridge, interleaved converter.
- CPU2 이관 전까지 CPU1 테스트 경로와 CPU2 최종 경로를 한 변경에 섞지 않는다.
