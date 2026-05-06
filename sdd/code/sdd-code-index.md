# Code Note Index

이 문서는 소스 코드와 직접 대응되는 SDD note의 진입점이다.
상위 허브는 [sdd-index](../sdd-index.md)다.

## 경로 규칙

- 정규 규칙: `sdd/code/<repo-relative-source-path>.md`
- 예시:
  - `CPU1/source_editable/main_cpu1.c` -> `sdd/code/CPU1/source_editable/main_cpu1.c.md`
  - `CM/source_editable/main_cm.cc` -> `sdd/code/CM/source_editable/main_cm.cc.md`
  - `CPU2/source_editable/main_cpu2.c` -> `sdd/code/CPU2/source_editable/main_cpu2.c.md`

## 작성 대상

- `source_editable/`와 `include_editable/`에서 새로 만들거나 실질 수정하는 파일
- boot, clock, IPC, linker, startup, interrupt, EPWM, ADC, CMPSS, XBAR, trip-zone 경로를 직접 바꾸는 파일
- C28x C++03 정책과 초기화 순서 계약을 가진 파일

## 제외 대상

- `device_not_editable/` 원본 성격 파일
- `CPU1_RAM`, `CPU2_RAM`, `CM_RAM` 같은 CCS 생성 폴더
- untouched legacy 파일과 단순 reference 문서

## 필수 내용

- source path와 실행 core
- 단일 책임과 비책임
- 초기화 순서와 선행/후행 조건
- hardware, driverlib, pinmux, CPUSEL 의존성
- MSGRAM, linker section, startup/vector 의존성
- ISR, trigger, timing, shared state 계약
- debug 관측값과 bench 성공 조건
- 변경 시 같이 갱신해야 하는 spec 또는 architecture note

템플릿은 [source-note](../templates/source-note.md)를 사용한다.

## 현재 Code Notes

- [CPU1 main_cpu1.c](CPU1/source_editable/main_cpu1.c.md)
- [CM main_cm.cc](CM/source_editable/main_cm.cc.md)
- [CPU2 main_cpu2.c](CPU2/source_editable/main_cpu2.c.md)
- [CPU1 pwm.cpp current](CPU1/source_editable/pwm.cpp.md)
- [CPU1 epwm_ctrl.cpp planned](CPU1/source_editable/epwm_ctrl.cpp.md)
- [CPU1 ctrl_loop.cpp planned](CPU1/source_editable/ctrl_loop.cpp.md)
- [CPU1 pinmux.c](CPU1/source_editable/pinmux.c.md)

## 운영 메모

- 이 인덱스는 전체 코드 백필 목록이 아니다.
- 앞으로 실질 수정하는 editable source부터 대응 note를 늘린다.
- 아직 source file이 없는 planned split note는 활성 plan이 직접 가리키는 경우에만 허용한다.
- `epwm_ctrl.cpp.md`, `ctrl_loop.cpp.md`는 [epwm-control-source-split](../plans/epwm-control-source-split.md) 계획에 묶인 planned note다.
