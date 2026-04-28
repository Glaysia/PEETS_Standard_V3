# Boot Flow

이 문서는 PEETS_Standard_V3의 CPU1, CPU2, CM boot/release 순서를 고정한다.

## Boundary

- CPU1은 시스템 마스터이며 초기 bring-up의 기준 core다.
- CPU2와 CM은 CPU1이 release한다.
- 각 core의 detailed peripheral bring-up은 기능별 `docs/specs/`에서 다룬다.

## Flow

1. `CPU1` 단독 부팅을 먼저 확인한다.
2. `CPU1`에서 clock, watchdog, heartbeat 같은 최소 기준선을 확인한다.
3. `CPU1 -> CM` release와 MSGRAM token handshake를 확인한다.
4. CM UART는 `CPU1 -> CM` handshake 성공 뒤에만 붙인다.
5. `CPU1 -> CPU2` release와 MSGRAM token handshake를 확인한다.
6. CPU2 fast ISR, EPWM/ADC update는 CPU2 main 진입과 handshake가 확인된 뒤에 붙인다.

## Invariants

- CM UART, CAN, Ethernet, USB는 CPU1-CM handshake 성공 전에는 enable하지 않는다.
- CPU2 fast control은 CPU1-CPU2 handshake 성공 전에는 enable하지 않는다.
- boot, clock, linker, startup, IPC 변경은 한 단계에서 동시에 섞지 않는다.
- 실패해도 CPU1 heartbeat 또는 diagnostic latch가 남아야 한다.

## Related Code Notes

- [CPU1 main_cpu1.c](../code/CPU1/source_editable/main_cpu1.c.md)
- [CM main_cm.cc](../code/CM/source_editable/main_cm.cc.md)
- [CPU2 main_cpu2.c](../code/CPU2/source_editable/main_cpu2.c.md)

## Related Specs

- `docs/specs/001-cpu1-cm-handshake/`
- `docs/specs/002-cm-uarta-hello/` 예정
- `docs/specs/003-cpu1-cpu2-handshake/` 예정

## 변경 시 주의점

- `Device_bootCM()` 또는 `Device_bootCPU2()` 호출 위치가 바뀌면 이 문서를 갱신한다.
- boot mode가 RAM/FLASH 사이에서 바뀌면 기능 spec과 검증 절차를 같이 갱신한다.
- debug core selection 절차가 바뀌면 `docs/people/sung/README.md` 또는 TODO도 함께 확인한다.
