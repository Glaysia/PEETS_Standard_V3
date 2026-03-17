# PEETS_Standard_V3 Agent Notes

## 목적
- 이 저장소는 F28388D용 CCS/Eclipse 3프로젝트 워크스페이스다.
- 문서 목적은 에이전트나 개발자가 무엇부터 bring-up 해야 하는지, 무엇을 함부로 바꾸면 안 되는지 빠르게 판단하게 만드는 것이다.

## 워크스페이스 역할 분담
- `CPU1`: 시스템 마스터. 부팅, 클럭, 공용 GPIO, 메모리, 주변장치 초기화, IPC 라우팅을 맡는다.
- `CPU2`: 타이밍 민감 제어. 빠른 ISR, EPWM/ECAP/ADC 트리거 기반 제어 루프를 맡는다.
- `CM`: UART/CAN/Ethernet/USB 등 통신, 게이트웨이, 진단, 로그 같은 비실시간 기능을 맡는다.
- 실제 주변장치 ownership은 `CPUSEL`, pinmux, SysConfig 결과를 기준으로 확인한다.

## 기본 작업 규칙
- 이 워크스페이스는 CCS/Eclipse 프로젝트 파일(`.project`, `.cproject`)을 사용한다. 요청이 없으면 새 빌드 시스템을 도입하지 않는다.
- 링크 커맨드 파일(`*.cmd`)은 각 프로젝트 루트에 둔다. CCS 설정이 이 위치를 전제로 한다.
- 생성 폴더(`CPU1_RAM`, `CPU2_RAM`, `CM_RAM`)와 그 아래 산출물은 CCS가 관리한다. 직접 수정하지 않는다.
- `.settings` 파일은 사용자 환경 의존 가능성이 크다. 꼭 필요할 때만 변경한다.
- `.gitignore`에 맞춰 생성 파일과 빌드 산출물을 취급한다.
- `.c`를 `.cc`로, 또는 `.cc`를 `.c`로 바꾸지 않는다. 언어 모드 차이를 검증한 경우만 예외다.
- C와 C++ 소스는 기존 레이아웃을 유지한다. C28x 툴체인에서 언어 혼합은 바로 빌드 문제로 이어진다.

## 검색 도구 규칙
- 이 환경에서는 `RIPGREP_CONFIG_PATH`가 CCS가 만든 잘못된 ripgrep 설정 파일을 가리킬 수 있다.
- 그 상태에서는 `rg pattern path` 형태의 기본 검색이 깨져서 패턴을 파일명처럼 해석할 수 있다.
- `rg` 사용 시 기본 명령은 항상 `env -u RIPGREP_CONFIG_PATH rg ...` 형태로 실행한다.
- 검색 실패가 이상하면 먼저 `printf '%s\n' "$RIPGREP_CONFIG_PATH"`로 환경변수를 확인한다.

## Bring-up 순서
- 1단계는 `CPU1` 단독 부팅 확인이다.
- 이 단계에서 먼저 클럭, watchdog, GPIO 기본 상태, 타이머 또는 heartbeat를 확인한다.
- 2단계는 `CPU1 -> CM` boot/release와 최소 핸드셰이크 확인이다.
- 이 단계에서 `MSGRAM` 또는 `IPC`로 단순 플래그 하나만 왕복시키는 수준까지 먼저 고정한다.
- 3단계는 `CM UART`다.
- `CM UART`는 `CPU1`이 `CM`을 정상적으로 깨우고 통신 가능한 상태라는 전제가 확인된 뒤에 붙인다.
- 4단계부터 필요한 주변장치를 예제 기반으로 하나씩 적층한다.
- 초기 bring-up에서는 여러 기능을 동시에 합치지 않는다.
- 원칙은 "예제 1개당 검증 포인트 1개"다. 한 단계에서 성공 조건이 하나만 보이게 만든다.

## 예제 적층 규칙
- 새 기능은 가능하면 CCS 예제 하나를 기준으로 가져온다.
- 기능 추가 시 아래 3가지를 함께 남긴다.
- 사용한 CCS 예제
- 실제 검증 방법
- 성공 조건
- 새 기능은 가능하면 독립 커밋 또는 독립 테스트 단위로 유지한다.
- 예제를 가져온 뒤에는 보드 핀, ownership, clock source, interrupt 연결만 최소 수정부터 한다.
- 예제 여러 개를 바로 합치지 않는다. 개별 검증 후 통합한다.

