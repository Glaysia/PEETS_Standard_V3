# Plan Note Index

큰 bring-up, 리팩터링, 주변장치 통합은 여기서 시작한다.
상위 허브는 [sdd-index](../sdd-index.md), 템플릿은 [plan-note](../templates/plan-note.md)다.

## 작성 조건

- CPU1, CPU2, CM 사이 boot/release 흐름이 바뀐다.
- IPC MSGRAM, flag, timeout, routing 계약이 바뀐다.
- EPWM, ADC trigger, CMPSS, XBAR, trip-zone 같은 hardware-facing 기능을 붙인다.
- peripheral ownership, CPUSEL, pinmux, linker, startup, interrupt vector를 건드린다.
- 한 번에 여러 소스 파일과 검증 절차가 묶이는 작업이다.

## 현재 계획 후보

- `docs/specs/002-cm-uarta-hello/`: CM UART TX/RX scope bring-up
- `docs/specs/003-cpu1-cpu2-handshake/`: CPU1이 CPU2를 release하고 MSGRAM token 왕복 확인
- `docs/specs/004-epwm-scope-smoke/`: EPWM1~12 무전력 scope smoke
- `docs/specs/005-adc-trigger-smoke/`: EPWM SOCA/SOCB 기반 ADC trigger smoke
- `docs/specs/006-cmpss-tz-protection-smoke/`: CMPSS/DAC -> XBAR -> TZ/DC 보호 smoke

## 운영 규칙

- 기능별 검증은 `docs/specs/NNN-short-name/`에 둔다.
- 장기 구조가 바뀌면 관련 [architecture-index](../architecture/architecture-index.md) 문서를 같은 변경에서 갱신한다.
- code note는 실제 영향 받는 소스 파일에만 만든다.
- 구현이 끝나면 해당 `verification.md`에 실제 관측 결과를 남긴다.
