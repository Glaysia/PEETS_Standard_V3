# Comm CM Source Split

이 문서는 CM 통신 코드를 `comm_cm` C++ 모듈로 분리하기 위한 기준을 정한다. 현재 통신 대상은 UART뿐이지만, 이름은 향후 CAN/Ethernet/USB 진단 경로를 담을 수 있게 `comm_cm`으로 고정한다.

## Boundary

- `comm_cm`은 CM core에서 동작하는 비실시간 통신 계층이다.
- v1 범위는 UARTA TX smoke, 향후 UART loopback, PC serial RX/TX 확인이다.
- CPU1/CPU2 boot, MSGRAM token, intercore release 로직은 `comm_cm`의 책임이 아니다.
- CM UART 작업은 CPU1 -> CM handshake 성공 뒤에만 enable한다.
- C28x SCI와 CM UART는 다른 peripheral로 취급한다.

## Planned Source Layout

| Header | Source | 역할 |
| --- | --- | --- |
| `CM/include_editable/comm_cm.h` | `CM/source_editable/comm_cm.cc` | CM UART init, TX smoke, loopback/serial test helper, 통신 상태 카운터 |

`main_cm.cc`는 장기적으로 CM init, intercore handshake gate, comm module 호출만 남기는 방향으로 줄인다.

## Public Contract

- v1 API는 명시적 초기화와 명시적 송신 함수만 둔다. 예: `CommCm_initUartTx()`, `CommCm_writeString()`, `CommCm_runUartSmokeTick()`.
- UART baud rate, TX idle delay, TX count 같은 bring-up 관측값은 `comm_cm`에 모은다.
- GPIO84/85 pinmux는 CPU1 ownership과 SysConfig/board 문서를 확인한 뒤 다룬다. `comm_cm`은 CM UART peripheral 설정과 송수신을 담당한다.
- 통신 실패가 CPU2 fast control 또는 power-stage safe state를 직접 흔들지 않게 한다.

## Implementation Rules

- CM 쪽은 기존 `.cc` 흐름을 유지한다. 단, 생성자 side effect와 전역 객체 초기화에 기대지 않는다.
- hardware side effect는 `init`, `enable`, `tick`, `write`처럼 호출 지점이 보이는 함수에 둔다.
- v1 UART TX smoke는 blocking write를 허용하지만, 후속 RX/loopback에서는 timeout 또는 bounded polling을 둔다.
- ISR, DMA, ring buffer, protocol framing은 v1에서 넣지 않는다. 필요하면 별도 spec으로 분리한다.
- UART 관련 상수와 카운터는 `main_cm.cc`에 흩어두지 않고 `comm_cm`으로 이동한다.

## Debug And Verification

- CM 관측값: CM main 진입, CPU1-CM ACK 상태, UART init 여부, TX count, loopback/serial RX count.
- Scope 관측값: GPIO84 UARTA_TX 파형, baud rate, idle interval.
- 최소 성공 조건: CPU1 heartbeat 유지, CPU1-CM ACK 유지, UART TX 파형 관측, CM hang 없음.
- PC serial 단계 성공 조건: 설정 baud rate로 문자열이 안정적으로 수신되고, 반복 송신 중 CPU1/CM 상태 latch가 유지된다.

## Related Documents

- [boot-flow](boot-flow.md)
- [multicore-ownership](multicore-ownership.md)
- [ipc-routing](ipc-routing.md)
- `docs/specs/002-cm-uarta-hello/` 예정

