# SDD Index

이 문서는 PEETS_Standard_V3 SDD 문서의 시작점이다.

## 운영 규칙

- [SDD](../SDD.md): 저장소 전체 SDD 운영 규칙
- [document-layout](structure/document-layout.md): 문서 배치와 링크 규칙
- [agent-sdd-workflow](structure/agent-sdd-workflow.md): 에이전트 코드 수정 전 SDD 작업 순서
- [commit-policy](structure/commit-policy.md): SDD와 구현 변경의 커밋 묶음 규칙
- `docs/specs/README.md`: 기능별 bring-up spec 작성 규칙

## 코드 대응 문서

- [sdd-code-index](code/sdd-code-index.md): editable source와 직접 대응되는 code note 허브

초기 baseline code notes:

- [CPU1 main_cpu1.c](code/CPU1/source_editable/main_cpu1.c.md)
- [CM main_cm.cc](code/CM/source_editable/main_cm.cc.md)
- [CPU2 main_cpu2.c](code/CPU2/source_editable/main_cpu2.c.md)
- [CPU1 pwm.cpp](code/CPU1/source_editable/pwm.cpp.md)
- [CPU1 pinmux.c](code/CPU1/source_editable/pinmux.c.md)

## 기능별 spec

기능 구현이나 bring-up 작업은 `docs/specs/NNN-short-name/`에서 시작한다.

현재 파일럿:

- `docs/specs/001-cpu1-cm-handshake/`

권장 다음 spec 후보:

- `docs/specs/002-cm-uarta-hello/`
- `docs/specs/003-cpu1-cpu2-handshake/`
- `docs/specs/004-cpu1-standalone-heartbeat/`

## 아키텍처

- [architecture-index](architecture/architecture-index.md): 아키텍처 문서 후보와 갱신 조건

우선 관리 문서:

- [boot-flow](architecture/boot-flow.md)
- [multicore-ownership](architecture/multicore-ownership.md)
- [ipc-routing](architecture/ipc-routing.md)
- [memory-map](architecture/memory-map.md)
- [intercore-source-split](architecture/intercore-source-split.md)
- [comm-cm-source-split](architecture/comm-cm-source-split.md)
- [epwm-bringup-boundary](architecture/epwm-bringup-boundary.md)

## 구조

- [document-layout](structure/document-layout.md): `docs/specs/`, `sdd/architecture/`, `sdd/code/` 역할 분리
- [agent-sdd-workflow](structure/agent-sdd-workflow.md): 에이전트 작업 루프와 금지 패턴
- [commit-policy](structure/commit-policy.md): 커밋과 SDD note 동반 규칙

## 계획

- [sdd-plans-index](plans/sdd-plans-index.md): 큰 bring-up, 리팩터링, 주변장치 통합 계획 허브

## 템플릿

- [source-note](templates/source-note.md): 핵심 소스 파일 실질 수정 시 사용하는 source note 템플릿
- [plan-note](templates/plan-note.md): 큰 작업 전 사용하는 plan note 템플릿

## 사용 순서

1. 새 기능이면 `docs/specs/`에 기능별 spec을 만든다.
2. boot, ownership, IPC, memory map처럼 장기 구조가 바뀌면 `sdd/architecture/` 문서를 만든다.
3. editable source를 실질 수정하면 `sdd/templates/source-note.md`를 기준으로 `sdd/code/<repo-relative-path>.md`를 만들거나 갱신한다.
4. 구현 후 `verification.md`에 실제 관측 결과를 남긴다.
