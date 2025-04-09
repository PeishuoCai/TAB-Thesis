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

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules. 
// Call this function in your application if you wish to do all module 
// initialization.
// If you wish to not use some of the initializations, instead of the 
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
	EALLOW;

	PinMux_init();
	SYNC_init();
	ADC_init();
	CPUTIMER_init();
	EPWM_init();
	INTERRUPT_init();

	EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
	//
	// PinMux for modules assigned to CPU1
	//
	
	//
	// EPWM8 -> myEPWM0 Pinmux
	//
	GPIO_setPinConfig(myEPWM0_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM0_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM0_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(myEPWM0_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM0_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM0_EPWMB_GPIO, GPIO_QUAL_SYNC);

	//
	// EPWM9 -> DAB_PRIM2 Pinmux
	//
	GPIO_setPinConfig(DAB_PRIM2_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(DAB_PRIM2_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(DAB_PRIM2_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(DAB_PRIM2_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(DAB_PRIM2_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(DAB_PRIM2_EPWMB_GPIO, GPIO_QUAL_SYNC);

	//
	// EPWM10 -> DAB_SEC1 Pinmux
	//
	GPIO_setPinConfig(DAB_SEC1_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(DAB_SEC1_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(DAB_SEC1_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(DAB_SEC1_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(DAB_SEC1_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(DAB_SEC1_EPWMB_GPIO, GPIO_QUAL_SYNC);

	//
	// EPWM11 -> DAB_SEC2 Pinmux
	//
	GPIO_setPinConfig(DAB_SEC2_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(DAB_SEC2_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(DAB_SEC2_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(DAB_SEC2_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(DAB_SEC2_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(DAB_SEC2_EPWMB_GPIO, GPIO_QUAL_SYNC);


}

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
void ADC_init(){
	ADCD_BASE_init();
	ADCA_BASE_init();
	ADCC_BASE_init();
	ADCB_BASE_init();
}

void ADCD_BASE_init(){
	//
	// ADC Initialization: Write ADC configurations and power up the ADC
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(ADCD_BASE_BASE, ADC_CLK_DIV_4_0);
	//
	// Configures the analog-to-digital converter resolution and signal mode.
	//
	ADC_setMode(ADCD_BASE_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(ADCD_BASE_BASE, ADC_PULSE_END_OF_CONV);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(ADCD_BASE_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(500);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(ADCD_BASE_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(ADCD_BASE_BASE, ADC_PRI_ALL_ROUND_ROBIN);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_EPWM8_SOCA
	//	  	Channel			: ADC_CH_ADCIN0
	//	 	Sample Window	: 31 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(ADCD_BASE_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM8_SOCA, ADC_CH_ADCIN0, 31U);
	ADC_setInterruptSOCTrigger(ADCD_BASE_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 3 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 3
	//	  	Trigger			: ADC_TRIGGER_EPWM8_SOCA
	//	  	Channel			: ADC_CH_ADCIN2
	//	 	Sample Window	: 31 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(ADCD_BASE_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_EPWM8_SOCA, ADC_CH_ADCIN2, 31U);
	ADC_setInterruptSOCTrigger(ADCD_BASE_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 5 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 5
	//	  	Trigger			: ADC_TRIGGER_CPU1_TINT2
	//	  	Channel			: ADC_CH_ADCIN3
	//	 	Sample Window	: 31 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(ADCD_BASE_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU1_TINT2, ADC_CH_ADCIN3, 31U);
	ADC_setInterruptSOCTrigger(ADCD_BASE_BASE, ADC_SOC_NUMBER5, ADC_INT_SOC_TRIGGER_NONE);
	//
	// ADC Interrupt 1 Configuration
	// 		Source	: ADC_SOC_NUMBER0
	// 		Interrupt Source: enabled
	// 		Continuous Mode	: disabled
	//
	//
	ADC_setInterruptSource(ADCD_BASE_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
	ADC_clearInterruptStatus(ADCD_BASE_BASE, ADC_INT_NUMBER1);
	ADC_disableContinuousMode(ADCD_BASE_BASE, ADC_INT_NUMBER1);
	ADC_enableInterrupt(ADCD_BASE_BASE, ADC_INT_NUMBER1);
}
void ADCA_BASE_init(){
	//
	// ADC Initialization: Write ADC configurations and power up the ADC
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(ADCA_BASE_BASE, ADC_CLK_DIV_4_0);
	//
	// Configures the analog-to-digital converter resolution and signal mode.
	//
	ADC_setMode(ADCA_BASE_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(ADCA_BASE_BASE, ADC_PULSE_END_OF_CONV);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(ADCA_BASE_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(500);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(ADCA_BASE_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(ADCA_BASE_BASE, ADC_PRI_ALL_ROUND_ROBIN);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_EPWM8_SOCA
	//	  	Channel			: ADC_CH_ADCIN14
	//	 	Sample Window	: 31 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(ADCA_BASE_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM8_SOCA, ADC_CH_ADCIN14, 31U);
	ADC_setInterruptSOCTrigger(ADCA_BASE_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 1 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 1
	//	  	Trigger			: ADC_TRIGGER_EPWM8_SOCA
	//	  	Channel			: ADC_CH_ADCIN4
	//	 	Sample Window	: 31 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(ADCA_BASE_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM8_SOCA, ADC_CH_ADCIN4, 31U);
	ADC_setInterruptSOCTrigger(ADCA_BASE_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
	//
	// ADC Interrupt 1 Configuration
	// 		Source	: ADC_SOC_NUMBER0
	// 		Interrupt Source: enabled
	// 		Continuous Mode	: disabled
	//
	//
	ADC_setInterruptSource(ADCA_BASE_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
	ADC_clearInterruptStatus(ADCA_BASE_BASE, ADC_INT_NUMBER1);
	ADC_disableContinuousMode(ADCA_BASE_BASE, ADC_INT_NUMBER1);
	ADC_enableInterrupt(ADCA_BASE_BASE, ADC_INT_NUMBER1);
}
void ADCC_BASE_init(){
	//
	// ADC Initialization: Write ADC configurations and power up the ADC
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(ADCC_BASE_BASE, ADC_CLK_DIV_4_0);
	//
	// Configures the analog-to-digital converter resolution and signal mode.
	//
	ADC_setMode(ADCC_BASE_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(ADCC_BASE_BASE, ADC_PULSE_END_OF_ACQ_WIN);
	//
	// Sets the timing of early interrupt generation.
	//
	ADC_setInterruptCycleOffset(ADCC_BASE_BASE, 0U);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(ADCC_BASE_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(500);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(ADCC_BASE_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(ADCC_BASE_BASE, ADC_PRI_ALL_ROUND_ROBIN);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_EPWM8_SOCA
	//	  	Channel			: ADC_CH_ADCIN2
	//	 	Sample Window	: 31 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(ADCC_BASE_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM8_SOCA, ADC_CH_ADCIN2, 31U);
	ADC_setInterruptSOCTrigger(ADCC_BASE_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
}
void ADCB_BASE_init(){
	//
	// ADC Initialization: Write ADC configurations and power up the ADC
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(ADCB_BASE_BASE, ADC_CLK_DIV_4_0);
	//
	// Configures the analog-to-digital converter resolution and signal mode.
	//
	ADC_setMode(ADCB_BASE_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(ADCB_BASE_BASE, ADC_PULSE_END_OF_ACQ_WIN);
	//
	// Sets the timing of early interrupt generation.
	//
	ADC_setInterruptCycleOffset(ADCB_BASE_BASE, 0U);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(ADCB_BASE_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(500);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(ADCB_BASE_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(ADCB_BASE_BASE, ADC_PRI_ALL_ROUND_ROBIN);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_EPWM8_SOCA
	//	  	Channel			: ADC_CH_ADCIN3
	//	 	Sample Window	: 31 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(ADCB_BASE_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM8_SOCA, ADC_CH_ADCIN3, 31U);
	ADC_setInterruptSOCTrigger(ADCB_BASE_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
}

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
void CPUTIMER_init(){
	myCPUTIMER2_init();
}

void myCPUTIMER2_init(){
	CPUTimer_setEmulationMode(myCPUTIMER2_BASE, CPUTIMER_EMULATIONMODE_STOPATZERO);
	CPUTimer_selectClockSource(myCPUTIMER2_BASE, CPUTIMER_CLOCK_SOURCE_SYS, CPUTIMER_CLOCK_PRESCALER_1);
	CPUTimer_setPreScaler(myCPUTIMER2_BASE, 0U);
	CPUTimer_setPeriod(myCPUTIMER2_BASE, 1999U);
	CPUTimer_enableInterrupt(myCPUTIMER2_BASE);
	CPUTimer_stopTimer(myCPUTIMER2_BASE);

	CPUTimer_reloadTimerCounter(myCPUTIMER2_BASE);
	CPUTimer_startTimer(myCPUTIMER2_BASE);
}

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
void EPWM_init(){
    EPWM_enableGlobalLoad(myEPWM0_BASE);	
    EPWM_enableGlobalLoadOneShotMode(myEPWM0_BASE);	
    EPWM_setGlobalLoadOneShotLatch(myEPWM0_BASE);	
    EPWM_setClockPrescaler(myEPWM0_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(myEPWM0_BASE, 500);	
    EPWM_enableGlobalLoadRegisters(myEPWM0_BASE, EPWM_GL_REGISTER_TBPRD_TBPRDHR);	
    EPWM_setTimeBaseCounter(myEPWM0_BASE, 0);	
    EPWM_setTimeBaseCounterMode(myEPWM0_BASE, EPWM_COUNTER_MODE_UP_DOWN);	
    EPWM_disablePhaseShiftLoad(myEPWM0_BASE);	
    EPWM_setPhaseShift(myEPWM0_BASE, 0);	
    EPWM_setSyncInPulseSource(myEPWM0_BASE, EPWM_SYNC_IN_PULSE_SRC_DISABLE);	
    EPWM_enableSyncOutPulseSource(myEPWM0_BASE, EPWM_SYNC_OUT_PULSE_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(myEPWM0_BASE, EPWM_COUNTER_COMPARE_A, 250);	
    EPWM_enableGlobalLoadRegisters(myEPWM0_BASE, EPWM_GL_REGISTER_CMPA_CMPAHR);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM0_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(myEPWM0_BASE, EPWM_COUNTER_COMPARE_B, 0);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM0_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_enableGlobalLoadRegisters(myEPWM0_BASE, EPWM_GL_REGISTER_AQCTLB_AQCTLB2);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM0_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(myEPWM0_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(myEPWM0_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM0_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_setRisingEdgeDelayCount(myEPWM0_BASE, 16380);	
    EPWM_setDeadBandDelayMode(myEPWM0_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(myEPWM0_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_setFallingEdgeDelayCount(myEPWM0_BASE, 16380);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM0_BASE);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM0_BASE);	
    EPWM_enableADCTrigger(myEPWM0_BASE, EPWM_SOC_A);	
    EPWM_setADCTriggerSource(myEPWM0_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);	
    EPWM_setADCTriggerEventPrescale(myEPWM0_BASE, EPWM_SOC_A, 1);	
    EPWM_enableADCTrigger(myEPWM0_BASE, EPWM_SOC_B);	
    EPWM_setADCTriggerSource(myEPWM0_BASE, EPWM_SOC_B, EPWM_SOC_TBCTR_D_CMPA);	
    EPWM_setADCTriggerEventPrescale(myEPWM0_BASE, EPWM_SOC_B, 1);	
    EPWM_enableGlobalLoad(DAB_PRIM2_BASE);	
    EPWM_setGlobalLoadTrigger(DAB_PRIM2_BASE, EPWM_GL_LOAD_PULSE_SYNC);	
    EPWM_enableGlobalLoadOneShotMode(DAB_PRIM2_BASE);	
    EPWM_setGlobalLoadOneShotLatch(DAB_PRIM2_BASE);	
    EPWM_setupEPWMLinks(DAB_PRIM2_BASE, EPWM_LINK_WITH_EPWM_8, EPWM_LINK_GLDCTL2);	
    EPWM_setClockPrescaler(DAB_PRIM2_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(DAB_PRIM2_BASE, 500);	
    EPWM_setupEPWMLinks(DAB_PRIM2_BASE, EPWM_LINK_WITH_EPWM_8, EPWM_LINK_TBPRD);	
    EPWM_setTimeBaseCounter(DAB_PRIM2_BASE, 0);	
    EPWM_setTimeBaseCounterMode(DAB_PRIM2_BASE, EPWM_COUNTER_MODE_UP_DOWN);	
    EPWM_setCountModeAfterSync(DAB_PRIM2_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);	
    EPWM_enablePhaseShiftLoad(DAB_PRIM2_BASE);	
    EPWM_setPhaseShift(DAB_PRIM2_BASE, 2);	
    EPWM_setSyncInPulseSource(DAB_PRIM2_BASE, EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM8);	
    EPWM_setCounterCompareValue(DAB_PRIM2_BASE, EPWM_COUNTER_COMPARE_A, 250);	
    EPWM_setCounterCompareShadowLoadMode(DAB_PRIM2_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_SYNC_ONLY);	
    EPWM_setupEPWMLinks(DAB_PRIM2_BASE, EPWM_LINK_WITH_EPWM_8, EPWM_LINK_COMP_A);	
    EPWM_setCounterCompareValue(DAB_PRIM2_BASE, EPWM_COUNTER_COMPARE_B, 0);	
    EPWM_setCounterCompareShadowLoadMode(DAB_PRIM2_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_SYNC_ONLY);	
    EPWM_setActionQualifierAction(DAB_PRIM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(DAB_PRIM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(DAB_PRIM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(DAB_PRIM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(DAB_PRIM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(DAB_PRIM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_enableGlobalLoadRegisters(DAB_PRIM2_BASE, EPWM_GL_REGISTER_AQCTLB_AQCTLB2);	
    EPWM_setActionQualifierShadowLoadMode(DAB_PRIM2_BASE, EPWM_ACTION_QUALIFIER_B, EPWM_AQ_LOAD_ON_SYNC_ONLY);	
    EPWM_setActionQualifierAction(DAB_PRIM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(DAB_PRIM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(DAB_PRIM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(DAB_PRIM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(DAB_PRIM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(DAB_PRIM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(DAB_PRIM2_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(DAB_PRIM2_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(DAB_PRIM2_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_setRisingEdgeDelayCount(DAB_PRIM2_BASE, 16380);	
    EPWM_setDeadBandDelayMode(DAB_PRIM2_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(DAB_PRIM2_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_setFallingEdgeDelayCount(DAB_PRIM2_BASE, 16380);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(DAB_PRIM2_BASE);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(DAB_PRIM2_BASE);	
    EPWM_enableGlobalLoad(DAB_SEC1_BASE);	
    EPWM_setGlobalLoadTrigger(DAB_SEC1_BASE, EPWM_GL_LOAD_PULSE_SYNC);	
    EPWM_enableGlobalLoadOneShotMode(DAB_SEC1_BASE);	
    EPWM_setGlobalLoadOneShotLatch(DAB_SEC1_BASE);	
    EPWM_setupEPWMLinks(DAB_SEC1_BASE, EPWM_LINK_WITH_EPWM_8, EPWM_LINK_GLDCTL2);	
    EPWM_setClockPrescaler(DAB_SEC1_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(DAB_SEC1_BASE, 500);	
    EPWM_setupEPWMLinks(DAB_SEC1_BASE, EPWM_LINK_WITH_EPWM_8, EPWM_LINK_TBPRD);	
    EPWM_setTimeBaseCounter(DAB_SEC1_BASE, 0);	
    EPWM_setTimeBaseCounterMode(DAB_SEC1_BASE, EPWM_COUNTER_MODE_UP_DOWN);	
    EPWM_setCountModeAfterSync(DAB_SEC1_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);	
    EPWM_enablePhaseShiftLoad(DAB_SEC1_BASE);	
    EPWM_setPhaseShift(DAB_SEC1_BASE, 2);	
    EPWM_setSyncInPulseSource(DAB_SEC1_BASE, EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM8);	
    EPWM_setCounterCompareValue(DAB_SEC1_BASE, EPWM_COUNTER_COMPARE_A, 250);	
    EPWM_setCounterCompareShadowLoadMode(DAB_SEC1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setupEPWMLinks(DAB_SEC1_BASE, EPWM_LINK_WITH_EPWM_8, EPWM_LINK_COMP_A);	
    EPWM_setCounterCompareValue(DAB_SEC1_BASE, EPWM_COUNTER_COMPARE_B, 0);	
    EPWM_setCounterCompareShadowLoadMode(DAB_SEC1_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierShadowLoadMode(DAB_SEC1_BASE, EPWM_ACTION_QUALIFIER_A, EPWM_AQ_LOAD_ON_SYNC_ONLY);	
    EPWM_setActionQualifierAction(DAB_SEC1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(DAB_SEC1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(DAB_SEC1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(DAB_SEC1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(DAB_SEC1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(DAB_SEC1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_enableGlobalLoadRegisters(DAB_SEC1_BASE, EPWM_GL_REGISTER_AQCTLB_AQCTLB2);	
    EPWM_setActionQualifierShadowLoadMode(DAB_SEC1_BASE, EPWM_ACTION_QUALIFIER_B, EPWM_AQ_LOAD_ON_SYNC_ONLY);	
    EPWM_setActionQualifierAction(DAB_SEC1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(DAB_SEC1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(DAB_SEC1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(DAB_SEC1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(DAB_SEC1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(DAB_SEC1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(DAB_SEC1_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(DAB_SEC1_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(DAB_SEC1_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_setRisingEdgeDelayCount(DAB_SEC1_BASE, 16380);	
    EPWM_setDeadBandDelayMode(DAB_SEC1_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(DAB_SEC1_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_setFallingEdgeDelayCount(DAB_SEC1_BASE, 16380);	
    EPWM_enableGlobalLoad(DAB_SEC2_BASE);	
    EPWM_setGlobalLoadTrigger(DAB_SEC2_BASE, EPWM_GL_LOAD_PULSE_SYNC);	
    EPWM_enableGlobalLoadOneShotMode(DAB_SEC2_BASE);	
    EPWM_setGlobalLoadOneShotLatch(DAB_SEC2_BASE);	
    EPWM_setupEPWMLinks(DAB_SEC2_BASE, EPWM_LINK_WITH_EPWM_8, EPWM_LINK_GLDCTL2);	
    EPWM_setClockPrescaler(DAB_SEC2_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(DAB_SEC2_BASE, 500);	
    EPWM_setTimeBaseCounter(DAB_SEC2_BASE, 0);	
    EPWM_setTimeBaseCounterMode(DAB_SEC2_BASE, EPWM_COUNTER_MODE_UP_DOWN);	
    EPWM_setCountModeAfterSync(DAB_SEC2_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);	
    EPWM_enablePhaseShiftLoad(DAB_SEC2_BASE);	
    EPWM_setPhaseShift(DAB_SEC2_BASE, 2);	
    EPWM_setSyncInPulseSource(DAB_SEC2_BASE, EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM8);	
    EPWM_setCounterCompareValue(DAB_SEC2_BASE, EPWM_COUNTER_COMPARE_A, 250);	
    EPWM_setCounterCompareShadowLoadMode(DAB_SEC2_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_SYNC_ONLY);	
    EPWM_setupEPWMLinks(DAB_SEC2_BASE, EPWM_LINK_WITH_EPWM_8, EPWM_LINK_COMP_A);	
    EPWM_setCounterCompareValue(DAB_SEC2_BASE, EPWM_COUNTER_COMPARE_B, 0);	
    EPWM_setCounterCompareShadowLoadMode(DAB_SEC2_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_SYNC_ONLY);	
    EPWM_setActionQualifierShadowLoadMode(DAB_SEC2_BASE, EPWM_ACTION_QUALIFIER_A, EPWM_AQ_LOAD_ON_SYNC_ONLY);	
    EPWM_setActionQualifierAction(DAB_SEC2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(DAB_SEC2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(DAB_SEC2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(DAB_SEC2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(DAB_SEC2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(DAB_SEC2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_enableGlobalLoadRegisters(DAB_SEC2_BASE, EPWM_GL_REGISTER_AQCTLB_AQCTLB2);	
    EPWM_setActionQualifierAction(DAB_SEC2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(DAB_SEC2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(DAB_SEC2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(DAB_SEC2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(DAB_SEC2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(DAB_SEC2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(DAB_SEC2_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(DAB_SEC2_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(DAB_SEC2_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_setRisingEdgeDelayCount(DAB_SEC2_BASE, 16380);	
    EPWM_setDeadBandDelayMode(DAB_SEC2_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(DAB_SEC2_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_setFallingEdgeDelayCount(DAB_SEC2_BASE, 16380);	
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){
	
	// Interrupt Setings for INT_ADCD_BASE_1
	Interrupt_register(INT_ADCD_BASE_1, &INT_ADCD_BASE_1_ISR);
	Interrupt_enable(INT_ADCD_BASE_1);
	
	// Interrupt Setings for INT_ADCA_BASE_1
	Interrupt_register(INT_ADCA_BASE_1, &INT_ADCA_BASE_1_ISR);
	Interrupt_enable(INT_ADCA_BASE_1);
	
	// Interrupt Setings for INT_myCPUTIMER2
	Interrupt_register(INT_myCPUTIMER2, &INT_myCPUTIMER2_ISR);
	Interrupt_enable(INT_myCPUTIMER2);
}
//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************
void SYNC_init(){
	SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT);
	//
	// SOCA
	//
	SysCtl_enableExtADCSOCSource(0);
	//
	// SOCB
	//
	SysCtl_enableExtADCSOCSource(0);
}
