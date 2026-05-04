# EPWM Bring-Up Boundary

이 문서는 EPWM을 아직 독립 모듈로 분리하지 않는 단계에서도 지켜야 할 bring-up 경계, ownership, 검증 순서를 정한다. 실제 구현 세부 구조는 후속 spec 또는 `docs/board/pwm-architecture.md`로 승격한다.

## Boundary

- v1 범위는 `EPWM1~12`의 무전력 scope smoke다.
- 목표는 제품용 제어기 완성이 아니라 A/B 출력, 주파수, duty, deadtime, phase shift, safe-off를 관측 가능한 기준선으로 고정하는 것이다.
- EPWM 초기 구현은 기존 `CPU1/include_editable/pwm.h`, `CPU1/source_editable/pwm.cpp` 후보 경로에서 시작할 수 있다.
- 이 단계에서 EPWM을 별도 production module로 완전히 분리하지 않아도 된다.
- 다만 EPWM register write, pinmux, ADC trigger, CMPSS/TZ를 한 변경에 섞지 않는다.

## Ownership Assumptions

- 현재 기준 ownership 가정은 CPU1이다.
- CPU2는 CPU1/CPU2 handshake와 CPU2 main 진입이 검증되기 전까지 EPWM runtime update를 맡지 않는다.
- 실제 ownership은 `CPUSEL`, `CPU1/include_editable/pinmux.h`, SysConfig 결과, 보드 문서를 기준으로 확인한다.
- CPU2로 EPWM update ownership을 넘기려면 별도 spec과 SDD 갱신이 필요하다.

## Bring-Up Order

1. CPU1 단독 부팅, heartbeat, watchdog/clock 기준선을 먼저 고정한다.
2. CPU1 -> CM handshake와 CPU1 -> CPU2 handshake가 실패하면 EPWM 실험으로 넘어가지 않는다.
3. Buffer EN/OE safe default와 실제 enable 동작을 확인한다.
4. `TBCLKSYNC off` 상태에서 EPWM profile을 적용한다.
5. 출력은 `safe-off first`로 시작하고, scope 연결과 계측 준비 후 enable한다.
6. 먼저 EV 보드에서 EPWM1~12 A/B 파형을 확인한다.
7. 실보드는 buffer enable, 전원 상태, 단락 여부, GND 공통 확인 뒤 같은 체크리스트로 반복한다.

## Implementation Rules

- pinmux 자체는 EPWM bring-up 코드에서 다시 정의하지 않는다.
- peripheral clock과 pinmux는 기존 `Device_init()`, `PinMux_init()` 흐름을 우선 사용한다.
- EPWM 설정은 driverlib 기반으로 작성한다.
- C28x C++03 정책을 따른다: 예외, RTTI, 동적 메모리, 가상 함수, 전역 생성자 side effect를 사용하지 않는다.
- 하드웨어 side effect는 `init`, `apply`, `start`, `stop`, `enable`, `disable`, `trip`, `clear`처럼 호출 지점이 보이는 함수에 둔다.
- ISR 경로에는 초기 bring-up용 긴 polling, logging, blocking wait를 넣지 않는다.
- ADC trigger와 CMPSS/TZ 보호 체인은 EPWM scope smoke가 닫힌 뒤 별도 spec으로 붙인다.

## Minimum EPWM Smoke Set

| 항목                   | 최소 확인                                         |
| -------------------- | --------------------------------------------- |
| Channel coverage     | EPWM1~12 A/B 출력 핀 scope 관측                    |
| Independent output   | A/B가 각 compare 설정을 반영하는지 확인                   |
| Complementary output | deadband 포함 보완 파형 확인                          |
| Phase shift          | master/slave phase offset 확인                  |
| Safe-off             | enable 전 출력 off, trip/disable 시 safe state 확인 |
| Runtime update       | duty 또는 period 변경이 bounded 경로로 반영되는지 확인       |

## Debug And Verification

- 코드 변경 전 사용한 CCS/C2000Ware 예제를 기록한다.
- 각 실험은 사용 예제, 코드 변경, 실제 관측, 성공 조건을 `docs/specs/004-epwm-scope-smoke/`에 남긴다.
- 최소 성공 조건은 EV 보드에서 EPWM1~12 A/B가 예상 주파수와 duty로 관측되고, safe-off와 disable 동작이 확인되는 것이다.
- 실보드 성공 조건은 EV 보드와 같은 체크리스트를 통과하고, buffer enable과 전원 준비 조건이 문서화되는 것이다.
- 실패 시 먼저 확인할 항목은 `CPUSEL`, pinmux, EPWM clock enable, `TBCLKSYNC`, trip latch, buffer EN/OE, scope GND 기준이다.

## Related Documents

- [multicore-ownership](multicore-ownership.md)
- [boot-flow](boot-flow.md)
- [intercore-source-split](intercore-source-split.md)
- `docs/board/pwm-architecture.md`
- `docs/board/board-io-reference.md`
- `docs/specs/004-epwm-scope-smoke/` 예정
