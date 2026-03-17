//*****************************************************************************
//
//  pinmux.h - Created using TI Pinmux 1.26.2+4477 on 2026. 2. 20. at 오후 8:42:45.
//
//*****************************************************************************
//
// Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************
//
//  These values will provide the functionality requested when written into
//  the registers for which the #defines are named.  For example, using the
//  C2000Ware driverlib header files, use the defines like in this
//  sample function:
//
//  void samplePinMuxFxn(void)
//  {
//      EALLOW;
//      //
//      // Write generated values to mux registers
//      //
//      HWREG(GPIOCTRL_BASE + GPIO_O_GPAMUX1)  = GPAMUX1_VALUE;
//      HWREG(GPIOCTRL_BASE + GPIO_O_GPAMUX2)  = GPAMUX2_VALUE;
//      HWREG(GPIOCTRL_BASE + GPIO_O_GPBMUX1)  = GPBMUX1_VALUE;
//        . . .
//      EDIS;
//  }
//
//  NOTE:  These GPIO control registers are only available on CPU1.
//
//*****************************************************************************

//
// Port A mux register values
//
// Pin C8 (GPIO0) to EPWM1A (mode 1)
// Pin D8 (GPIO1) to EPWM1B (mode 1)
// Pin A7 (GPIO2) to EPWM2A (mode 1)
// Pin B7 (GPIO3) to EPWM2B (mode 1)
// Pin C7 (GPIO4) to EPWM3A (mode 1)
// Pin D7 (GPIO5) to EPWM3B (mode 1)
// Pin A6 (GPIO6) to EPWM4A (mode 1)
// Pin B6 (GPIO7) to EPWM4B (mode 1)
// Pin G2 (GPIO8) to EPWM5A (mode 1)
// Pin G3 (GPIO9) to EPWM5B (mode 1)
// Pin B2 (GPIO10) to EPWM6A (mode 1)
// Pin C1 (GPIO11) to EPWM6B (mode 1)
// Pin C2 (GPIO12) to EPWM7A (mode 1)
// Pin D1 (GPIO13) to EPWM7B (mode 1)
// Pin D2 (GPIO14) to EPWM8A (mode 1)
// Pin D3 (GPIO15) to EPWM8B (mode 1)
// Pin E1 (GPIO16) to EPWM9A (mode 5)
// Pin E2 (GPIO17) to EPWM9B (mode 5)
// Pin E3 (GPIO18) to EPWM10A (mode 5)
// Pin E4 (GPIO19) to EPWM10B (mode 5)
// Pin F2 (GPIO20) to EPWM11A (mode 5)
// Pin F3 (GPIO21) to EPWM11B (mode 5)
// Pin J4 (GPIO22) to EPWM12A (mode 5)
// Pin K4 (GPIO23) to EPWM12B (mode 5)
// Pin K3 (GPIO24) to GPIO24 (mode 0)
// Pin K2 (GPIO25) to GPIO25 (mode 0)
// Pin K1 (GPIO26) to GPIO26 (mode 0)
// Pin L1 (GPIO27) to GPIO27 (mode 0)
// Pin V11 (GPIO28) to GPIO28 (mode 0)
// Pin T11 (GPIO30) to GPIO30 (mode 0)
// Pin W11 (GPIO29) to GPIO29 (mode 0)
// Pin U11 (GPIO31) to MCAN_TX (mode 3)
#define GPAMUX1_MASK 0xffffffff
#define GPAMUX2_MASK 0xffffffff
#define GPAMUX1_VALUE 0x55555555
#define GPAMUX2_VALUE 0xc0005555
#define GPAGMUX1_VALUE 0x00000000
#define GPAGMUX2_VALUE 0x00005555