## 핀과 주변장치 ownership
- pin 설정 전에 `CPUSEL`, pinmux, SysConfig 결과를 먼저 확인한다.
- `CM UART`와 C28x `SCI`를 혼동하지 않는다. 이름이 비슷해도 코어와 레지스터 세트가 다르다.
- 핀 관련 기준 문서는 `sysconfig/`와 프로젝트 메모다.
- 하드웨어에 실제로 연결되지 않은 핀이나 reserved 기능은 문서 확인 전 변경하지 않는다.
- EtherCAT, Ethernet 같은 고정 배선 기능은 관련 문서 확인 없이 핀을 재할당하지 않는다.

## 변경 금지 또는 주의 항목
- 부트 플로우는 근거 없이 바꾸지 않는다.
- linker command file 배치는 근거 없이 바꾸지 않는다.
- startup 코드와 인터럽트 벡터 배치는 근거 없이 바꾸지 않는다.
- IPC message RAM section 배치는 근거 없이 바꾸지 않는다.
- 초기 단계에서는 boot, clock, linker, startup, IPC를 동시에 수정하지 않는다. 문제 원인 분리가 불가능해진다.

## C28x C++03 정책
### 적용 범위
- F28388D의 C28x 툴체인으로 빌드되는 `CPU1`/`CPU2` 코드 전체에 적용한다.

### 핵심 원칙
- C++03은 사실상 "C-with-classes" 수준으로만 사용한다.
- 클래스는 zero-overhead 정리 수단으로만 허용한다.
- 하드웨어 접근 부작용은 숨기지 말고, 명시적 초기화 경로에서만 실행한다.

### 금지 사항
- 예외와 RTTI 금지: `throw`, `try/catch`, `dynamic_cast`, `typeid`
- 동적 메모리 금지: `new`, `delete`, `new[]`, `delete[]`
- 가상 함수와 런타임 다형성 금지
- iostream 등 무거운 표준 라이브러리 사용 금지
- 전역 생성자 기반 초기화 금지
- 파일 스코프 객체가 레지스터 쓰기, IPC, peripheral init 같은 side effect를 가지면 안 된다

### 허용 범위
- `namespace`, `enum`, `struct`, 제한된 `class`
- header의 `static inline` wrapper
- 단순하고 코드 크기 폭증을 만들지 않는 템플릿
- 의도가 명확한 함수 오버로딩

### 클래스 사용 규칙
- 생성자와 소멸자에서 하드웨어를 건드리지 않는다.
- 하드웨어 side effect는 `init()` / `deinit()` / `enable()` / `disable()` 같은 명시적 함수에 둔다.
- 가능하면 instance 없는 wrapper를 선호한다.
- instance가 꼭 필요하면 POD에 가까운 형태로 두고 `main()` 또는 지정된 init 단계에서 명시적으로 초기화한다.

### 초기화 규칙
- 모든 초기화는 중앙에서 순서대로 호출한다.
- 권장 흐름은 `SystemInit() -> BoardInit() -> AppInit()` 이다.
- global constructor로 암묵 초기화하지 않는다.
- init order dependency가 있으면 호출 지점에 드러나게 남긴다.

### 실시간 안전 규칙
- ISR 경로는 bounded and predictable 해야 한다.
- ISR에서 blocking wait나 긴 spin을 넣지 않는다.
- ISR에서 logging/`printf`를 하지 않는다.
- ISR과 background 사이 공유 데이터는 `volatile`, critical section, ring buffer 등 명시적 동기화 수단으로 다룬다.

### 권장 wrapper 패턴
```cpp
struct Epwm1
{
    static inline void init()
    {
        // EALLOW; configure regs; EDIS;
    }

    static inline void set_cmpa(uint16_t v)
    {
        // EPwm1Regs.CMPA.bit.CMPA = v;
    }
};
```

## 검토 기준
- 처음 보는 엔지니어가 이 문서를 2분 내에 읽고 첫 bring-up 순서를 말할 수 있어야 한다.
- "CM UART부터 바로 붙여도 되나?"라는 질문에 대해 문서만 보고 "아니오, `CPU1 -> CM` 핸드셰이크 확인 후 UART"라고 답할 수 있어야 한다.
