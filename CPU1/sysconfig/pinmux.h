//*****************************************************************************
//
//  pinmux.h - Created using TI Pinmux 1.26.2+4477 on 1/27/2026 at 6:18:44 PM.
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
#define GPAMUX1_MASK		0xffffffff
#define GPAMUX2_MASK		0x0000ffff
#define GPAMUX1_VALUE		0x55555555
#define GPAMUX2_VALUE		0x00005555
#define GPAGMUX1_VALUE		0x00000000
#define GPAGMUX2_VALUE		0x00005555

//
// Port B mux register values
//
#define GPBMUX1_MASK		0x00000000
#define GPBMUX2_MASK		0x00000000
#define GPBMUX1_VALUE		0x00000000
#define GPBMUX2_VALUE		0x00000000
#define GPBGMUX1_VALUE		0x00000000
#define GPBGMUX2_VALUE		0x00000000

//
// Port C mux register values
//
#define GPCMUX1_MASK		0x00000000
#define GPCMUX2_MASK		0x00000000
#define GPCMUX1_VALUE		0x00000000
#define GPCMUX2_VALUE		0x00000000
#define GPCGMUX1_VALUE		0x00000000
#define GPCGMUX2_VALUE		0x00000000

//
// Port D mux register values
//
#define GPDMUX1_MASK		0x00000000
#define GPDMUX2_MASK		0x00000000
#define GPDMUX1_VALUE		0x00000000
#define GPDMUX2_VALUE		0x00000000
#define GPDGMUX1_VALUE		0x00000000
#define GPDGMUX2_VALUE		0x00000000

//
// Port E mux register values
//
#define GPEMUX1_MASK		0x00000000
#define GPEMUX2_MASK		0x00000000
#define GPEMUX1_VALUE		0x00000000
#define GPEMUX2_VALUE		0x00000000
#define GPEGMUX1_VALUE		0x00000000
#define GPEGMUX2_VALUE		0x00000000

//
// Port F mux register values
//
#define GPFMUX1_MASK		0x00000000
#define GPFMUX1_VALUE		0x00000000
#define GPFGMUX1_VALUE		0x00000000

//
// Port B analog mode register values
//
// Pin D19 (GPIO42) to USB0DM (mode ALT)
// Pin C19 (GPIO43) to USB0DP (mode ALT)
#define GPBAMSEL_MASK		0x00000c00
#define GPBAMSEL_VALUE		0x00000c00

//*****************************************************************************
//
// Function prototype for function to write values above into their
// corresponding registers. This function is found in pinmux.c. Its use is
// completely optional.
//
//*****************************************************************************
extern void GPIO_setPinMuxConfig(void);
