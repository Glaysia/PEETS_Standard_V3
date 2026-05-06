# Sung Onboarding Tutorial

이 문서는 `PEETS_Standard_V3` 워크스페이스에 처음 들어온 사람이 개발 환경을 만들고, 보드를 한 단계씩 bring-up 하기 위한 초보자용 절차다.

## 0. 먼저 알아야 할 것

이 저장소는 TI F28388D용 CCS/Eclipse 3프로젝트 워크스페이스다.

- `CPU1`: 시스템 마스터. 부팅, 클럭, 공용 GPIO, 메모리, 주변장치 초기화, IPC 라우팅을 맡는다.
- `CPU2`: 타이밍 민감 제어. 빠른 ISR, EPWM/ECAP/ADC 트리거 기반 제어 루프를 맡는다.
- `CM`: UART/CAN/Ethernet/USB 등 통신, 게이트웨이, 진단, 로그 같은 비실시간 기능을 맡는다.

처음 작업할 때는 기능을 한꺼번에 붙이지 않는다. 항상 아래 순서로 하나씩 확인한다.

1. `CPU1` 단독 부팅 확인
2. `CPU1 -> CM` boot/release와 최소 핸드셰이크 확인
3. `CM UART` 확인
4. 필요한 주변장치를 CCS/C2000Ware 예제 기반으로 하나씩 추가

기준 문서:

- [전체 에이전트/작업 규칙](../../../AGENTS.md)
- [CCS 수동 설정](../../ti/ccs-manual-setup.md)
- [spec 문서 작성 규칙](../../specs/README.md)
- [보드 IO 기준](../../board/board-io-reference.md)

## 1. GitHub 계정 만들기

1. GitHub에 가입한다.
2. 회사 또는 프로젝트에서 사용할 이메일을 계정에 등록한다.
3. 프로필 이름과 이메일이 실제 작업자를 구분할 수 있게 설정되어 있는지 확인한다.
4. 저장소 접근 권한을 받는다.

처음에는 fork와 개인 branch에서만 작업한다. 원본 저장소의 main branch에 직접 push하지 않는다.

## 2. Git 설치와 기본 설정

Windows 기준:

1. Git for Windows를 설치한다.
2. 설치 후 `Git Bash` 또는 `PowerShell`을 연다.
3. 사용자 정보를 설정한다.

```bash
git config --global user.name "Your Name"
git config --global user.email "your-email@example.com"
git config --global init.defaultBranch main
```

확인:

```bash
git config --global --list
```

## 3. GitHub fork, clone, branch

1. GitHub에서 원본 저장소를 fork한다.
   - 원본 저장소: https://github.com/Glaysia/PEETS_Standard_V3
2. 자기 fork 주소를 복사한다.
3. 작업 PC에 clone한다.

```bash
git clone <your-fork-url>
cd PEETS_Standard_V3
```

원본 저장소를 `upstream`으로 등록한다.

```bash
git remote add upstream https://github.com/Glaysia/PEETS_Standard_V3.git
git remote -v
```

자기 개발 branch를 만든다. branch 이름은 `dev/sung`을 기본으로 사용한다.

```bash
git switch -c dev/sung
```

작업 후 commit/push 기본 흐름:

```bash
git status
git add <changed-files>
git commit -m "docs: update sung onboarding note"
git push -u origin dev/sung
```

## 4. Obsidian 설치와 열기

1. Obsidian을 설치한다.
2. `Open folder as vault`를 선택한다.
3. clone한 `PEETS_Standard_V3` 폴더를 vault로 연다.
4. 문서는 Markdown 파일 그대로 편집한다.

Obsidian은 문서 읽기와 메모 확인용으로 사용한다. 빌드 산출물이나 CCS 설정 파일을 Obsidian에서 실수로 수정하지 않는다.

## 5. VS Code 설치와 열기

1. VS Code를 설치한다.
2. `File > Open Folder`로 `PEETS_Standard_V3` 폴더를 연다.
3. Git 상태는 Source Control 패널이나 터미널의 `git status`로 확인한다.
4. C/C++ 인식이 이상하면 먼저 CCS에서 빌드가 된 상태인지 확인한다.

이 저장소는 CCS가 빌드 후 `CPU*_RAM/.clangd/`, `CM_RAM/.clangd/` 아래에 `compile_commands.json`을 생성한다. 에디터 설정은 빌드 산출물과 연결될 수 있으므로, 초반에는 코드 인식보다 CCS 빌드 성공을 먼저 본다.

## 6. Codex 사용 규칙

Codex는 Windows용 앱이나 VS Code용 확장 중 편한 방식으로 사용한다.
둘 중 하나만 정상 로그인되고, 이 저장소 폴더에서 질문을 보낼 수 있으면 충분하다.

