# Multicore Ownership

이 문서는 CPU1, CPU2, CM 역할과 peripheral ownership 판단 기준을 고정한다.

## Boundary

- 이 문서는 역할과 ownership 기준을 다룬다.
- 실제 register 설정은 기능별 spec과 code note에서 다룬다.
- 최종 판단은 `CPUSEL`, pinmux, SysConfig 결과, 보드 배선 문서가 기준이다.

## Core Roles

- `CPU1`: system master. boot, clock, 공용 GPIO, pinmux, safe default, CPU2/CM release, IPC routing, supervisor를 맡는다.
- `CPU2`: fast control core. 빠른 ISR, EPWM/ADC result 처리, phase-shift 또는 duty update를 맡는다.
- `CM`: non-realtime communication core. UART/CAN/Ethernet/USB, gateway, diagnostics, log를 맡는다.

## Peripheral Baseline

- EPWM1~12 핀은 현재 board reference 기준 GPIO0~23에 열려 있다.
- CM UARTA는 GPIO84/85를 기준으로 한다.
- C28x SCI와 CM UART는 서로 다른 peripheral로 취급한다.
- EtherCAT/Ethernet처럼 고정 배선 기능은 관련 문서와 실장 상태 확인 없이 pin 재할당하지 않는다.

## Invariants

- CPU1-only GPIO control register 설정은 CPU1 경로에서 수행한다.
- CPU2가 fast control을 맡더라도 CPU1의 safe enable과 fault supervisor 책임은 유지한다.
- CM 통신 실패가 power-stage fast loop를 멈추는 구조는 만들지 않는다.
- peripheral ownership 변경은 `docs/board/board-io-reference.md`와 SysConfig 결과를 먼저 확인한다.

## Related Code Notes

- [CPU1 pinmux.c](../code/CPU1/source_editable/pinmux.c.md)
- [CPU1 pwm.cpp](../code/CPU1/source_editable/pwm.cpp.md)
- [CPU2 main_cpu2.c](../code/CPU2/source_editable/main_cpu2.c.md)
- [CM main_cm.cc](../code/CM/source_editable/main_cm.cc.md)

## 변경 시 주의점

- EPWM/ADC/CMPSS ownership을 CPU1에서 CPU2로 재분배하면 별도 plan/spec이 필요하다.
- pinmux를 바꾸는 작업은 보드 문서와 실제 scope/logic analyzer 관측을 함께 남긴다.
- CM UART 작업에서는 GPIO84/85와 SCIA/SCIB 핀을 혼동하지 않는다.
