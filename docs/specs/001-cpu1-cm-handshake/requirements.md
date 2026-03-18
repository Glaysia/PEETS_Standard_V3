# 001 CPU1-CM Handshake Requirements

## 목적

- `CM UART` 이전 단계로 `CPU1 -> CM boot/release + 최소 핸드셰이크`를 먼저 고정한다.

## 범위

- 포함:
  - CPU1이 CM boot/release를 수행하는 초기화 경로
  - CPU1과 CM 사이의 단일 boot-ready / acknowledge 왕복
  - timeout 시 CPU1 진단 상태 유지
- 제외:
  - `CM UARTA` 송수신
  - Ethernet, CAN, USB 같은 CM 통신 스택
  - CPU2 연동

## 제약

- `AGENTS.md`의 bring-up 순서를 따른다.
- `CM UART`는 이 핸드셰이크가 확인되기 전에는 붙이지 않는다.
- 초기 단계에서는 boot, clock, linker, startup, IPC를 한 번에 여러 개 바꾸지 않는다.
- 검증 포인트는 한 단계당 하나만 둔다.

## 요구사항

### R1 CPU1 단독 부팅 유지

```md
WHEN power-on reset completes
THE SYSTEM SHALL allow CPU1 to complete its own initialization and heartbeat behavior
before CM-dependent optional features are enabled.
```

검증 방법:
- CPU1 heartbeat GPIO가 기존과 동일하게 토글되는지 확인한다.

성공 조건:
- CM 상태와 무관하게 CPU1 heartbeat가 유지된다.

### R2 CM release

```md
WHEN CPU1 basic initialization completes
THE SYSTEM SHALL release CM through the approved boot path
after safe GPIO and required system initialization are complete.
```

검증 방법:
- CPU1 코드 경로에서 CM release 호출 지점을 명시하고, CM 코드가 main 진입 후 handshake 대기 상태에 들어가는지 확인한다.

성공 조건:
- CM이 최소한 `main()`까지 진입한다.

### R3 Boot-ready publish

```md
WHEN CPU1 releases CM
THE SYSTEM SHALL publish a boot-ready token in the agreed shared communication path.
```

검증 방법:
- MSGRAM 또는 IPC 경로의 단일 토큰 값이 CPU1에서 기록되는지 확인한다.

성공 조건:
- CM이 읽을 수 있는 위치에 boot-ready 토큰이 존재한다.

### R4 CM acknowledge

```md
WHEN CM observes the valid boot-ready token
THE SYSTEM SHALL write an acknowledge token back within the defined timeout.
```

검증 방법:
- CM이 acknowledge 토큰을 기록하고 CPU1이 이를 polling으로 감지하는지 확인한다.

성공 조건:
- timeout 이내에 CPU1이 acknowledge를 관측한다.

### R5 Failure containment

```md
IF acknowledge is not observed within the timeout
THEN CPU1 SHALL latch a diagnostic state and keep CM-dependent optional features disabled.
```

검증 방법:
- CM acknowledge를 의도적으로 막은 상태에서 CPU1 진단 상태와 fallback 동작을 확인한다.

성공 조건:
- CPU1은 멈추지 않고 heartbeat를 계속 유지한다.
- CM UART 등 후속 기능은 enable되지 않는다.

## 메모

- v1의 공유 경로는 가장 단순한 single-word mailbox를 우선한다.
- mailbox 위치와 토큰 값은 `design.md`에서 고정한다.
