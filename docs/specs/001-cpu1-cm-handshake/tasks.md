# 001 CPU1-CM Handshake Tasks

## 사용 예제

- 구현 시작 시 C2000Ware의 dual-core / CM boot 예제 1개만 선택한다.
- 선택 기준:
  - F28388D에서 CPU1이 CM release를 다루는 예제일 것
  - shared MSGRAM 또는 최소 IPC flag 왕복이 포함될 것
  - UART, Ethernet, CAN 같은 다른 기능이 섞여 있지 않을 것

## 작업 순서

- [ ] Task 1: 기준 예제 1개 확정
  - 검증 포인트: boot/release와 mailbox 왕복 경로가 예제 안에 존재한다.
  - 성공 조건: 참고할 예제 이름, 경로, 가져올 범위가 문서에 기록된다.

- [ ] Task 2: CPU1 오케스트레이션 경로 추가
  - 검증 포인트: CPU1이 기존 heartbeat를 유지하면서 CM release까지 진행한다.
  - 성공 조건: CPU1 단독 부팅 회귀 없이 CM release 호출이 들어간다.

- [ ] Task 3: shared mailbox 초기화와 boot-ready write
  - 검증 포인트: CPU1이 agreed token을 write한다.
  - 성공 조건: debugger 또는 메모리 창에서 token이 확인된다.

- [ ] Task 4: CM side acknowledge 구현
  - 검증 포인트: CM이 boot-ready를 보고 ack를 write한다.
  - 성공 조건: CM `main()` 진입 후 ack token이 기록된다.

- [ ] Task 5: CPU1 polling timeout과 진단 latch
  - 검증 포인트: ack 성공/실패 두 경우가 분기된다.
  - 성공 조건: 성공 시 handshake-ok, 실패 시 diagnostic latch가 남는다.

- [ ] Task 6: `CM UART` 차단 조건 연결
  - 검증 포인트: handshake 전에는 CM UART 관련 후속 초기화가 실행되지 않는다.
  - 성공 조건: handshake 실패 시 UART bring-up task가 자동으로 진행되지 않는다.

- [ ] Task 7: bench 검증 기록
  - 검증 포인트: 실제 보드에서 성공/실패 케이스를 남긴다.
  - 성공 조건: `verification.md`가 `PENDING` 상태가 아니게 된다.

## 완료 조건

- `requirements.md`의 R1~R5에 모두 대응하는 코드 경로가 존재한다.
- `CPU1 -> CM handshake` 성공이 관측되기 전에는 `CM UART` 작업을 시작하지 않는다.
- 실제 검증 결과가 `verification.md`에 남는다.
