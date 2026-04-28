# CPU2 source_editable/main_cpu2.c

## 소스 경로

- path: `CPU2/source_editable/main_cpu2.c`
- project: `CPU2`
- language: `C`

## 단일 책임

- CPU2 bring-up의 최소 진입점이다.
- 현재 파일은 비어 있는 `main()`만 가지며, 다음 단계에서 CPU2 main 진입 latch와 CPU1-CPU2 handshake를 맡는다.
- 이 파일은 아직 fast ISR, EPWM update, ADC result 처리, 제어 law를 맡지 않는다.

## 실행 코어와 초기화 순서

- 실행 코어: `CPU2`
- 호출 위치: CPU1이 CPU2를 release한 뒤 CPU2 reset vector에서 `main()`
- 권장 흐름: `Device_init() 필요 여부 확인 -> main_entered latch -> CPU1 token 대기 -> ACK write -> heartbeat/tick loop`
- 선행 조건: CPU1 단독 heartbeat와 CPU1 boot/release path가 안정적이어야 한다.
- 후행 조건: CPU1이 CPU2 main 진입과 ACK token을 관측해야 한다.

## 주요 입력과 출력

- 입력: 예정 `MSGRAM_CPU1_TO_CPU2` boot-ready token
- 출력: 예정 `MSGRAM_CPU2_TO_CPU1` ACK token, CPU2 status latch 또는 tick counter
- shared state: 예정 CPU1-CPU2 mailbox
- 외부 관측값: debugger 변수, CPU2 tick counter, 필요 시 GPIO heartbeat

## Hardware / Driverlib 의존성

- peripheral: CPU1-CPU2 MSGRAM, 향후 CPU2 timer/ISR, EPWM/ADC 관련 peripheral
- driverlib/API: CPU2 device init 필요 여부는 CPU2 bring-up spec에서 고정한다.
- CPUSEL / pinmux 의존성: CPU2가 EPWM/ADC를 실제로 소유하기 전까지 pinmux/ownership 변경 금지
- clock source: CPU1이 설정한 system clock과 CPU2 boot frequency 계약

## Memory / Startup / Linker 의존성

- section:
  - `MSGRAM_CPU1_TO_CPU2`
  - `MSGRAM_CPU2_TO_CPU1`
- linker command file:
  - `CPU2/2838x_RAM_lnk_cpu2.cmd`
  - `CPU2/2838x_FLASH_lnk_cpu2.cmd`
- startup/vector 의존성: CPU2 startup/vector는 fast ISR 도입 전까지 건드리지 않는다.
- IPC MSGRAM 의존성: CPU1 linker command file의 CPU1-CPU2 MSGRAM section과 일치해야 한다.

## Interrupt / Trigger / Timing

- ISR: 현재 없음
- trigger source: 예정 CPU1 boot-ready token
- bounded 조건: CPU1 쪽에서 CPU2 ACK timeout을 둔다.
- background와 공유하는 데이터: CPU2 status latch, mailbox, tick counter
- 동기화 방식: 초기 bring-up v1에서는 `volatile` mailbox polling

## 핵심 invariant

- CPU2 fast ISR은 CPU1-CPU2 handshake 성공 전에는 만들지 않는다.
- EPWM/ADC/CMPSS ownership은 `CPUSEL`과 SysConfig 결과 확인 전에는 바꾸지 않는다.
- CPU2 코드에서 C28x C++03 금지 사항을 우회하지 않는다.

## Fail-fast / 실패 처리

- 실패 조건: CPU2 main 진입 또는 ACK token 관측 실패
- 시스템 동작: CPU1이 CPU2 timeout latch를 남기고 후속 fast control enable을 막아야 한다.
- 후속 기능 차단 조건: CPU2 handshake 실패 시 PWM/ADC runtime update를 CPU2에 맡기지 않는다.
- debug 관측 방법: CPU2 status 변수, CPU1-CPU2 MSGRAM, CPU1 timeout latch 확인

## 관련 문서

- 예정 기능 spec: `docs/specs/003-cpu1-cpu2-handshake/`
- architecture:
  - [boot-flow](../../../architecture/boot-flow.md)
  - [ipc-routing](../../../architecture/ipc-routing.md)
  - [multicore-ownership](../../../architecture/multicore-ownership.md)
  - [memory-map](../../../architecture/memory-map.md)
- code collaborators:
  - [CPU1 main_cpu1.c](../../CPU1/source_editable/main_cpu1.c.md)

## 관련 테스트와 검증

- bench 절차: CPU1에서 CPU2 release, CPU2 main 진입 변수 확인, CPU1-CPU2 token 왕복 확인
- 기대 관측값: CPU2 main entered latch, CPU2 ACK token, CPU1 heartbeat 유지
- 성공 조건: 세 core debug attach 시 CPU1/CPU2/CM 상태 변수가 모두 관측됨
- 실패 시 확인 항목: CPU2 image load, boot mode, linker section, CPU2 reset 상태

## 변경 시 주의점

- CPU2를 살리는 첫 변경에서 PWM/ADC ISR까지 같이 넣지 않는다.
- CPU2 heartbeat GPIO를 추가하면 pinmux와 ownership 문서를 먼저 확인한다.
- fast control skeleton은 별도 spec에서 ISR cadence와 shared data 계약을 고정한 뒤 추가한다.
