# EPWM Control Source Split Plan

## 목적

- 현재 CPU1 테스트 단계의 `pwm.cpp`를 EPWM peripheral 제어 계층으로 이름과 책임을 정리한다.
- 제어 law와 PWM command 생성 코드는 EPWM register write 코드와 분리한다.
- CPU2 최종 이관 전까지는 CPU1에서 무전력 scope smoke와 runtime update 실험을 진행한다.

## 대상 소스

| 상태 | 경로 | 책임 |
| --- | --- | --- |
| rename 예정 | `CPU1/source_editable/pwm.cpp` -> `CPU1/source_editable/epwm_ctrl.cpp` | EPWM hardware wrapper, channel/group, duty/period/phase/trip 적용 |
| 신규 예정 | `CPU1/include_editable/epwm_ctrl.h` | C ABI와 EPWM control POD/public API |
| 신규 예정 | `CPU1/source_editable/ctrl_loop.cpp` | 테스트용 control loop, command 생성, duty/period/phase update 정책 |
| 신규 예정 | `CPU1/include_editable/ctrl_loop.h` | control loop C ABI와 상태/명령 interface |

## 책임 경계

- `epwm_ctrl.*`는 C2000 EPWM 주변장치 제어 계층이다.
- `epwm_ctrl.*`는 `TBPRD`, `CMPA/CMPB`, `TBPHS`, `AQ`, `DB`, `TZ`, sync, shadow/global load 같은 hardware-facing 동작을 맡는다.
- `ctrl_loop.*`는 제어 입력을 받아 `duty`, `period`, `phase`, `deadband` command를 만든다.
- `ctrl_loop.*`는 EPWM register를 직접 쓰지 않는다.
- board buffer OE/DIR safe default는 `main_cpu1.c` 또는 후속 board I/O 파일 책임으로 유지한다.

## 초기 구현 순서

1. `pwm.cpp`를 `epwm_ctrl.cpp`로 rename하고 외부 smoke C ABI를 유지한다.
2. `pwm.h`의 이름은 첫 rename에서는 유지할 수 있지만, 다음 단계에서 `epwm_ctrl.h`로 정리한다.
3. `EpwmChannel` 정적 배열을 도입하고 EPWM1~12 base, period, compare, phase, deadband를 보관한다.
4. 기존 `pwm_smoke_init()`, `pwm_smoke_force_safe_off()`, `pwm_smoke_release_outputs()` 내부를 `EpwmChannel`/`EpwmGroup` 메서드 호출로 바꾼다.
5. `ctrl_loop.cpp`를 추가하고 debugger 또는 고정 test 변수 기반 command 생성만 먼저 넣는다.
6. `ctrl_loop`가 만든 command를 `epwm_ctrl` commit 함수로 반영한다.

## C++03 제한

- `new/delete`, exception, RTTI, virtual function은 사용하지 않는다.
- 전역 객체 constructor에서 register write를 하지 않는다.
- static storage는 POD에 가깝게 두고, hardware side effect는 `init`, `apply`, `commit`, `forceTrip`, `clearTrip` 같은 명시 함수 안에 둔다.
- ISR에서 호출될 수 있는 함수는 bounded path만 허용한다.

## CPU Ownership

- 현재 테스트 단계: CPU1에서 EPWM init, safe-off, scope smoke, runtime update 실험을 진행한다.
- 최종 방향: CPU2가 fast control loop와 EPWM runtime update를 맡을 수 있다.
- CPU2 이관 조건: CPU1/CPU2 handshake, CPUSEL, pinmux, ADC trigger, interrupt routing, EPWM safe default가 별도 spec에서 검증되어야 한다.

## 완료 조건

- `main_cpu1.c`가 EPWM register 세부 설정을 직접 알지 않는다.
- `epwm_ctrl.*`와 `ctrl_loop.*`의 책임이 섞이지 않는다.
- EV 보드에서 EPWM safe-off, enable, duty/period/phase runtime update가 각각 독립 관측된다.
