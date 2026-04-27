# Source Note Template

이 템플릿은 핵심 소스 파일을 실질 수정할 때만 사용한다.
모든 파일에 1:1 source note를 강제하지 않는다.

## 소스 경로

- path:
- project: `CPU1` / `CPU2` / `CM`
- language: `C` / `C++`

## 단일 책임

- 이 파일이 맡는 책임:
- 이 파일이 맡지 않는 책임:

## 실행 코어와 초기화 순서

- 실행 코어:
- 호출 위치:
- 권장 흐름:
- 선행 조건:
- 후행 조건:

## 주요 입력과 출력

- 입력:
- 출력:
- shared state:
- 외부 관측값:

## Hardware / Driverlib 의존성

- peripheral:
- register 또는 driverlib API:
- CPUSEL / pinmux / SysConfig 의존성:
- clock source:

## Memory / Startup / Linker 의존성

- section:
- linker command file:
- startup/vector 의존성:
- IPC MSGRAM 의존성:

## Interrupt / Trigger / Timing

- ISR:
- trigger source:
- worst-case 또는 bounded 조건:
- background와 공유하는 데이터:
- 동기화 방식:

## 핵심 invariant

- invariant 1:
- invariant 2:
- invariant 3:

## Fail-fast / 실패 처리

- 실패 조건:
- 시스템 동작:
- 후속 기능 차단 조건:
- debug 관측 방법:

## 관련 문서

- 기능 spec:
- architecture:
- board reference:
- TI 또는 C2000Ware 예제:

## 관련 테스트와 검증

- bench 절차:
- 기대 관측값:
- 성공 조건:
- 실패 시 확인 항목:

## 변경 시 주의점

- boot, clock, linker, startup, IPC를 동시에 바꾸지 않는다.
- 생성 폴더와 CCS 산출물을 직접 수정하지 않는다.
- C28x 쪽은 예외, RTTI, 동적 메모리, virtual, global constructor side effect를 도입하지 않는다.
- ISR 경로에는 blocking wait, 긴 spin, logging, `printf`를 넣지 않는다.