Codex나 다른 에이전트를 사용할 때는 먼저 아래처럼 요청한다.

```text
AGENTS.md와 관련 문서를 먼저 읽고, 지금 작업의 계획을 세워줘. 아직 파일은 수정하지 마.
```

작업을 맡길 때는 기능 하나만 지정한다.

좋은 요청 예:

```text
CPU1 단독 부팅 확인을 위한 현재 main 흐름을 설명하고, 수정이 필요하면 계획부터 작성해줘.
```

나쁜 요청 예:

```text
CPU1, CM UART, ADC, PWM 다 한 번에 붙여줘.
```

에이전트가 코드를 바꿀 때도 원칙은 같다.

- 한 번에 기능 하나만 작업한다.
- 사용한 CCS/C2000Ware 예제를 기록한다.
- 실제 검증 방법과 성공 조건을 남긴다.
- build output 폴더, linker/startup/IPC, pinmux를 근거 없이 바꾸지 않는다.

## 7. CCS 환경 세팅

이 워크스페이스의 기준 버전:

- CCS: `20.5.0`
- SysConfig: `1.27.0`
- C2000Ware: `26.0.0.0`
- TI CGT C2000: `25.11.0.LTS`
- TI CGT ARM: `20.2.7.LTS`

Windows 설치 경로 예:

- CCS: `C:\ti\ccs2050`
- SysConfig: `C:\ti\sysconfig_1.27.0`
- C2000Ware: `C:\ti\c2000\C2000Ware_26_00_00_00`
- TI CGT C2000: `C:\ti\ti-cgt-c2000_25.11.0.LTS`
- TI CGT ARM: `C:\ti\ti-cgt-arm_20.2.7.LTS`

CCS에서 해야 할 일:

1. 세 프로젝트를 import한다.
2. `General > Compilers`에서 ARM/C2000 컴파일러 버전이 기준과 맞는지 확인한다.
3. `General > Products`에서 C2000Ware와 SysConfig 버전이 기준과 맞는지 확인한다.
4. `General > Variables`에서 필요한 사용자 변수를 확인한다.
5. 자동 탐색이 오래된 버전을 먼저 잡으면 해당 discovery path를 `excluded` 처리한다.

상세 절차와 스크린샷은 [CCS 수동 설정](../../ti/ccs-manual-setup.md)을 따른다.

## 8. 첫 bring-up 작업 순서

### 1단계: CPU1 단독 부팅

목표:

- CPU1이 build/debug/run 되는지 확인한다.
- watchdog, clock, 기본 GPIO 상태, heartbeat 같은 최소 신호를 확인한다.

성공 조건 예:

- CCS debug 연결 성공
- CPU1 코드가 main loop까지 진행
- 지정한 heartbeat 또는 관측 포인트가 보임

### 2단계: CPU1 -> CM 핸드셰이크

목표:

- CPU1이 CM을 정상 release한다.
- MSGRAM 또는 IPC로 단순 token 1개를 주고받는다.

관련 spec:

- [001-cpu1-cm-handshake](../../specs/001-cpu1-cm-handshake/requirements.md)

성공 전에는 `CM UART` 작업을 시작하지 않는다.

### 3단계: CM UART

목표:

- `CPU1 -> CM` 핸드셰이크가 확인된 뒤 CM UART 송수신을 붙인다.
- C28x `SCI`와 CM `UART`를 혼동하지 않는다.

핀과 ownership은 [보드 IO 기준](../../board/board-io-reference.md)과 SysConfig 결과를 먼저 확인한다.

### 4단계 이후: 기능 하나씩 추가

새 기능마다 아래 3가지를 남긴다.

- 사용한 CCS/C2000Ware 예제
- 실제 검증 방법
- 성공 조건

기능별 문서는 `docs/specs/NNN-short-name/` 형식으로 만든다.

## 9. 절대 조심할 것

- `CPU1_RAM`, `CPU2_RAM`, `CM_RAM` 같은 build output 폴더를 직접 수정하지 않는다.
- `.c`를 `.cc`로, 또는 `.cc`를 `.c`로 바꾸지 않는다.
- linker command file 위치를 근거 없이 옮기지 않는다.
- startup 코드와 interrupt vector 배치를 근거 없이 바꾸지 않는다.
- IPC message RAM section을 근거 없이 바꾸지 않는다.
- boot, clock, linker, startup, IPC를 한 번에 같이 바꾸지 않는다.
- pin 설정 전에 `CPUSEL`, pinmux, SysConfig 결과를 먼저 확인한다.

문제가 생기면 바로 더 붙이지 말고, 마지막으로 성공한 단계와 실패한 단계 사이의 변경만 본다.