//
// Port B mux register values
//
// Pin K18 (GPIO44) to ENET_MII_TX_CLK (mode 11)
// Pin U17 (GPIO41) to ENET_REVMII_MDIO_RST (mode 10)
// Pin E18 (GPIO47) to ENET_PPS0 (mode 11)
// Pin R16 (GPIO48) to ENET_PPS1 (mode 11)
// Pin D19 (GPIO42) to GPIO42 (mode 0)
// Pin C19 (GPIO43) to GPIO43 (mode 0)
// Pin E19 (GPIO46) to GPIO46 (mode 0)
// Pin R18 (GPIO50) to GPIO50 (mode 0)
// Pin N17 (GPIO58) to GPIO58 (mode 0)
// Pin M16 (GPIO59) to GPIO59 (mode 0)
// Pin T14 (GPIO35) to GPIO35 (mode 0)
// Pin U16 (GPIO37) to GPIO37 (mode 0)
// Pin T16 (GPIO38) to GPIO38 (mode 0)
// Pin N16 (GPIO56) to GPIO56 (mode 0)
// Pin N18 (GPIO57) to GPIO57 (mode 0)
// Pin R19 (GPIO51) to GPIO51 (mode 0)
// Pin P18 (GPIO54) to GPIO54 (mode 0)
// Pin P16 (GPIO52) to GPIO52 (mode 0)
// Pin P17 (GPIO53) to GPIO53 (mode 0)
// Pin K19 (GPIO45) to GPIO45 (mode 0)
// Pin W17 (GPIO39) to GPIO39 (mode 0)
// Pin V17 (GPIO40) to GPIO40 (mode 0)
// Pin P19 (GPIO55) to GPIO55 (mode 0)
// Pin U13 (GPIO32) to I2CA_SDA (mode 1)
// Pin T13 (GPIO33) to I2CA_SCL (mode 1)
// Pin V16 (GPIO36) to MCAN_RX (mode 10)
// Pin R17 (GPIO49) to SCIA_RX (mode 6)
// Pin U14 (GPIO34) to SCIA_TX (mode 13)
#define GPBMUX1_MASK 0xffffffff
#define GPBMUX2_MASK 0x00ffffff
#define GPBMUX1_VALUE 0xc3080215
#define GPBMUX2_VALUE 0x0000000b
#define GPBGMUX1_VALUE 0x82080230
#define GPBGMUX2_VALUE 0x00000006

//
// Port C mux register values
//
// Pin D16 (GPIO75) to ENET_MII_TX_DATA0 (mode 11)
// Pin A16 (GPIO73) to ENET_RMII_CLK (mode 10)
// Pin C18 (GPIO68) to GPIO68 (mode 0)
// Pin B18 (GPIO69) to GPIO69 (mode 0)
// Pin A17 (GPIO70) to GPIO70 (mode 0)
// Pin B16 (GPIO72) to GPIO72 (mode 0)
// Pin C17 (GPIO74) to GPIO74 (mode 0)
// Pin C16 (GPIO76) to GPIO76 (mode 0)
// Pin A15 (GPIO77) to GPIO77 (mode 0)
// Pin B15 (GPIO78) to GPIO78 (mode 0)
// Pin C15 (GPIO79) to GPIO79 (mode 0)
// Pin D15 (GPIO80) to GPIO80 (mode 0)
// Pin A14 (GPIO81) to GPIO81 (mode 0)
// Pin B14 (GPIO82) to GPIO82 (mode 0)
// Pin C14 (GPIO83) to GPIO83 (mode 0)
// Pin D11 (GPIO87) to GPIO87 (mode 0)
// Pin C6 (GPIO88) to GPIO88 (mode 0)
// Pin D6 (GPIO89) to GPIO89 (mode 0)
// Pin A5 (GPIO90) to GPIO90 (mode 0)
// Pin B5 (GPIO91) to GPIO91 (mode 0)
// Pin A4 (GPIO92) to GPIO92 (mode 0)
// Pin B4 (GPIO93) to GPIO93 (mode 0)
// Pin A3 (GPIO94) to GPIO94 (mode 0)
// Pin B3 (GPIO95) to GPIO95 (mode 0)
// Pin B17 (GPIO71) to SCIB_RX (mode 6)
// Pin C11 (GPIO86) to SCIB_TX (mode 5)
// Pin A11 (GPIO84) to UARTA_TX (mode 11)
// Pin B11 (GPIO85) to UARTA_RX (mode 11)
#define GPCMUX1_MASK 0xffffff00
#define GPCMUX2_MASK 0xffffffff
#define GPCMUX1_VALUE 0x00c88000
#define GPCMUX2_VALUE 0x00001f00
#define GPCGMUX1_VALUE 0x00884000
#define GPCGMUX2_VALUE 0x00001a00

