# Agent SDD Workflow

이 문서는 에이전트가 PEETS_Standard_V3에서 코드를 수정하기 전에 따라야 하는 SDD 작업 순서를 정한다.

## 기본 루프

1. `AGENTS.md`를 먼저 읽는다.
2. 작업이 기능 추가나 bring-up이면 `docs/specs/`의 관련 spec을 찾는다.
3. boot, ownership, IPC, memory, interrupt, peripheral 경계가 걸리면 `sdd/architecture/` 문서를 읽는다.
4. 수정할 editable source가 있으면 `sdd/code/<repo-relative-source-path>.md`를 읽거나 만든다.
5. 구현 후 실제 관측 결과를 관련 `verification.md`에 남긴다.

## 코드 수정 전 확인

- CPU1, CPU2, CM 중 어느 core에서 실행되는지 확인한다.
- peripheral ownership은 `CPUSEL`, pinmux, SysConfig 결과로 확인한다.
- `.c`와 `.cc` 확장자는 근거 없이 바꾸지 않는다.
- linker command file, startup, vector, MSGRAM section은 관련 architecture note 없이 바꾸지 않는다.
- `device_not_editable/`는 원본 성격 파일이므로 수정 전 별도 근거를 남긴다.

## SDD 갱신 조건

- 새 기능이면 `docs/specs/NNN-short-name/`를 만든다.
- 핵심 editable source를 실질 수정하면 대응 code note를 만든다.
- 장기 구조가 바뀌면 architecture note를 갱신한다.
- 큰 작업이면 plan note 또는 기능 spec에서 선행 결정을 고정한다.

## 금지 패턴

- boot, clock, linker, startup, IPC를 한 번에 섞어 수정하지 않는다.
- CM UART를 CPU1-CM handshake 검증 전에 붙이지 않는다.
- CPU2 fast control을 CPU1-CPU2 최소 handshake 없이 붙이지 않는다.
- PWM/ADC/CMPSS/TZ를 한 커밋에 처음부터 합치지 않는다.
- ISR 경로에 blocking wait, 긴 spin, logging, `printf`를 넣지 않는다.

## 완료 기준

- 변경한 동작을 debugger, scope, memory window, build result 중 하나 이상으로 검증한다.
- 실패 조건과 확인 항목을 `verification.md` 또는 code note에 남긴다.
- 관련 SDD 링크가 실제 직접 관련 문서만 가리킨다.
