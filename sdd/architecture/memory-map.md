# Memory Map

이 문서는 linker command file, MSGRAM section, startup/vector 변경 시 확인할 기준을 정한다.

## Boundary

- 이 문서는 초기 bring-up에서 직접 의존하는 memory section과 변경 주의점을 다룬다.
- 전체 linker script 해설이나 TI 원본 memory map 백필은 하지 않는다.

## Current Baseline

- 각 프로젝트의 linker command file은 프로젝트 루트에 둔다.
- RAM/FLASH linker command file 모두 MSGRAM section 계약을 맞춰야 한다.
- CPU1/CPU2 C28x MSGRAM:
  - `MSGRAM_CPU1_TO_CPU2`
  - `MSGRAM_CPU2_TO_CPU1`
  - `MSGRAM_CPU_TO_CM`
  - `MSGRAM_CM_TO_CPU`
- CM MSGRAM:
  - `MSGRAM_CPU1_TO_CM`
  - `MSGRAM_CM_TO_CPU1`
  - `MSGRAM_CPU2_TO_CM`
  - `MSGRAM_CM_TO_CPU2`

## Invariants

- `#pragma DATA_SECTION`의 section 이름과 linker command file section 이름은 일치해야 한다.
- MSGRAM mailbox는 초기 bring-up에서 `NOINIT` section에 둔다.
- startup code와 interrupt vector 배치는 근거 없이 바꾸지 않는다.
- linker command file 위치는 프로젝트 루트에 둔다.

## Related Code Notes

- [CPU1 main_cpu1.c](../code/CPU1/source_editable/main_cpu1.c.md)
- [CM main_cm.cc](../code/CM/source_editable/main_cm.cc.md)
- [CPU2 main_cpu2.c](../code/CPU2/source_editable/main_cpu2.c.md)

## 변경 시 주의점

- RAM build와 FLASH build 양쪽 linker command file을 같이 확인한다.
- section 이름 변경은 source, linker, architecture note, 기능 spec을 같은 변경 단위로 묶는다.
- startup/vector를 바꾸는 작업은 interrupt, ISR, boot-flow spec과 분리해 검증한다.
