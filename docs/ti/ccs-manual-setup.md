# CCS Manual Setup

## 목적

- 이 워크스페이스는 CCS 의존성 자동 탐색 결과를 그대로 쓰지 않는다.
- 컴파일러와 제품 등록은 수동 discovery-path 기준으로 고정한다.
- 기본 경로가 잘못된 버전을 먼저 잡으면 `excluded` 처리해서 검색 대상에서 뺀다.

## Windows 호환성

- 이 워크스페이스는 Windows CCS에서도 정상 동작한다.
- 아래 절차의 핵심은 OS가 아니라 CCS에 등록되는 제품과 컴파일러 버전이다.
- Windows에서는 Linux 예시 경로를 그대로 쓰지 말고, 같은 버전이 설치된 Windows 경로를 `Discovery Path`에 직접 등록한다.
- 예를 들어 `C:\ti\ccs2050`, `C:\ti\sysconfig_1.27.0`, `C:\ti\c2000\C2000Ware_26_00_00_00`, `C:\ti\ti-cgt-arm_20.2.7.LTS`, `C:\ti\ti-cgt-c2000_25.11.0.LTS`처럼 실제 설치 위치에 맞춘다.
- Windows에서도 오래된 상위 경로가 먼저 잡히면 동일하게 `excluded` 처리한다.
- 확인 기준은 Linux와 같다. `Discovered Compilers`와 `Discovered Products`에 아래 기준 버전이 보이면 정상이다.

## 기준 버전

- CCS: `20.5.0`
  Code Composer Studio. 프로젝트 import, build, debug를 담당하는 TI IDE다.
- SysConfig: `sysconfig_1_27_0`
  pinmux, peripheral 설정, 초기화 코드 생성을 돕는 설정 도구다.
- C2000Ware: `C2000Ware26_0_0_0STS`
  F28388D용 driverlib, device header, example을 포함한 TI SDK다.
- TI CGT ARM: `TI_CGT_ARM_20_2_7LTS`
  `CM`용 ARM 컴파일러와 링커다.
- TI CGT C2000: `TI_CGT_C2000_25_11_0LTS`
  `CPU1`/`CPU2`용 C28x 컴파일러와 링커다.

공식 다운로드 링크:

- [Code Composer Studio Downloads](https://www.ti.com/tool/CCSTUDIO#downloads)
- [C2000Ware Downloads](https://www.ti.com/tool/C2000WARE#downloads)
- [ARM CGT Downloads](https://www.ti.com/tool/ARM-CGT#downloads)
- [C2000 CGT Downloads](https://www.ti.com/tool/C2000-CGT#downloads)

## 1. Compilers

메뉴: `General > Compilers`

확인 순서:

1. `Discovery Path`에서 아래 Linux 경로가 등록되어 있는지 본다.
2. 오래된 기본 경로가 먼저 잡히면 `excluded`로 바꿔서 탐색 대상에서 뺀다.
3. `Discovered Compilers`에 ARM과 C2000 툴체인이 기대 버전으로 보이는지 확인한다.

현재 Linux discovery-path:

- `/home/harry/ti/ccs2050` -> `default`, `excluded`
- `/home/harry/ti` -> `default`, `excluded`
- `/home/harry/ti/ti-cgt-arm_20.2.7.LTS`
- `/home/harry/ti/ti-cgt-c2000_25.11.0.LTS`

기대되는 discovered compilers:

- `Arm` -> `TI v20.2.7.LTS : /home/harry/ti/ti-cgt-arm_20.2.7.LTS`
- `C2000` -> `TI v25.11.0.LTS : /home/harry/ti/ti-cgt-c2000_25.11.0.LTS`

스크린샷:

![CCS Compilers Manual Setup](../images/ccs-settings-compilers.png)

## 2. Products

메뉴: `General > Products`

확인 순서:

1. `Discovery Path`에서 SysConfig와 C2000Ware 경로가 직접 등록되어 있는지 본다.
2. `ccs2050`, `/home/harry/ti` 같은 상위 경로가 오래된 버전을 먼저 잡으면 `excluded` 처리한다.
3. `Discovered Products`에 `C2000Ware 26.0.0.0`, `SysConfig 1.27.0`이 보이는지 확인한다.

현재 Linux discovery-path:

- `/home/harry/ti/ccs2050` -> `default`, `excluded`
- `/home/harry/ti` -> `default`, `excluded`
- `/home/harry/ti/sysconfig_1.27.0`
- `/home/harry/ti/c2000`

기대되는 discovered products:

- `C2000Ware` -> `26.0.0.0 : /home/harry/ti/c2000/C2000Ware_26_00_00_00`
- `SysConfig` -> `1.27.0 : /home/harry/ti/sysconfig_1.27.0`

스크린샷:

![CCS Products Manual Setup](../images/ccs-settings-products.png)

## 3. Variables

메뉴: `General > Variables`

확인 순서:

1. 사용자 정의 변수에 `peets_is_linux`가 등록되어 있는지 본다.
2. 목록이 많으면 `Show only user-defined variables`를 켜서 확인한다.

현재 사용자 정의 변수:

- `peets_is_linux` -> `[String] True`

필요하면 `Show only user-defined variables`로 바꿔서 확인한다.

스크린샷:

![CCS Variables Manual Setup](../images/ccs-settings-variables.png)

## 메모

- 현재 문서의 Linux 경로는 이 머신의 실제 설치 경로를 기준으로 적었다.
- 문서와 실제 프로젝트 설정이 다르면 `CPU1/.cproject`, `CPU2/.cproject`, `CM/.cproject`를 먼저 확인한다.
- 자동 탐색 결과에 오래된 버전이 먼저 잡히면 가져다 쓰지 말고 discovery-path에서 제외한다.
