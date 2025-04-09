/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// EPWM8 -> myEPWM0 Pinmux
//
//
// EPWM8A - GPIO Settings
//
#define GPIO_PIN_EPWM8A 14
#define myEPWM0_EPWMA_GPIO 14
#define myEPWM0_EPWMA_PIN_CONFIG GPIO_14_EPWM8A
//
// EPWM8B - GPIO Settings
//
#define GPIO_PIN_EPWM8B 15
#define myEPWM0_EPWMB_GPIO 15
#define myEPWM0_EPWMB_PIN_CONFIG GPIO_15_EPWM8B

//
// EPWM9 -> DAB_PRIM2 Pinmux
//
//
// EPWM9A - GPIO Settings
//
#define GPIO_PIN_EPWM9A 16
#define DAB_PRIM2_EPWMA_GPIO 16
#define DAB_PRIM2_EPWMA_PIN_CONFIG GPIO_16_EPWM9A
//
// EPWM9B - GPIO Settings
//
#define GPIO_PIN_EPWM9B 17
#define DAB_PRIM2_EPWMB_GPIO 17
#define DAB_PRIM2_EPWMB_PIN_CONFIG GPIO_17_EPWM9B

//
// EPWM10 -> DAB_SEC1 Pinmux
//
//
// EPWM10A - GPIO Settings
//
#define GPIO_PIN_EPWM10A 18
#define DAB_SEC1_EPWMA_GPIO 18
#define DAB_SEC1_EPWMA_PIN_CONFIG GPIO_18_EPWM10A
//
// EPWM10B - GPIO Settings
//
#define GPIO_PIN_EPWM10B 19
#define DAB_SEC1_EPWMB_GPIO 19
#define DAB_SEC1_EPWMB_PIN_CONFIG GPIO_19_EPWM10B

//
// EPWM11 -> DAB_SEC2 Pinmux
//
//
// EPWM11A - GPIO Settings
//
#define GPIO_PIN_EPWM11A 20
#define DAB_SEC2_EPWMA_GPIO 20
#define DAB_SEC2_EPWMA_PIN_CONFIG GPIO_20_EPWM11A
//
// EPWM11B - GPIO Settings
//
#define GPIO_PIN_EPWM11B 21
#define DAB_SEC2_EPWMB_GPIO 21
#define DAB_SEC2_EPWMB_PIN_CONFIG GPIO_21_EPWM11B

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
#define ADCD_BASE_BASE ADCD_BASE
#define ADCD_BASE_RESULT_BASE ADCDRESULT_BASE
#define ADCD_BASE_DAB_IPRIMTANK ADC_SOC_NUMBER0
#define ADCD_BASE_FORCE_DAB_IPRIMTANK ADC_FORCE_SOC0
#define ADCD_BASE_SAMPLE_WINDOW_DAB_IPRIMTANK 155
#define ADCD_BASE_TRIGGER_SOURCE_DAB_IPRIMTANK ADC_TRIGGER_EPWM8_SOCA
#define ADCD_BASE_CHANNEL_DAB_IPRIMTANK ADC_CH_ADCIN0
#define ADCD_BASE_DAB_IPRIM ADC_SOC_NUMBER3
#define ADCD_BASE_FORCE_DAB_IPRIM ADC_FORCE_SOC3
#define ADCD_BASE_SAMPLE_WINDOW_DAB_IPRIM 155
#define ADCD_BASE_TRIGGER_SOURCE_DAB_IPRIM ADC_TRIGGER_EPWM8_SOCA
#define ADCD_BASE_CHANNEL_DAB_IPRIM ADC_CH_ADCIN2
#define ADCD_BASE_PS_1V65 ADC_SOC_NUMBER5
#define ADCD_BASE_FORCE_PS_1V65 ADC_FORCE_SOC5
#define ADCD_BASE_SAMPLE_WINDOW_PS_1V65 155
#define ADCD_BASE_TRIGGER_SOURCE_PS_1V65 ADC_TRIGGER_CPU1_TINT2
#define ADCD_BASE_CHANNEL_PS_1V65 ADC_CH_ADCIN3
void ADCD_BASE_init();

#define ADCA_BASE_BASE ADCA_BASE
#define ADCA_BASE_RESULT_BASE ADCARESULT_BASE
#define ADCA_BASE_ISEC_TANK ADC_SOC_NUMBER0
#define ADCA_BASE_FORCE_ISEC_TANK ADC_FORCE_SOC0
#define ADCA_BASE_SAMPLE_WINDOW_ISEC_TANK 155
#define ADCA_BASE_TRIGGER_SOURCE_ISEC_TANK ADC_TRIGGER_EPWM8_SOCA
#define ADCA_BASE_CHANNEL_ISEC_TANK ADC_CH_ADCIN14
#define ADCA_BASE_DAB_ISEC ADC_SOC_NUMBER1
#define ADCA_BASE_FORCE_DAB_ISEC ADC_FORCE_SOC1
#define ADCA_BASE_SAMPLE_WINDOW_DAB_ISEC 155
#define ADCA_BASE_TRIGGER_SOURCE_DAB_ISEC ADC_TRIGGER_EPWM8_SOCA
#define ADCA_BASE_CHANNEL_DAB_ISEC ADC_CH_ADCIN4
void ADCA_BASE_init();

