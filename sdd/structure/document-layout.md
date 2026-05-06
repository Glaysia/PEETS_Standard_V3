# Document Layout

이 문서는 PEETS_Standard_V3의 SDD 문서 배치 규칙을 정한다.

## 기본 원칙

- 기능별 변경은 작게 나누고 `docs/specs/`에서 시작한다.
- 장기 참조가 필요한 구조와 경계는 `sdd/`에 둔다.
- 모든 소스 파일에 1:1 문서를 강제하지 않는다.
- 레거시 전체 백필은 하지 않는다.

## 경로 역할

| 경로 | 역할 |
| --- | --- |
| `SDD.md` | 저장소 전체 SDD 운영 규칙 |
| `sdd/sdd-index.md` | SDD 허브 |
| `docs/specs/NNN-short-name/` | 기능별 bring-up spec |
| `sdd/architecture/` | boot, IPC, ownership, memory map 같은 장기 설계 |
| `sdd/structure/` | 문서 배치, 프로젝트 구조, ownership map |
| `sdd/plans/` | 큰 bring-up, 리팩터링, 주변장치 통합 전 계획 |
| `sdd/templates/` | SDD 작성 템플릿 |
| `sdd/code/` | editable source와 직접 대응되는 source note |

## 기능별 spec 규칙

- 경로는 `docs/specs/NNN-short-name/` 형식을 따른다.
- 번호는 작업 순서를 반영한다.
- 하나의 spec은 하나의 검증 가능한 기능만 다룬다.
- 기본 파일은 `requirements.md`, `design.md`, `tasks.md`, `verification.md`다.
- 새 spec은 `docs/specs/_template/`를 복사해서 시작한다.

## Architecture 문서 생성 조건

아래 항목이 바뀌면 `sdd/architecture/` 문서를 만들거나 갱신한다.

- CPU1, CPU2, CM의 boot/release 순서
- peripheral ownership 또는 CPUSEL 기준
- IPC flag, MSGRAM, routing 구조
- linker command file과 memory section 배치
- interrupt/vector/startup 책임
- CCS 프로젝트 layout이나 tool discovery 기준

## Source note 생성 조건

`sdd/code/<repo-relative-path>.md`는 editable source 실질 수정 시 만들거나 갱신한다.
특히 아래 경우에는 생략하지 않는다.

- boot, linker, startup, IPC, interrupt 경로를 실질 수정한다.
- peripheral ownership 또는 pinmux 변경이 코드에 반영된다.
- ISR, ADC trigger, EPWM, CMPSS, XBAR, trip-zone 경로가 바뀐다.
- C28x C++03 제한과 관련된 클래스, 전역 객체, 초기화 순서 계약이 바뀐다.

초기 baseline으로 아래 editable source는 이미 note를 가진다.

- `CPU1/source_editable/main_cpu1.c`
- `CM/source_editable/main_cm.cc`
- `CPU2/source_editable/main_cpu2.c`
- `CPU1/source_editable/pwm.cpp`
- `CPU1/source_editable/epwm_ctrl.cpp`
- `CPU1/source_editable/ctrl_loop.cpp`
- `CPU1/source_editable/pinmux.c`

## Plan note 생성 조건

`sdd/plans/`는 기능별 spec보다 상위의 작업 분해와 장기 결정을 남길 때 사용한다.

- 여러 source file과 architecture note를 동시에 건드리는 작업
- EPWM, ADC, CMPSS/TZ처럼 bench 검증이 큰 주변장치 bring-up
- core ownership, boot flow, IPC routing 재분배
- 서브에이전트 또는 사람에게 작업을 분배하기 전 경계 고정

## 링크 규칙

- SDD 내부 링크는 기본적으로 Markdown 상대경로 링크를 쓴다.
- Obsidian wikilink `[[...]]`는 vault root와 파일명 충돌 설정에 따라 새 문서를 만들 수 있으므로 사용하지 않는다.
- 넓은 관련성, backlog, future work, historical context는 plain text path나 inline code로 남긴다.
- 모든 문서에 전역 허브 링크를 반복하지 않는다.
- code note처럼 파일명에 `.c.md`, `.cc.md`, `.cpp.md`가 들어가는 문서는 반드시 실제 파일명까지 포함한 상대경로로 링크한다.

## 이름 규칙

- 파일명은 소문자 kebab-case를 기본으로 한다.
- 기능 spec은 번호와 기능명을 함께 쓴다.
- 아키텍처 문서는 긴 설명보다 책임을 드러내는 이름을 쓴다.
- 예: `boot-flow.md`, `ipc-routing.md`, `multicore-ownership.md`, `memory-map.md`
