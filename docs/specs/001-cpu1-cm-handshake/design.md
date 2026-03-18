# 001 CPU1-CM Handshake Design

## 현재 상태

- `CPU1/source_editable/main_cpu1.c`는 현재 `Device_init()` 후 PWM smoke test와 heartbeat만 수행한다.
- `CM/source_editable/main_cm.cc`는 비어 있다.
- 현재 상태에서는 CPU1이 CM을 release했는지, CM이 실제로 살아났는지 확인하는 최소 경로가 없다.

## 설계 목표

- CPU1이 system master로서 CM boot/release를 명시적 순서로 수행한다.
- CPU1과 CM 사이에 인터럽트 없는 최소 mailbox 왕복을 먼저 고정한다.
- 실패 시에도 CPU1 단독 bring-up 신호는 유지한다.

## 비목표

- 이번 단계에서 `CM UARTA`를 붙이지 않는다.
- interrupt-driven IPC나 다중 메시지 프로토콜로 확장하지 않는다.
- CM을 시스템 필수 의존성으로 만들지 않는다.

## 제안 설계

### 통신 경로

- v1은 `CPU1 -> CM`, `CM -> CPU1` 방향으로 boot token / ack token 1개씩만 다룬다.
- 경로는 single-word mailbox를 우선한다.
- 구현 수단은 다음 우선순위를 따른다.
  1. C2000Ware가 제공하는 CM shared MSGRAM 기반 단순 mailbox
  2. 기존 boot path가 강하게 묶여 있을 때만 polling 기반 IPC flag
- v1에서는 ISR을 사용하지 않는다.

### 토큰

- `CPU1_TO_CM_BOOT_READY = 0xC001CAFE`
- `CM_TO_CPU1_ACK_READY = 0xACCECA11`

두 값은 문서 단계에서 먼저 고정한다.
구현 시에도 CPU1과 CM 양쪽에서 동일 상수를 사용한다.

### CPU1 상태 흐름

1. `Device_init()`
2. safe GPIO / heartbeat 초기화
3. mailbox 초기값 clear
4. CM release
5. boot-ready token write
6. timeout 동안 acknowledge polling
7. 성공 시 `cm_handshake_ok = true`
8. 실패 시 `cm_handshake_fault = true` latch
9. 메인 루프에서 heartbeat 유지

### CM 상태 흐름

1. `main()`
2. mailbox 관찰
3. boot-ready token 확인
4. acknowledge token write
5. 이후 idle loop 또는 다음 spec 대기

## 구현 포인트

### CPU1

- 파일 기준 시작점은 `CPU1/source_editable/main_cpu1.c`다.
- `main_cpu1.c`에는 오케스트레이션만 남기고, mailbox/boot helper는 별도 파일로 분리하는 것이 바람직하다.
- 권장 흐름은 `SystemInit() -> BoardSafeInit() -> CmHandshakeInit()` 형태다.

### CM

- 파일 기준 시작점은 `CM/source_editable/main_cm.cc`다.
- CM 쪽은 global constructor 없이 `main()`에서만 mailbox를 다룬다.
- v1은 `printf`, UART logging, 동적 메모리를 사용하지 않는다.

## 설계 메모

- `CM UARTA`는 `docs/board/board-io-reference.md`에 보이는 GPIO84/85를 사용하지만, 이번 단계에서는 핀과 UART 레지스터를 아직 건드리지 않는다.
- boot path와 mailbox 경로를 함께 바꾸더라도 linker/startup 변경까지 동시에 들어가면 원인 분리가 어려워진다.
- timeout은 디버깅이 쉬운 범위로 두되, blocking wait가 시스템 전체 정지를 만들지 않게 해야 한다.

## 리스크

- CM release API 선택이 잘못되면 CM이 `main()`에 도달하지 못한다.
- shared mailbox 주소/section 배치가 잘못되면 양 코어가 다른 메모리를 볼 수 있다.
- timeout 중 긴 busy wait는 이후 확장 시 문제가 될 수 있다.

## 완화 방법

- v1은 단일 토큰만 사용하고, 값과 메모리 위치를 문서에 먼저 고정한다.
- startup, linker, IPC interrupt를 동시에 건드리지 않는다.
- 실패 시에도 CPU1 heartbeat를 관측 기준으로 남긴다.