#define ADCC_BASE_BASE ADCC_BASE
#define ADCC_BASE_RESULT_BASE ADCCRESULT_BASE
#define ADCC_BASE_DAB_VSEC ADC_SOC_NUMBER0
#define ADCC_BASE_FORCE_DAB_VSEC ADC_FORCE_SOC0
#define ADCC_BASE_SAMPLE_WINDOW_DAB_VSEC 155
#define ADCC_BASE_TRIGGER_SOURCE_DAB_VSEC ADC_TRIGGER_EPWM8_SOCA
#define ADCC_BASE_CHANNEL_DAB_VSEC ADC_CH_ADCIN2
void ADCC_BASE_init();

#define ADCB_BASE_BASE ADCB_BASE
#define ADCB_BASE_RESULT_BASE ADCBRESULT_BASE
#define ADCB_BASE_DAB_VPRIM ADC_SOC_NUMBER0
#define ADCB_BASE_FORCE_DAB_VPRIM ADC_FORCE_SOC0
#define ADCB_BASE_SAMPLE_WINDOW_DAB_VPRIM 155
#define ADCB_BASE_TRIGGER_SOURCE_DAB_VPRIM ADC_TRIGGER_EPWM8_SOCA
#define ADCB_BASE_CHANNEL_DAB_VPRIM ADC_CH_ADCIN3
void ADCB_BASE_init();


//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
#define myCPUTIMER2_BASE CPUTIMER2_BASE
void myCPUTIMER2_init();

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
#define myEPWM0_BASE EPWM8_BASE
#define myEPWM0_TBPRD 500
#define myEPWM0_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define myEPWM0_TBPHS 0
#define myEPWM0_CMPA 250
#define myEPWM0_CMPB 0
#define myEPWM0_CMPC 0
#define myEPWM0_CMPD 0
#define myEPWM0_DBRED 16380
#define myEPWM0_DBFED 16380
#define myEPWM0_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM0_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM0_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define DAB_PRIM2_BASE EPWM9_BASE
#define DAB_PRIM2_TBPRD 500
#define DAB_PRIM2_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define DAB_PRIM2_TBPHS 2
#define DAB_PRIM2_CMPA 250
#define DAB_PRIM2_CMPB 0
#define DAB_PRIM2_CMPC 0
#define DAB_PRIM2_CMPD 0
#define DAB_PRIM2_DBRED 16380
#define DAB_PRIM2_DBFED 16380
#define DAB_PRIM2_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DAB_PRIM2_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DAB_PRIM2_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define DAB_SEC1_BASE EPWM10_BASE
#define DAB_SEC1_TBPRD 500
#define DAB_SEC1_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define DAB_SEC1_TBPHS 2
#define DAB_SEC1_CMPA 250
#define DAB_SEC1_CMPB 0
#define DAB_SEC1_CMPC 0
#define DAB_SEC1_CMPD 0
#define DAB_SEC1_DBRED 16380
#define DAB_SEC1_DBFED 16380
#define DAB_SEC1_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DAB_SEC1_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DAB_SEC1_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define DAB_SEC2_BASE EPWM11_BASE
#define DAB_SEC2_TBPRD 500
#define DAB_SEC2_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define DAB_SEC2_TBPHS 2
#define DAB_SEC2_CMPA 250
#define DAB_SEC2_CMPB 0
#define DAB_SEC2_CMPC 0
#define DAB_SEC2_CMPD 0
#define DAB_SEC2_DBRED 16380
#define DAB_SEC2_DBFED 16380
#define DAB_SEC2_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DAB_SEC2_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DAB_SEC2_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_ADCD_BASE_1
#define INT_ADCD_BASE_1 INT_ADCD1
#define INT_ADCD_BASE_1_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void INT_ADCD_BASE_1_ISR(void);

// Interrupt Settings for INT_ADCA_BASE_1
#define INT_ADCA_BASE_1 INT_ADCA1
#define INT_ADCA_BASE_1_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void INT_ADCA_BASE_1_ISR(void);

// Interrupt Settings for INT_myCPUTIMER2
#define INT_myCPUTIMER2 INT_TIMER2
extern __interrupt void INT_myCPUTIMER2_ISR(void);

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	ADC_init();
void	CPUTIMER_init();
void	EPWM_init();
void	INTERRUPT_init();
void	SYNC_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