//
// Port D mux register values
//
// Pin V9 (GPIO127) to ESC_SYNC0 (mode 14)
// Pin T9 (GPIO125) to ESC_LATCH0 (mode 14)
// Pin U9 (GPIO126) to ESC_LATCH1 (mode 14)
// Pin N2 (GPIO109) to ENET_MII_CRS (mode 14)
// Pin M2 (GPIO110) to ENET_MII_COL (mode 14)
// Pin M4 (GPIO111) to ENET_MII_RX_CLK (mode 14)
// Pin M3 (GPIO112) to ENET_MII_RX_DV (mode 14)
// Pin N4 (GPIO113) to ENET_MII_RX_ERR (mode 14)
// Pin N3 (GPIO114) to ENET_MII_RX_DATA0 (mode 14)
// Pin V12 (GPIO115) to ENET_MII_RX_DATA1 (mode 14)
// Pin W10 (GPIO116) to ENET_MII_RX_DATA2 (mode 14)
// Pin U12 (GPIO117) to ENET_MII_RX_DATA3 (mode 14)
// Pin T12 (GPIO118) to ENET_MII_TX_EN (mode 14)
// Pin T15 (GPIO119) to ENET_MII_TX_ERR (mode 14)
// Pin T8 (GPIO122) to ENET_MII_TX_DATA1 (mode 14)
// Pin U8 (GPIO123) to ENET_MII_TX_DATA2 (mode 14)
// Pin V8 (GPIO124) to ENET_MII_TX_DATA3 (mode 14)
// Pin L4 (GPIO108) to ENET_MII_INTR (mode 14)
// Pin J3 (GPIO105) to ENET_MDIO_CLK (mode 14)
// Pin L2 (GPIO106) to ENET_MDIO_DATA (mode 14)
// Pin H1 (GPIO100) to GPIO100 (mode 0)
// Pin L3 (GPIO107) to GPIO107 (mode 0)
// Pin U15 (GPIO120) to GPIO120 (mode 0)
// Pin W16 (GPIO121) to GPIO121 (mode 0)
// Pin H2 (GPIO101) to GPIO101 (mode 0)
// Pin H3 (GPIO102) to GPIO102 (mode 0)
// Pin J1 (GPIO103) to GPIO103 (mode 0)
// Pin J2 (GPIO104) to GPIO104 (mode 0)
// Pin C3 (GPIO96) to GPIO96 (mode 0)
// Pin A2 (GPIO97) to GPIO97 (mode 0)
// Pin F1 (GPIO98) to GPIO98 (mode 0)
// Pin G1 (GPIO99) to GPIO99 (mode 0)
#define GPDMUX1_MASK 0xffffffff
#define GPDMUX2_MASK 0xffffffff
#define GPDMUX1_VALUE 0xaa280000
#define GPDMUX2_VALUE 0xaaa0aaaa
#define GPDGMUX1_VALUE 0xff3c0000
#define GPDGMUX2_VALUE 0xfff0ffff

