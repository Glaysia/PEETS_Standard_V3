# 001 CPU1-CM Handshake Verification

상태: `PENDING`

## 환경

- 보드: PEETS Standard V3 + F28388D
- 빌드 구성: `CPU1_RAM`, `CM_RAM` 또는 실제 사용 구성
- 사용 예제: `TBD`

## 절차

1. CPU1만 먼저 로드하고 heartbeat가 유지되는지 확인한다.
2. CPU1에서 CM release와 boot-ready token write가 실행되게 한다.
3. CM이 `main()`에 진입해 acknowledge token을 write하는지 확인한다.
4. CPU1이 timeout 이내에 acknowledge를 감지하는지 확인한다.
5. CM acknowledge를 막은 상태에서 CPU1 diagnostic latch가 남는지 확인한다.

## 기대 결과

- 성공 케이스:
  - CPU1 heartbeat 유지
  - boot-ready token write 관측
  - CM acknowledge token write 관측
  - CPU1 handshake-ok 상태 관측
- 실패 케이스:
  - CPU1 heartbeat 유지
  - timeout 후 diagnostic latch 관측
  - `CM UART` 관련 후속 기능 미실행

## 관측 방법

- CPU1 heartbeat GPIO
- debugger memory window의 mailbox 값
- CPU1 / CM의 상태 변수

## 실패 시 확인 항목

- CM release API 선택
- MSGRAM / IPC 경로와 linker section 일치 여부
- startup code 변경 여부
- boot, clock, linker, startup, IPC를 한 번에 같이 바꿨는지 여부

## 결과 기록

- 날짜: `TBD`
- 결과: `PENDING`
- 메모:
