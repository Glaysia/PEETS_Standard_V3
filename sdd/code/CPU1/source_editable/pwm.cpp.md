# CPU1 source_editable/pwm.cpp

## 소스 경로

- path: `CPU1/source_editable/pwm.cpp`
- planned rename: `CPU1/source_editable/epwm_ctrl.cpp`
- project: `CPU1`
- language: `C++`
- status: 현재 실제 소스가 남아 있으므로 이 note는 유지한다. 소스 rename이 끝나면 이 note를 제거하거나 `epwm_ctrl.cpp.md`로 통합한다.

## 단일 책임

- 현재 CPU1 테스트 단계의 EPWM1~12 scope smoke 구현을 맡는다.
- `pwm_smoke_init()`, `pwm_smoke_force_safe_off()`, `pwm_smoke_release_outputs()` C ABI를 제공한다.
- EPWM time-base, compare, action qualifier, deadband, phase, one-shot trip safe-off를 driverlib로 설정한다.
- 다음 정리 단계에서 이 책임은 `epwm_ctrl.cpp`로 이동한다.
- 제어 law, PLL, duty/period/phase command 계산은 `ctrl_loop.cpp` 후보 파일로 분리한다.

## 실행 코어와 초기화 순서

- 실행 코어: `CPU1`
- 호출 위치: `CPU1/source_editable/main_cpu1.c`
- 현재 흐름: `Device_init() -> GPIO_setPinMuxConfig() -> board I/O safe default -> pwm_smoke_init() -> pwm_smoke_force_safe_off() -> intercore handshake -> heartbeat loop`
- 선행 조건: CPU1 C/C++ mixed build, EPWM driverlib symbol, pinmux apply, board I/O safe default가 정상이어야 한다.
- 후행 조건: EPWM1~12가 safe-off 상태로 초기화되고, debugger enable request 전에는 출력이 활성화되지 않아야 한다.

## 주요 입력과 출력

- 입력: smoke fixed profile, debugger-controlled board output enable 경로
- 출력: EPWM register 설정, one-shot trip force/clear
- shared state: 직접 소유 shared state는 없음. `main_cpu1.c`의 `g_epwm_smoke_initialized`, `g_board_io_enable_request`, `g_board_io_outputs_enabled`와 동작 계약을 가진다.
- 외부 관측값: EPWM1~12 A/B scope waveform, trip safe-off 상태, CPU1 heartbeat 유지

## Hardware / Driverlib 의존성

- peripheral: EPWM1~12
- driverlib/API: `EPWM_*`, `SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC)`, `SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC)`
- CPUSEL / pinmux / SysConfig 의존성: CPU1 테스트 단계에서는 CPU1 ownership과 `CPU1/include_editable/pinmux.h` 결과를 따른다.
- clock source: `Device_init()` 이후 EPWM clock과 TBCLKSYNC 제어에 의존한다.

## Memory / Startup / Linker 의존성

- section: 기본 code/data section
- linker command file: CPU1 linker command file의 C++ runtime 지원에 의존
- startup/vector 의존성: 없음
- IPC MSGRAM 의존성: 없음

## Interrupt / Trigger / Timing

- ISR: 없음
- trigger source: CPU1 init path와 debugger-controlled enable path
- bounded 조건: EPWM1~12 fixed loop register write
- background와 공유하는 데이터: 현재 없음
- 동기화 방식: 초기 smoke 단계에서는 명시 동기화 없음

## 핵심 invariant

- safe-off first를 지킨다.
- C ABI 함수는 rename 전까지 유지한다.
- C28x C++03 정책을 따른다.
- 생성자/소멸자에서 hardware side effect를 만들지 않는다.
- `ctrl_loop.cpp`가 생기면 EPWM register write를 그쪽에 넣지 않는다.

## Fail-fast / 실패 처리

- 실패 조건: C/C++ mixed build 실패, EPWM driverlib symbol/link 실패, scope 파형 불일치, safe-off 불응
- 시스템 동작: board output enable을 진행하지 않고 원인 분리
- 후속 기능 차단 조건: EPWM safe-off와 enable이 확인되기 전에는 ADC trigger, CMPSS/TZ, power-stage 실험으로 넘어가지 않는다.
- debug 관측 방법: `g_epwm_smoke_initialized`, `g_board_io_enable_request`, `g_board_io_outputs_enabled`, EPWM register view, scope

## 관련 문서

- architecture:
  - [epwm-bringup-boundary](../../../architecture/epwm-bringup-boundary.md)
  - [multicore-ownership](../../../architecture/multicore-ownership.md)
- plan:
  - [epwm-control-source-split](../../../plans/epwm-control-source-split.md)
- board reference: [pwm-architecture](../../../../docs/board/pwm-architecture.md)
- code collaborators:
  - [CPU1 main_cpu1.c](main_cpu1.c.md)
  - [CPU1 pinmux.c](pinmux.c.md)
  - [CPU1 epwm_ctrl.cpp planned](epwm_ctrl.cpp.md)
  - [CPU1 ctrl_loop.cpp planned](ctrl_loop.cpp.md)

## 관련 테스트와 검증

- bench 절차: `docs/specs/004-epwm-scope-smoke/verification.md`를 따른다.
- 기대 관측값: boot 후 safe-off 유지, debugger request `1`에서 EPWM1~12 A/B 파형 관측, request `0`에서 safe-off 복귀
- 성공 조건: EV 보드에서 예상 주파수, duty, deadband, safe-off 동작 확인
- 실패 시 확인 항목: C++ build 설정, CPUSEL, pinmux, EPWM clock enable, TBCLKSYNC, trip latch, buffer OE, scope GND 기준

## 변경 시 주의점

- 다음 구현 변경에서 `pwm.cpp`를 `epwm_ctrl.cpp`로 rename하고, 이 note의 현재 책임은 `epwm_ctrl.cpp.md`로 이동한다.
- EPWM register write, ADC trigger, trip-zone, control loop를 한 변경에 처음부터 모두 붙이지 않는다.
- dynamic allocation, RTTI, exceptions, virtual function, global constructor side effect를 도입하지 않는다.
