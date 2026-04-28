# Intercore Source Split

이 문서는 CPU1/CPU2/CM 사이 bring-up 테스트 코드를 장기적으로 사용할 intercore C 모듈로 분리하기 위한 기준을 정한다.

## Boundary

- `intercore`는 CPU 사이 boot/release, MSGRAM token 왕복, 상태 latch, timeout 관측만 담당한다.
- v1 범위는 polling 기반 handshake다. IPC interrupt, queue, packet protocol, telemetry stream은 후속 spec 대상이다.
- CPU1/CPU2 쪽 intercore 소스는 C로 작성한다. 기존 `.c` 파일을 `.cc`로 바꾸지 않는다.
- CM이 intercore header를 참조해야 하면 C ABI로 노출한다. CM 내부 구현이 C++이어도 intercore 계약은 C 중심으로 유지한다.

## Planned Source Layout

| Core | Header | Source | 역할 |
| --- | --- | --- | --- |
| CPU1 | `CPU1/include_editable/intercore_cpu1.h` | `CPU1/source_editable/intercore_cpu1.c` | CPU2/CM release, token write, ACK wait, status latch |
| CPU2 | `CPU2/include_editable/intercore_cpu2.h` | `CPU2/source_editable/intercore_cpu2.c` | CPU1 token observe, CPU2 ACK write, CPU2 tick/status latch |
| Shared tokens | `CPU1/include_editable/intercore_tokens.h`, `CPU2/include_editable/intercore_tokens.h` | 없음 | token 값, timeout 상수, status enum 계약 |

CM handshake token이 intercore로 승격되면 CM 쪽에는 `CM/include_editable/intercore_cm.h`와 `CM/source_editable/intercore_cm.cc` 또는 C ABI wrapper를 별도 검토한다. v1에서는 CPU1/CPU2 분리를 먼저 끝낸다.

## Public Contract

- token 값은 한 곳에서 정의하고 양쪽 core가 같은 값을 include해야 한다.
- MSGRAM mailbox는 `#pragma DATA_SECTION`과 linker command file section 이름이 일치해야 한다.
- CPU1은 remote core release 전후 상태를 status enum으로 남긴다.
- CPU1은 timeout 안에 ACK를 못 받으면 timeout latch를 남기고 후속 기능 enable을 막는다.
- CPU2는 `main()` 진입 여부, token 관측 여부, ACK write 여부, tick count를 debugger에서 볼 수 있게 남긴다.

## Implementation Rules

- CPU1/CPU2 intercore API는 C 함수로 둔다. 예: `IntercoreCpu1_bootCpu2()`, `IntercoreCpu1_runCpu2Handshake()`, `IntercoreCpu2_serviceHandshake()`.
- C28x C++03 wrapper는 지금 만들지 않는다. 필요해지면 side effect 없는 얇은 wrapper만 별도 변경으로 추가한다.
- 생성자, 전역 객체, dynamic allocation, exception, RTTI에 의존하지 않는다.
- ISR 경로에 handshake polling을 넣지 않는다.
- shared state는 `volatile` 또는 명시적 동기화 계약으로 다룬다.
- 하드코딩 주소보다 linker section에 배치된 symbol을 우선한다. 주소를 써야 하면 양쪽 offset 계약과 근거 문서를 같이 남긴다.

## Debug And Verification

- CPU1 관측값: CPU2 boot/release status, poll count, timeout/OK latch, MSGRAM token 값.
- CPU2 관측값: `main()` 진입 flag, handshake status, tick count, ACK token 값.
- 최소 성공 조건: CPU1/CPU2/CM 세 core가 동시에 run 상태이고, CPU1 heartbeat가 유지되며, CPU1-CPU2 token 왕복이 timeout 없이 끝난다.
- 실패 시 먼저 확인할 항목: CPU2 image load 여부, boot mode, MSGRAM section 이름, token 값, mailbox offset, linker command file.

## Related Documents

- [boot-flow](boot-flow.md)
- [ipc-routing](ipc-routing.md)
- [memory-map](memory-map.md)
- [multicore-ownership](multicore-ownership.md)

