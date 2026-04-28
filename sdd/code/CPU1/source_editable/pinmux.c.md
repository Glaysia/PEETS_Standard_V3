# CPU1 source_editable/pinmux.c

## 소스 경로

- path: `CPU1/source_editable/pinmux.c`
- project: `CPU1`
- language: `C`

## 단일 책임

- SysConfig/Pinmux 결과 값을 CPU1 GPIO control register와 Input X-BAR select register에 적용한다.
- 이 파일은 pin assignment의 source of truth가 아니라 generated value를 적용하는 실행 경로다.
- 이 파일은 runtime peripheral policy, PWM profile, UART protocol, CPU2 fast loop를 맡지 않는다.

## 실행 코어와 초기화 순서

- 실행 코어: `CPU1`
- 호출 위치: 아직 `main_cpu1.c`에서 직접 호출되지 않는다. pinmux bring-up spec에서 호출 위치를 고정해야 한다.
- 권장 흐름: `Device_init() -> GPIO_setPinMuxConfig() -> board safe GPIO init -> peripheral-specific init`
- 선행 조건: CPU1 GPIO control register 접근 가능
- 후행 조건: GPIO mux, analog mode, Input X-BAR select 값이 generated header와 일치해야 한다.

## 주요 입력과 출력

- 입력: `CPU1/include_editable/pinmux.h`의 mask/value macro
- 출력: GPIO mux register write, Input X-BAR select register write
- shared state: GPIO control register와 XBAR register
- 외부 관측값: GPIO pin function, scope/logic analyzer pin behavior

## Hardware / Driverlib 의존성

- peripheral: GPIO control, Input X-BAR
- register/API: `HWREG`, `HWREGH`, `EALLOW`, `EDIS`, `GPIOCTRL_BASE`, `INPUTXBAR_BASE`
- CPUSEL / pinmux / SysConfig 의존성: CPU1-only GPIO control register와 generated pinmux header에 의존
- clock source: CPU1 device init 이후 GPIO/XBAR register 접근 가능해야 한다.

## Memory / Startup / Linker 의존성

- section: 기본 code section
- linker command file: 특별 section 없음
- startup/vector 의존성: 없음
- IPC MSGRAM 의존성: 없음

## Interrupt / Trigger / Timing

- ISR: 없음
- trigger source: explicit function call
- bounded 조건: register write sequence
- background와 공유하는 데이터: GPIO mux register state
- 동기화 방식: EALLOW/EDIS 보호 구간

## 핵심 invariant

- pin 변경은 `docs/board/board-io-reference.md`, SysConfig 결과, 실제 보드 배선 확인 없이 하지 않는다.
- Ethernet/EtherCAT처럼 고정 배선 기능은 bring-up 근거 없이 재할당하지 않는다.
- CM UART와 C28x SCI pin을 혼동하지 않는다.

## Fail-fast / 실패 처리

- 실패 조건: pinmux header와 보드 문서 불일치, reserved pin 재할당, scope 관측 불일치
- 시스템 동작: 해당 peripheral bring-up을 멈추고 pin/source of truth를 재확인한다.
- 후속 기능 차단 조건: pinmux 불확실하면 PWM, UART, fault input 테스트를 진행하지 않는다.
- debug 관측 방법: register view, scope, `docs/board/board-io-reference.md` 대조

## 관련 문서

- architecture:
  - [multicore-ownership](../../../architecture/multicore-ownership.md)
- board reference: [board-io-reference](../../../../docs/board/board-io-reference.md)
- code collaborators:
  - [CPU1 main_cpu1.c](main_cpu1.c.md)
  - [CPU1 pwm.cpp](pwm.cpp.md)

## 관련 테스트와 검증

- bench 절차: pinmux apply 후 대상 GPIO/peripheral pin을 scope 또는 debugger register view로 확인
- 기대 관측값: generated header의 pin function과 실제 pin behavior 일치
- 성공 조건: targeted peripheral smoke에서 pin mismatch가 없음
- 실패 시 확인 항목: SysConfig snapshot, generated macro, board wiring, CPUSEL ownership

## 변경 시 주의점

- 이 파일을 손으로 대규모 수정하지 말고 SysConfig 결과와 차이를 문서화한다.
- pinmux 변경과 peripheral driver bring-up을 한 커밋에 무리하게 섞지 않는다.
- CPU2나 CM ownership 변경은 architecture/spec 갱신 없이는 하지 않는다.
