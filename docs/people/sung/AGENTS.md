# Sung Folder Agent Rules

## 목적

- 이 폴더는 Sung 담당자의 사람 전용 온보딩 문서 영역이다.
- 에이전트는 이 폴더의 문서를 읽고 안내에 참고할 수 있지만, 이 폴더 아래 파일을 수정하지 않는다.

## 읽기 전용 규칙

- 에이전트는 `docs/people/sung/**` 아래 파일을 생성, 수정, 삭제하지 않는다.
- `README.md`, `TODO.md`, `AGENTS.md`는 사람이 직접 관리한다.
- `TODO.md` 체크박스도 사람이 직접 수정한다.
- 사용자가 이 폴더 수정을 요청해도, 먼저 상위 작업자가 명시적으로 허용했는지 확인한다.

## 작업 기록 위치

- 기능 구현 계획과 검증 결과는 이 폴더가 아니라 `docs/specs/NNN-short-name/` 아래에 남긴다.
- 실제 bench 결과는 해당 기능의 `verification.md`에 남긴다.
- CCS 설치나 툴 설정 기준은 `docs/ti/ccs-manual-setup.md`를 우선한다.

## 상위 규칙

- 저장소 루트의 `AGENTS.md`가 이 폴더에도 적용된다.
- bring-up 순서는 `CPU1` 단독 부팅, `CPU1 -> CM` 핸드셰이크, `CM UART`, 주변장치 순서를 따른다.
- 초기 단계에서는 boot, clock, linker, startup, IPC를 동시에 수정하지 않는다.
- pin 설정 전에는 `CPUSEL`, pinmux, SysConfig 결과를 먼저 확인한다.
- C28x 코드에서는 루트 `AGENTS.md`의 C++03 정책을 따른다.

## 검색 규칙

이 환경에서는 `RIPGREP_CONFIG_PATH`가 CCS가 만든 잘못된 ripgrep 설정 파일을 가리킬 수 있다.

검색할 때는 아래 형식을 사용한다.

```bash
env -u RIPGREP_CONFIG_PATH rg <pattern> <path>
```
