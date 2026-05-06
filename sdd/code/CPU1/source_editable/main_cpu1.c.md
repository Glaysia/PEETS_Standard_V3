# CPU1 source_editable/main_cpu1.c

## 소스 경로

- path: `CPU1/source_editable/main_cpu1.c`
- project: `CPU1`
- language: `C`

## 단일 책임

- CPU1의 초기 bring-up 오케스트레이션을 맡는다.
- 현재 책임은 `Device_init()`, C++ PWM smoke 호출, CPU1 heartbeat GPIO 초기화, CPU1-CM release/handshake다.
- 이 파일은 CM UART register 설정, CPU2 fast ISR, 제품용 PWM/ADC/CMPSS profile 구현을 맡지 않는다.

## 실행 코어와 초기화 순서

- 실행 코어: `CPU1`
- 호출 위치: CPU1 reset 후 `main()`
- 현재 흐름: `Device_init() -> pwm_test_run() -> cpu1_init_heartbeat() -> cpu1_run_cm_handshake() -> heartbeat loop`
- 선행 조건: CPU1 RAM 또는 FLASH image가 CCS에서 정상 load/run 되어야 한다.
- 후행 조건: CM handshake 상태가 `g_cm_handshake_status`에 latch되고 CPU1 heartbeat가 유지되어야 한다.

## 주요 입력과 출력

- 입력: CM ACK mailbox 값, compile mode `_FLASH`
- 출력: CPU1 heartbeat GPIO toggle, CM boot-ready token, handshake status latch
- shared state:
  - `g_cpu1_to_cm_mailbox`
  - `g_cm_to_cpu1_mailbox`
  - `g_cm_handshake_status`
  - `g_cm_handshake_poll_count`
- 외부 관측값: heartbeat GPIO, debugger memory window의 MSGRAM 값, status 변수

## Hardware / Driverlib 의존성

- peripheral: GPIO, CM boot controller, CPU-CM MSGRAM
- driverlib/API: `Device_init()`, `Device_bootCM()`, `GPIO_setPinConfig()`, `GPIO_togglePin()`, `DEVICE_DELAY_US()`
- pinmux 의존성: heartbeat는 `DEVICE_GPIO_PIN_LED1`, `DEVICE_GPIO_CFG_LED1` 기준
- clock source: `Device_init()`에서 설정된 CPU1 system clock

## Memory / Startup / Linker 의존성

- section:
  - `MSGRAM_CPU_TO_CM`
  - `MSGRAM_CM_TO_CPU`
- linker command file:
  - `CPU1/2838x_RAM_lnk_cpu1.cmd`
  - `CPU1/2838x_FLASH_lnk_cpu1.cmd`
- startup/vector 의존성: 현재 파일은 interrupt vector를 직접 바꾸지 않는다.
- IPC MSGRAM 의존성: CM 쪽 section 이름과 실제 주소가 대응되어야 한다.

## Interrupt / Trigger / Timing

- ISR: 없음
- trigger source: polling 기반 CM ACK 확인
- bounded 조건: `CM_HANDSHAKE_TIMEOUT_POLLS * CM_HANDSHAKE_POLL_DELAY_US`
- background 공유 데이터: handshake status와 mailbox는 debugger/remote core 관측 대상이다.
- 동기화 방식: 초기 bring-up v1에서는 `volatile` mailbox와 bounded polling

## 핵심 invariant

- CPU1 heartbeat는 CM handshake 성공/실패와 무관하게 유지되어야 한다.
- CM UART 같은 후속 기능은 handshake OK 전에는 enable하지 않는다.
- boot mode, MSGRAM section, timeout 정책을 동시에 바꾸지 않는다.

## Fail-fast / 실패 처리

- 실패 조건: CM ACK token이 timeout 안에 들어오지 않음
- 시스템 동작: `CM_HANDSHAKE_STATUS_TIMEOUT` latch 후 heartbeat loop 유지
- 후속 기능 차단 조건: timeout이면 CM UART bring-up을 진행하지 않는다.
- debug 관측 방법: `g_cm_handshake_status`, `g_cm_handshake_poll_count`, MSGRAM mailbox 값 확인

## 관련 문서

- 기능 spec: `docs/specs/001-cpu1-cm-handshake/`
- architecture:
  - [boot-flow](../../../architecture/boot-flow.md)
  - [ipc-routing](../../../architecture/ipc-routing.md)
  - [memory-map](../../../architecture/memory-map.md)
- code collaborators:
  - [CM main_cm.cc](../../CM/source_editable/main_cm.cc.md)
  - [CPU1 pwm.cpp current](pwm.cpp.md)
  - [CPU1 epwm_ctrl.cpp planned](epwm_ctrl.cpp.md)
  - [CPU1 ctrl_loop.cpp planned](ctrl_loop.cpp.md)

## 관련 테스트와 검증

- bench 절차: CPU1 load/run, CM image 준비, CPU1-CM MSGRAM token 왕복 확인
- 기대 관측값: CPU1 heartbeat 유지, CM ACK token write, CPU1 OK 또는 TIMEOUT latch
- 성공 조건: `g_cm_handshake_status == CM_HANDSHAKE_STATUS_OK`
- 실패 시 확인 항목: CM boot mode, CM image load, MSGRAM section 이름, linker command file

## 변경 시 주의점

- CPU2 release를 추가할 때 CM handshake와 같은 함수에 뒤섞지 말고 별도 단계와 status latch를 둔다.
- CM UART init은 이 파일에 직접 넣지 말고 CM source와 spec에서 다룬다.
- ISR 또는 blocking logging을 heartbeat loop에 넣지 않는다.