//
// Port E mux register values
//
// Pin F18 (GPIO143) to ESC_LED_LINK0_ACTIVE (mode 14)
// Pin F17 (GPIO144) to ESC_LED_LINK1_ACTIVE (mode 14)
// Pin D18 (GPIO146) to ESC_LED_RUN (mode 14)
// Pin E17 (GPIO145) to ESC_LED_ERR (mode 14)
// Pin D17 (GPIO147) to ESC_LED_STATE_RUN (mode 14)
// Pin B13 (GPIO150) to ESC_I2C_SDA (mode 14)
// Pin C13 (GPIO151) to ESC_I2C_SCL (mode 14)
// Pin U18 (GPIO135) to ESC_TX1_DATA3 (mode 14)
// Pin V18 (GPIO134) to ESC_TX1_DATA2 (mode 14)
// Pin W18 (GPIO132) to ESC_TX1_DATA1 (mode 14)
// Pin V10 (GPIO131) to ESC_TX1_DATA0 (mode 14)
// Pin W9 (GPIO128) to ESC_SYNC1 (mode 14)
// Pin D13 (GPIO152) to ESC_MDIO_CLK (mode 14)
// Pin A12 (GPIO153) to ESC_MDIO_DATA (mode 14)
// Pin B12 (GPIO154) to ESC_PHY_CLK (mode 14)
// Pin T10 (GPIO129) to ESC_TX1_ENA (mode 14)
// Pin T18 (GPIO137) to ESC_RX1_CLK (mode 14)
// Pin T17 (GPIO136) to ESC_RX1_DV (mode 14)
// Pin T19 (GPIO138) to ESC_RX1_ERR (mode 14)
// Pin N19 (GPIO139) to ESC_RX1_DATA0 (mode 14)
// Pin M19 (GPIO140) to ESC_RX1_DATA1 (mode 14)
// Pin M18 (GPIO141) to ESC_RX1_DATA2 (mode 14)
// Pin L19 (GPIO142) to ESC_RX1_DATA3 (mode 14)
// Pin C12 (GPIO155) to ESC_PHY_RESETn (mode 14)
// Pin B10 (GPIO157) to ESC_TX0_CLK (mode 14)
// Pin C10 (GPIO158) to ESC_TX0_DATA0 (mode 14)
// Pin D10 (GPIO159) to ESC_TX0_DATA1 (mode 14)
// Pin D12 (GPIO156) to ESC_TX0_ENA (mode 14)
// Pin U10 (GPIO130) to ESC_TX1_CLK (mode 14)
// Pin D14 (GPIO148) to ESC_PHY0_LINKSTATUS (mode 14)
// Pin A13 (GPIO149) to ESC_PHY1_LINKSTATUS (mode 14)
// Pin G18 (GPIO133) to GPIO133 (mode 0)
#define GPEMUX1_MASK 0xffffffff
#define GPEMUX2_MASK 0xffffffff
#define GPEMUX1_VALUE 0xaaaaa2aa
#define GPEMUX2_VALUE 0xaaaaaaaa
#define GPEGMUX1_VALUE 0xfffff3ff
#define GPEGMUX2_VALUE 0xffffffff

//
// Port F mux register values
//
// Pin A8 (GPIO163) to ESC_RX0_CLK (mode 14)
// Pin D9 (GPIO162) to ESC_RX0_DV (mode 14)
// Pin B8 (GPIO164) to ESC_RX0_ERR (mode 14)
// Pin C5 (GPIO165) to ESC_RX0_DATA0 (mode 14)
// Pin D5 (GPIO166) to ESC_RX0_DATA1 (mode 14)
// Pin C4 (GPIO167) to ESC_RX0_DATA2 (mode 14)
// Pin D4 (GPIO168) to ESC_RX0_DATA3 (mode 14)
// Pin B9 (GPIO160) to ESC_TX0_DATA2 (mode 14)
// Pin C9 (GPIO161) to ESC_TX0_DATA3 (mode 14)
#define GPFMUX1_MASK 0x0003ffff
#define GPFMUX1_VALUE 0x0002aaaa
#define GPFGMUX1_VALUE 0x0003ffff

//
// Port B analog mode register values
//
// Pin D19 (GPIO42) to GPIO42 (mode 0)
// Pin C19 (GPIO43) to GPIO43 (mode 0)
#define GPBAMSEL_MASK 0x00000c00
#define GPBAMSEL_VALUE 0x00000000

//
// Input X-BAR register values
//
// Pin M17 (GPIO60) to INPUTXBAR1 (mode XBAR1)
// Pin L16 (GPIO61) to INPUTXBAR2 (mode XBAR2)
// Pin J17 (GPIO62) to INPUTXBAR3 (mode XBAR3)
// Pin J16 (GPIO63) to INPUTXBAR4 (mode XBAR4)
// Pin L17 (GPIO64) to INPUTXBAR5 (mode XBAR5)
// Pin K16 (GPIO65) to INPUTXBAR6 (mode XBAR6)
// Pin K17 (GPIO66) to INPUTXBAR7 (mode XBAR7)
// Pin B19 (GPIO67) to INPUTXBAR8 (mode XBAR8)
#define INPUT1SELECT_VALUE 0x0000003c
#define INPUT2SELECT_VALUE 0x0000003d
#define INPUT3SELECT_VALUE 0x0000003e
#define INPUT4SELECT_VALUE 0x0000003f
#define INPUT5SELECT_VALUE 0x00000040
#define INPUT6SELECT_VALUE 0x00000041
#define INPUT7SELECT_VALUE 0x00000042
#define INPUT8SELECT_VALUE 0x00000043

//*****************************************************************************
//
// Function prototype for function to write values above into their
// corresponding registers. This function is found in pinmux.c. Its use is
// completely optional.
//
//*****************************************************************************
extern void GPIO_setPinMuxConfig(void);
