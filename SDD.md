# SDD

이 저장소의 Software Design Documentation 운영 규칙은 이 문서가 정한다.
실무 기준점은 `AGENTS.md`, `README.md`, `docs/specs/README.md`, 그리고 `sdd/sdd-index.md`다.

## 목적

- F28388D CCS 워크스페이스의 bring-up 변경 이유, 설계 판단, 검증 조건을 코드와 분리되지 않게 유지한다.
- 초기 bring-up에서 boot, clock, linker, startup, IPC, pinmux 변경이 한 번에 섞이는 것을 막는다.
- 처음 보는 엔지니어가 문서만 보고 다음 검증 순서와 변경 금지 영역을 판단할 수 있게 한다.

## 적용 범위

- 기본 대상은 앞으로 새로 만드는 기능별 bring-up spec, 아키텍처 문서, 핵심 소스 변경 노트다.
- 기존 레거시 파일은 untouched 상태에서는 소급 문서화하지 않는다.
- 생성 폴더(`CPU1_RAM`, `CPU2_RAM`, `CM_RAM`)와 CCS 산출물은 SDD 대상이 아니다.
- TI/C2000Ware에서 가져온 원본 성격의 파일은 직접 수정하지 않는 한 SDD 대상이 아니다.

## 문서 체계

- 기능별 변경은 `docs/specs/NNN-short-name/` 아래에서 시작한다.
- 장기 참조 구조와 설계 경계는 `sdd/architecture/`와 `sdd/structure/`에 둔다.
- editable source를 실질 수정할 때는 `sdd/code/<repo-relative-path>.md` 노트를 같이 만들거나 갱신한다.
- 큰 bring-up, 리팩터링, 주변장치 통합은 `sdd/plans/` 또는 `docs/specs/`에서 먼저 작업 경계를 고정한다.
- SDD 허브는 `sdd/sdd-index.md`다.

## 실질 수정 정의

아래 변경은 실질 수정이다.

- boot flow 변경
- clock, watchdog, GPIO 기본 상태 변경
- linker command file, memory section, startup, interrupt vector 변경
- IPC MSGRAM section, IPC flag, handshake, routing 변경
- CPUSEL, pinmux, peripheral ownership 변경
- EPWM, ECAP, ADC trigger, CMPSS, XBAR, trip-zone 연결 변경
- ISR 실행 경로, trigger source, shared state, volatile/critical section 계약 변경
- C28x C/C++ ABI, pragma, interrupt attribute, section placement 변경
- CM 통신 peripheral 초기화 순서 또는 CPU1 release 전제 변경

아래 변경은 보통 실질 수정이 아니다.

- 포맷팅-only
- comment-only
- 의미와 동작이 바뀌지 않는 문서 링크 정리
- 생성 산출물 삭제 또는 `.gitignore` 정리

애매하면 실질 수정으로 간주하고 관련 spec 또는 SDD 문서를 함께 갱신한다.

## 작업 순서

- 실질 수정 전에는 먼저 관련 `docs/specs/` 또는 `sdd/` 문서를 확인한다.
- 수정할 editable source가 있으면 대응 `sdd/code/` note를 먼저 확인한다.
- 새 bring-up 기능은 `requirements.md`에서 성공 조건을 먼저 고정한 뒤 `design.md`, `tasks.md`, `verification.md` 순서로 구체화한다.
- boot, clock, linker, startup, IPC는 초기 단계에서 동시에 바꾸지 않는다.
- peripheral 추가는 가능하면 CCS/C2000Ware 예제 1개를 기준으로 시작하고, 사용 예제와 검증 방법을 남긴다.
- 구현 후에는 실제 관측 결과를 `verification.md`에 기록한다.

## 레거시 백필 금지

- 기존 전체 코드를 한 번에 SDD로 백필하지 않는다.
- 새 파일을 만들거나 실질 수정한 editable source를 문서화 대상으로 삼는다.
- `device_not_editable/`와 untouched legacy 파일은 직접 수정하지 않는 한 code note를 강제하지 않는다.
- 문서화가 작업보다 커지면 기능별 spec과 핵심 architecture 문서를 우선하되, 수정한 editable source의 책임 note는 생략하지 않는다.

## 우선순위

1. `AGENTS.md`의 bring-up 순서와 변경 금지 항목
2. `docs/specs/`의 기능별 요구사항과 검증 조건
3. `sdd/architecture/`와 `sdd/structure/`의 장기 설계 기준
4. 개별 source note
