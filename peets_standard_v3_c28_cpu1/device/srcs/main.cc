//###########################################################################
// 						UOS PEETS Standard Code V3
//
// Author : Harry Lee
// Created on : Mon, Feb. 19 20:21, 2026 $
//
// This source code is optimized for the hardware '388D_Control_v1'
// SDS100i Emulator is set as the default emulator for this source code
// If you are using other emulators (e.g SDS200i), 'PEETS_Standard_V1.ccxml' must be modified
//
// Gate signal : ON = 'FLAG_PWM_ENABLE' = 1, OFF = 'FLAG_PWM_ENABLE' = 0
// Duty : 	'Vtx_duty' (Vtx_duty is limited to 0.5)
// Switching frequency : 'fsw' (default : 60 kHz)
//
// GPIO -> gpio.c, EPWM -> epwm.c, DAC -> dac.c, ADC -> adc.c, Variable -> variable.c
//
//###########################################################################


#include "include/f28388d_project.h"
#include <stdio.h>

void main(void)
{
    while(1)
    {
        asm(" nop");
    }
}