# CPU1 source_editable/pwm.cpp

## 소스 경로

- path: `CPU1/source_editable/pwm.cpp`
- project: `CPU1`
- language: `C++`

## 단일 책임

- 현재는 C28x C++ 빌드와 C ABI 호출을 확인하는 PWM smoke test 파일이다.
- 향후 EPWM driverlib 기반 PWM bank 구현의 후보 파일이다.
- 현재 파일은 실제 EPWM register 설정, pinmux, trip-zone, ADC trigger를 수행하지 않는다.

## 실행 코어와 초기화 순서

- 실행 코어: `CPU1`
- 호출 위치: `CPU1/source_editable/main_cpu1.c`의 `pwm_test_run(1U)`
- 현재 흐름: seed 값을 가진 stack 객체 생성, `step()`, 값 반환
- 선행 조건: CPU1 C/C++ mixed build가 정상이어야 한다.
- 후행 조건: `g_pwm_smoke_value`가 seed+1 값을 받아야 한다.

## 주요 입력과 출력

- 입력: `uint16_t seed`
- 출력: `uint16_t` smoke result
- shared state: 없음
- 외부 관측값: CPU1 debugger에서 `g_pwm_smoke_value`

## Hardware / Driverlib 의존성

- peripheral: 현재 없음
- driverlib/API: 현재 없음
- CPUSEL / pinmux / SysConfig 의존성: 실제 EPWM 구현 전까지 없음
- clock source: 현재 없음

## Memory / Startup / Linker 의존성

- section: 기본 code/data section
- linker command file: CPU1 linker command file의 C++ runtime 지원에 의존
- startup/vector 의존성: 없음
- IPC MSGRAM 의존성: 없음

## Interrupt / Trigger / Timing

- ISR: 없음
- trigger source: 없음
- bounded 조건: deterministic stack-only smoke function
- background와 공유하는 데이터: 없음
- 동기화 방식: 없음

## 핵심 invariant

- C ABI 함수는 `extern "C"`로 유지한다.
- C28x C++03 정책을 따른다.
- 생성자/소멸자에서 hardware side effect를 만들지 않는다.

## Fail-fast / 실패 처리

- 실패 조건: C/C++ mixed build 실패 또는 반환값 mismatch
- 시스템 동작: CPU1 bring-up 초기에 smoke 변수로 확인
- 후속 기능 차단 조건: C++ ABI 문제가 있으면 EPWM C++ wrapper 구현을 진행하지 않는다.
- debug 관측 방법: `g_pwm_smoke_value` 확인

## 관련 문서

- architecture:
  - [multicore-ownership](../../../architecture/multicore-ownership.md)
- board reference: [pwm-architecture](../../../../docs/board/pwm-architecture.md)
- code collaborators:
  - [CPU1 main_cpu1.c](main_cpu1.c.md)
  - [CPU1 pinmux.c](pinmux.c.md)

## 관련 테스트와 검증

- bench 절차: CPU1 build/run 후 `g_pwm_smoke_value == 2` 확인
- 기대 관측값: CPU1 main이 smoke call 이후 heartbeat까지 진행
- 성공 조건: C/C++ link 문제 없이 CPU1이 main loop에 진입
- 실패 시 확인 항목: `.c`/`.cpp` language mode, name mangling, compiler 설정

## 변경 시 주의점

- 실제 EPWM 구현으로 전환할 때 `docs/board/pwm-architecture.md`의 public API와 safe-off-first 규칙을 따른다.
- EPWM register write, ADC trigger, trip-zone을 한 번에 모두 붙이지 않는다.
- dynamic allocation, RTTI, exceptions, virtual function, global constructor side effect를 도입하지 않는다.
