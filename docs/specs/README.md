# Specs

이 디렉터리는 이 워크스페이스에서 사용하는 가벼운 SDD(Spec-Driven Development) 문서를 둔다.
목적은 구현 전에 요구사항, 설계 판단, 작업 순서, 검증 방법을 먼저 고정해서 bring-up 실패 원인을 분리하는 것이다.

## 이 저장소에서의 SDD 원칙

- spec은 코드를 대체하지 않는다. 구현 전에 변경 이유와 성공 조건을 고정하는 문서다.
- spec은 작아야 한다. 기능 1개당 spec 1개를 기본으로 한다.
- bring-up 초기에는 여러 기능을 한 spec에 섞지 않는다.
- `AGENTS.md`의 bring-up 순서와 변경 금지 항목을 우선한다.
- 초기 단계에서는 boot, clock, linker, startup, IPC를 한 번에 여러 개 바꾸는 spec을 만들지 않는다.
- 새 기능은 가능하면 CCS/C2000Ware 예제 1개를 기준으로 잡고, 검증 방법과 성공 조건을 함께 남긴다.

## 폴더 규칙

- 경로 형식은 `docs/specs/NNN-short-name/` 으로 한다.
- 번호는 작업 순서를 반영한다.
- 이름은 기능 단위를 드러내야 한다.
- 예:
  - `001-cpu1-cm-handshake`
  - `002-cm-uarta-hello`
  - `010-cpu2-adc-trigger-chain`

## 파일 구성

각 spec 폴더는 아래 4개 파일을 기본으로 둔다.

- `requirements.md`: 무엇을 만족해야 하는지
- `design.md`: 어떤 방식으로 구현할지
- `tasks.md`: 어떤 순서로 바꿀지
- `verification.md`: 어떻게 확인할지

새 spec은 `docs/specs/_template/`를 복사해서 시작한다.

## requirements 작성 규칙

- 요구사항은 검증 가능하게 적는다.
- 모호한 표현 대신 조건, 동작, 실패 시 처리, 성공 기준을 적는다.
- 가능하면 EARS 스타일을 따른다.

예:

```md
WHEN CPU1 system initialization completes
THE SYSTEM SHALL release CM and publish a boot-ready flag.

IF CM acknowledge is not observed within the timeout
THEN CPU1 SHALL keep CM-dependent optional features disabled.
```

## design 작성 규칙

- 현재 상태와 변경 이유를 함께 적는다.
- core ownership, pinmux, boot flow, IPC 경로를 명시한다.
- side effect는 명시적 init 경로에만 둔다.
- C28x 쪽은 `AGENTS.md`의 C++03 제한을 그대로 따른다.

## tasks 작성 규칙

- 작업은 순차적이어야 한다.
- 각 task는 검증 포인트 하나만 가지게 쪼갠다.
- 예제 기반 도입이면 사용 예제를 먼저 적는다.
- task 완료 기준은 "코드 변경"이 아니라 "관측 가능한 결과"로 적는다.

## verification 작성 규칙

- bench 절차를 짧고 반복 가능하게 적는다.
- 기대 관측값, 실패 조건, 로그 위치를 함께 적는다.
- 아직 검증 전이면 `PENDING`으로 남긴다.

## 권장 흐름

1. `requirements.md`를 먼저 고정한다.
2. `design.md`에서 ownership과 제약을 정리한다.
3. `tasks.md`를 작은 단계로 나눈다.
4. 구현 후 `verification.md`에 실제 결과를 남긴다.

## 현재 파일럿

- `001-cpu1-cm-handshake`
  - 목적: `CM UART` 이전에 `CPU1 -> CM boot/release + 최소 핸드셰이크`를 먼저 닫는다.
