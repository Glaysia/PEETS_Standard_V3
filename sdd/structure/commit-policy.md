# Commit Policy

이 문서는 SDD와 구현 변경을 커밋 단위에서 분리하지 않기 위한 기준이다.

## Grouping Rules

- 커밋은 논리 단위를 우선한다.
- 서로 다른 bring-up 검증 포인트가 섞이면 커밋을 분리한다.
- 관련 파일이 많아도 같은 검증 단위이면 함께 묶는다.
- 파일 수를 맞추기 위해 무관한 변경을 끼우지 않는다.

## SDD Coupling

- 핵심 editable source의 실질 수정은 대응 `sdd/code/` note와 함께 커밋한다.
- 기능 bring-up은 관련 `docs/specs/` 문서와 함께 커밋한다.
- boot, ownership, IPC, memory map 변경은 관련 `sdd/architecture/` 문서와 함께 커밋한다.
- 문서 배치나 에이전트 작업 규칙 변경은 `sdd/structure/` 문서와 함께 커밋한다.

## Exclusions

- CCS 생성 폴더와 build output은 커밋하지 않는다.
- `.settings`는 사용자 환경 의존성이 크므로 꼭 필요한 경우만 포함한다.
- `device_not_editable/` 수정은 원본 성격 파일 변경 사유가 SDD에 기록된 경우만 포함한다.
- 임시 scope 캡처, 실험 로그, local IDE 상태는 명시 요청 없이는 포함하지 않는다.

## Commit Message

- 기본 형식은 `<area>: <summary>`다.
- 예: `sdd: add CPU2 handshake notes`, `cpu1: add CM handshake timeout latch`
- summary는 변경의 검증 단위를 드러내게 쓴다.

## Pre-Commit Checks

- `git status --short --untracked-files=all`로 예상 밖 변경을 확인한다.
- 관련 RAM build가 가능하면 CCS 또는 documented build 절차로 확인한다.
- 실제 보드 검증이 필요한 변경은 `verification.md`에 `PENDING` 또는 실제 결과를 명확히 남긴다.
