# CPU1 source_editable/epwm_ctrl.cpp

## 소스 경로

- planned path: `CPU1/source_editable/epwm_ctrl.cpp`
- predecessor: `CPU1/source_editable/pwm.cpp`
- project: `CPU1`
- language: `C++`

## 단일 책임

- C2000 EPWM peripheral 제어 계층을 맡는다.
- EPWM channel/group, time-base, compare, phase, deadband, trip, sync, safe-off 적용을 담당한다.
- 제어 law, PLL, duty/period/phase command 계산은 `ctrl_loop.cpp`가 맡는다.
- board buffer OE/DIR policy는 `main_cpu1.c` 또는 후속 board I/O 파일이 맡는다.

## 실행 코어와 초기화 순서

- 현재 테스트 실행 코어: `CPU1`
- 호출 위치: `main_cpu1.c`의 EPWM bring-up 단계
- 권장 흐름: `Device_init() -> GPIO_setPinMuxConfig() -> board I/O safe default -> epwm_ctrl init -> safe-off -> control loop command`
- CPU2 runtime ownership 이관은 별도 spec 전까지 하지 않는다.

## 주요 입력과 출력

- 입력: EPWM channel config, duty/period/phase/deadband command, trip clear/force request
- 출력: EPWM register write, trip latch clear/force, debug status
- shared state: EPWM command/status는 `volatile` 또는 명시 동기화 정책을 둔다.
- 외부 관측값: EPWM1~12 A/B scope waveform, trip/safe-off 상태, debugger status 변수

## Hardware / Driverlib 의존성

- peripheral: EPWM1~12
- driverlib/API: `EPWM_*`, `SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC)`, `SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC)`
- CPUSEL / pinmux / SysConfig 의존성: CPU1 테스트 단계에서는 CPU1 ownership과 `CPU1/include_editable/pinmux.h` 기준을 따른다.
- clock source: `Device_init()` 이후 EPWM clock과 TBCLKSYNC 상태에 의존한다.

## Interrupt / Trigger / Timing

- 초기 smoke 단계 ISR: 없음
- 후속 runtime update: ISR에서 호출될 수 있는 path는 bounded 해야 한다.
- ADC trigger, CMPSS/TZ, XBAR 연계는 별도 spec에서 붙인다.
- group commit은 여러 EPWM의 update timing이 갈라지지 않도록 shadow/global load 정책을 둔다.

## 핵심 invariant

- safe-off first를 지킨다.
- constructor/destructor에서 hardware side effect를 만들지 않는다.
- `ctrl_loop.cpp`가 EPWM register를 직접 쓰지 않게 한다.
- EPWM register write, pinmux, ADC trigger, CMPSS/TZ를 한 변경에 처음부터 섞지 않는다.

## 관련 문서

- architecture:
  - [epwm-bringup-boundary](../../../architecture/epwm-bringup-boundary.md)
  - [multicore-ownership](../../../architecture/multicore-ownership.md)
- plan:
  - [epwm-control-source-split](../../../plans/epwm-control-source-split.md)
- code collaborators:
  - [CPU1 main_cpu1.c](main_cpu1.c.md)
  - [CPU1 ctrl_loop.cpp planned](ctrl_loop.cpp.md)

## 변경 시 주의점

- dynamic allocation, RTTI, exceptions, virtual function, global constructor side effect를 도입하지 않는다.
- runtime update API는 duty, period, phase를 독립적으로 갱신할 수 있게 하되 commit timing은 group 단위로 관리한다.
