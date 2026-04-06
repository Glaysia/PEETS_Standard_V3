# CCS Manual Setup

## 목적

- 이 워크스페이스는 CCS 의존성 자동 탐색 결과를 그대로 쓰지 않는다.
- 컴파일러와 제품 등록은 수동 discovery-path 기준으로 고정한다.
- 기본 경로가 잘못된 버전을 먼저 잡으면 `excluded` 처리해서 검색 대상에서 뺀다.

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

현재 Linux discovery-path:

- `/home/harry/ti/ccs2050` -> `default`, `excluded`
- `/home/harry/ti` -> `default`, `excluded`
- `/home/harry/ti/ti-cgt-arm_20.2.7.LTS`
- `/home/harry/ti/ti-cgt-c2000_25.11.0.LTS`

기대되는 discovered compilers:

- `Arm` -> `TI v20.2.7.LTS : /home/harry/ti/ti-cgt-arm_20.2.7.LTS`
- `C2000` -> `TI v25.11.0.LTS : /home/harry/ti/ti-cgt-c2000_25.11.0.LTS`

![CCS Compilers Manual Setup](../images/ccs-settings-compilers.png)

## 2. Products

메뉴: `General > Products`

현재 Linux discovery-path:

- `/home/harry/ti/ccs2050` -> `default`, `excluded`
- `/home/harry/ti` -> `default`, `excluded`
- `/home/harry/ti/sysconfig_1.27.0`
- `/home/harry/ti/c2000`

기대되는 discovered products:

- `C2000Ware` -> `26.0.0.0 : /home/harry/ti/c2000/C2000Ware_26_00_00_00`
- `SysConfig` -> `1.27.0 : /home/harry/ti/sysconfig_1.27.0`

![CCS Products Manual Setup](../images/ccs-settings-products.png)

## 3. Variables

메뉴: `General > Variables`

현재 사용자 정의 변수:

- `peets_is_linux` -> `[String] True`

필요하면 `Show only user-defined variables`로 바꿔서 확인한다.

![CCS Variables Manual Setup](../images/ccs-settings-variables.png)

## 메모

- 현재 문서의 Linux 경로는 이 머신의 실제 설치 경로를 기준으로 적었다.
- 문서와 실제 프로젝트 설정이 다르면 `CPU1/.cproject`, `CPU2/.cproject`, `CM/.cproject`를 먼저 확인한다.
- 자동 탐색 결과에 오래된 버전이 먼저 잡히면 가져다 쓰지 말고 discovery-path에서 제외한다.
