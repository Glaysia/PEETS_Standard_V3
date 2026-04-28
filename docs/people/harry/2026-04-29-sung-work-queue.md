# 2026-04-29 성훈 작업 큐

오늘 CPU1/CPU2/CM 세 코어 동작 확인 결과를 기준선으로 둔다. 내일 작업은 아래 3개 묶음으로 나누고, 성훈은 이를 보고 `docs/people/sung/TODO.md`에 당일 실행 계획과 검증 결과를 자체 분해해서 남긴다.

## 1. 실보드 준비와 리팩토링 전 기준선 검증

- 실보드 전원 인가 전 임시 전원 인터페이스를 만든다. 아직 인터페이스 보드가 없으므로 만능기판에 SMPS용 단자와 캐패시터를 구성한다.
- 임시 연결선으로 전원을 넣기 전에 극성, 전압, GND 공통, 단락 여부를 확인한다.
- 리팩토링 전에 오늘 CPU1/CPU2/CM 세 코어 테스트 코드가 실보드에서 그대로 도는지 확인한다.
- 실보드 정보를 취합한다. 보드 revision, 실장 상태, 커넥터/계측 포인트, EV 보드와 다른 핀/버퍼/전원 enable 조건을 기록한다.
- 새 컨트롤보드 schematic PDF를 찾아서 문서 자료로 추가할 준비를 한다.

## 2. Intercore/통신 소스 분리와 재검증

- Intercore 소스는 우선 C 모듈로 분리한다. CPU1/CPU2의 boot/release, MSGRAM token, status latch, timeout 관측 코드를 담는다. 기준 문서는 `sdd/architecture/intercore-source-split.md`다.
- Intercore 리팩토링에서 CPU1/CPU2 `.c` 파일을 `.cc`로 바꾸지 않는다.
- 통신용 소스 이름은 `comm_cm`으로 고정한다. `CM/source_editable/comm_cm.cc`, `CM/include_editable/comm_cm.h`에 CM UART smoke 코드와 향후 UART loopback/PC serial 확인 코드를 담는다. 기준 문서는 `sdd/architecture/comm-cm-source-split.md`다.
- 리팩토링 뒤에는 EV 보드와 실보드 양쪽에서 CPU1/CPU2/CM 기준 테스트가 다시 도는지 확인한다.

## 3. 보드 I/O 확장과 EPWM EV 보드 테스트

- EV 보드와 실보드 교차 테스트 체크리스트를 만든다.
- 버퍼 EN/OE용 GPIO 코드를 작성하고 EV 보드와 실보드에서 실제 enable 동작을 확인한다.
- EPWM은 `sdd/architecture/epwm-bringup-boundary.md` 기준으로 활성화하고 먼저 EV 보드에서 scope 테스트한다.
- buffer enable과 safe-off 조건이 확인되기 전에는 전력부 실험으로 넘어가지 않는다.
- 위 작업은 기능별로 쪼개고, 각 항목마다 검증 방법과 성공 조건을 기록한다.
