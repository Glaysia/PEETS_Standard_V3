# SDD Index

이 문서는 PEETS_Standard_V3 SDD 문서의 시작점이다.

## 운영 규칙

- [[SDD]]: 저장소 전체 SDD 운영 규칙
- [[sdd/structure/document-layout]]: 문서 배치와 링크 규칙
- `docs/specs/README.md`: 기능별 bring-up spec 작성 규칙

## 기능별 spec

기능 구현이나 bring-up 작업은 `docs/specs/NNN-short-name/`에서 시작한다.

현재 파일럿:

- `docs/specs/001-cpu1-cm-handshake/`

권장 다음 spec 후보:

- `docs/specs/002-cm-uarta-hello/`
- `docs/specs/003-cpu1-cpu2-handshake/`
- `docs/specs/004-cpu1-standalone-heartbeat/`

## 아키텍처

- [[sdd/architecture/architecture-index]]: 아키텍처 문서 후보와 갱신 조건

우선 관리 대상:

- boot flow
- multicore ownership
- IPC routing
- memory map
- CCS project layout

## 구조

- [[sdd/structure/document-layout]]: `docs/specs/`, `sdd/architecture/`, `sdd/code/` 역할 분리

## 템플릿

- [[sdd/templates/source-note]]: 핵심 소스 파일 실질 수정 시 사용하는 source note 템플릿

## 사용 순서

1. 새 기능이면 `docs/specs/`에 기능별 spec을 만든다.
2. boot, ownership, IPC, memory map처럼 장기 구조가 바뀌면 `sdd/architecture/` 문서를 만든다.
3. 위험도가 큰 핵심 소스 파일을 실질 수정하면 `sdd/templates/source-note.md`를 복사해 `sdd/code/<repo-relative-path>.md`를 만든다.
4. 구현 후 `verification.md`에 실제 관측 결과를 남긴다.

