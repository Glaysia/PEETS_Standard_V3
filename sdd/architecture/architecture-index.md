# Architecture Index

이 문서는 PEETS_Standard_V3에서 장기적으로 관리할 아키텍처 문서 후보와 갱신 조건을 정한다.

## 목적

- bring-up 단계에서 바뀌면 위험한 구조 결정을 한곳에서 찾게 한다.
- 기능별 spec이 끝난 뒤에도 남아야 하는 boot, ownership, IPC, memory 기준을 보존한다.
- CPU1, CPU2, CM 역할 분담과 CCS 프로젝트 구조를 문서화한다.

## 우선 문서

| 문서 | 목적 | 생성 또는 갱신 조건 |
| --- | --- | --- |
| [boot-flow](boot-flow.md) | CPU1 단독 부팅, CPU2/CM release, handshake 순서 | boot mode, release sequence, boot-ready flag 변경 |
| [multicore-ownership](multicore-ownership.md) | CPU1/CPU2/CM 역할과 peripheral ownership | CPUSEL, pinmux, SysConfig 결과, ownership 변경 |
| [ipc-routing](ipc-routing.md) | CPU 간 IPC flag, MSGRAM, handshake, timeout 구조 | IPC flag 번호, MSGRAM section, routing 변경 |
| [memory-map](memory-map.md) | linker command file과 section 배치 기준 | `*.cmd`, MSGRAM, startup section 변경 |
| [intercore-source-split](intercore-source-split.md) | CPU1/CPU2 intercore C 모듈 분리 기준 | boot/release, MSGRAM token, status latch 코드 분리 |
| [comm-cm-source-split](comm-cm-source-split.md) | CM 통신 C++ 모듈 `comm_cm` 분리 기준 | UART/CAN/Ethernet/USB 진단 통신 코드 분리 |
| [epwm-bringup-boundary](epwm-bringup-boundary.md) | EPWM 무전력 scope smoke와 모듈 분리 전 경계 | EPWM1~12 출력, safe-off, ownership, ADC/CMPSS 연계 전제 변경 |
| `ccs-project-layout.md` | CCS/Eclipse 프로젝트 구조와 tool discovery 기준 | `.project`, `.cproject`, compiler/product 기준 변경 |

## 현재 기준

- CPU1은 시스템 마스터이며 boot, clock, 공용 GPIO, 메모리, 주변장치 초기화, IPC 라우팅을 맡는다.
- CPU2는 타이밍 민감 제어와 빠른 ISR, EPWM/ECAP/ADC trigger 기반 제어 루프를 맡는다.
- CM은 UART/CAN/Ethernet/USB 등 통신, 게이트웨이, 진단, 로그 같은 비실시간 기능을 맡는다.
- 실제 peripheral ownership은 `CPUSEL`, pinmux, SysConfig 결과를 기준으로 확인한다.

## 갱신 규칙

- 기능별 spec에서 장기 구조가 바뀌면 해당 architecture 문서를 같은 변경 안에서 갱신한다.
- 초기 bring-up에서는 boot, clock, linker, startup, IPC 변경을 한 architecture 문서에서 한꺼번에 정당화하지 않는다.
- 아직 검증되지 않은 설계는 `PENDING` 또는 `ASSUMPTION`으로 표시한다.
- 실제 보드 검증 결과는 기능별 `verification.md`에 남기고, architecture 문서에는 안정된 기준만 승격한다.
- source file 책임이 바뀌면 관련 [sdd-code-index](../code/sdd-code-index.md) note도 같이 갱신한다.

## 비대상

- 개별 함수 구현 세부사항
- CCS가 생성한 산출물
- 일회성 실험 로그
- 검증 전 임시 pin reassignment
