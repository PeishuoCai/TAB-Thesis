//#############################################################################
//
// FILE:   adc_ex2_soc_epwm.c
//
// TITLE:  ADC ePWM Triggering
//
//! \addtogroup driver_example_list
//! <h1>ADC ePWM Triggering</h1>
//!
//! This example sets up ePWM1 to periodically trigger a conversion on ADCA.
//!
//! \b External \b Connections \n
//!  - A0 should be connected to a signal to convert
//!
//! \b Watch \b Variables \n
//! - \b myADC0Results - A sequence of analog-to-digital conversion samples from
//!   pin A0. The time between samples is determined based on the period
//!   of the ePWM timer.
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
// $
//#############################################################################
//

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//

typedef struct {
    volatile float adc_1v65_ref;

} PS_meas_t;
PS_meas_t PS_meas;

#define ADC_RES_PS (1<<12)
#define ADC_REF_PS 3.0
#define DAC_REF_PS 3.3
#define ADC_VOFFSET_PS 1.65
#define DAC_MAX 4095
#define ADC_RES_DAB ADC_RES_PS
#define ADC_REF_DAB ADC_REF_PS
#define DAC_REF_DAB DAC_REF_PS

#define ADC_SCALER_DAB (ADC_RES_DAB/ADC_REF_DAB)
#define DAC_SCALER_DAB (ADC_RES_DAB/DAC_REF_DAB)
#define G_ISEC (41 * (0.006/5.0)*(7.15)/(4.7+4.7))
#define G_TEMP ((ADC_SCALER_DAB));
#define G_VSEC (0.4 * (12.4/(365+365+12.4))*(8.45/(2.55+2.55)))
#define G_IPRIM ((150/10)*(0.01/5.0))
#define G_ITANK (0.02)
#define G_VPRIM (7.15/((3*365)+7.15))
#define MEAS_PS_1V65_REF ((float)HWREGH(ADCDRESULT_BASE + (uint32_t)ADCD_BASE_PS_1V65))
float meas1v65;

#define PS_1V65_REF (PS_meas.adc_1v65_ref)

const float adcscalerDAB = 1/ADC_SCALER_DAB;
const float g_ISEC = 1/G_ISEC;
const float g_TEMP = 1/G_TEMP;
const float g_VSEC = 1/G_VSEC;
const float g_IPRIM = 1/G_IPRIM;
const float g_ITANK = 1/G_ITANK;
const float g_VPRIM = 1/G_VPRIM;

#define RESULTS_BUFFER_SIZE     256
#define SCALE_ISEC(x) (g_ISEC*(adcscalerDAB*(x - MEAS_PS_1V65_REF)))
#define INV_SCALE_ISEC(x) (((x * G_ISEC) + ADC_VOFFSET_PS)*DAC_SCALER_DAB)

#define SCALE_IPRIM(x) (g_IPRIM*(adcscalerDAB*(x - MEAS_PS_1V65_REF)))
#define INV_SCALE_IPRIM(x) (((x * G_IPRIM) + ADC_VOFFSET_PS)*DAC_SCALER_DAB)

#define SCALE_VSEC(x) (g_VSEC*(adcscalerDAB*x))
#define INV_SCALE_VSEC(x) ((x * G_VSEC)*DAC_SCALER_DAB)

#define SCALE_VPRIM(x) (g_VPRIM*(adcscalerDAB*x))
#define INV_SCALE_VPRIM(x) ((x * G_VPRIM)*DAC_SCALER_DAB)

#define SCALE_ITANK(x) (g_ITANK*(adcscalerDAB*(x - MEAS_PS_1V65_REF)))
#define SCALE_SYSTEM_TEMP(x) ((x-0.5)/(0.01) + 0)

#define MEAS_DAB_IPRIM_TANK ((float)HWREGH(ADCDRESULT_BASE + (uint32_t)ADC_SOC_NUMBER0))  //SOCA
#define MEAS_DAB_ISEC_TANK ((float)HWREGH(ADCARESULT_BASE + (uint32_t)ADC_SOC_NUMBER0))  //SOCA
#define MEAS_DAB_IPRIM ((float)HWREGH(ADCDRESULT_BASE + (uint32_t)ADC_SOC_NUMBER3))  //SOCA
#define MEAS_DAB_ISEC ((float)HWREGH(ADCARESULT_BASE + (uint32_t)ADC_SOC_NUMBER1))  //SOCA

#define MEAS_DAB_VPRIM ((float)HWREGH(ADCBRESULT_BASE + (uint32_t)ADC_SOC_NUMBER0))  //SOCA
#define MEAS_DAB_VSEC ((float)HWREGH(ADCCRESULT_BASE + (uint32_t)ADC_SOC_NUMBER0))  //SOCA

#define DAB_MAX_DEADBAND_DELAY 16380
#define DAB_STD_DEADBAND_DELAY 20
#define DAB_DEBUG_DEADBAND_DELAY 0
#define thetaMax 1.0f
#define DAB_INIT_DURATION 1.0f // seconds
#define DAB_CTRL_PERIOD (4000.0f/200000000.0f)
#define DAB_RAMP_THETA_STEP thetaMax/(DAB_INIT_DURATION/DAB_CTRL_PERIOD)
static inline void DAB_setDeadband(uint32_t delay);
float targetTheta = 0;

#define DAB_MAX_PHASE_SHIFT_INT ((DAB_PRIM1_TBPRD/2)-1)
#define DAB_PHASE_SHIFT_DELAY 2 // number of cycles it takes to propogate the sync pulse
#define DAB_MIN_PHASE_SHIFT (1.0/(DAB_PRIM1_TBPRD*2))


//
// Globals
//
uint16_t myADC0Results[RESULTS_BUFFER_SIZE];   // Buffer for results
uint16_t myADC1Results[RESULTS_BUFFER_SIZE];
uint16_t index0;                              // Index into result buffer
uint16_t index1;
volatile uint16_t bufferFull;                // Flag to indicate buffer is full

struct CUR_state{
    //ISEC
    volatile float ISEC;

    //VSEC
    volatile float VSEC;

    //IPRIM
    volatile float IPRIM;

    //IPRIM_TANK
    volatile float IPRIM_TANK;

    //ISEC_TANK
    volatile float ISEC_TANK;

    //VPRIM
    volatile float VPRIM;

    //PWR
    float Pprim;
    float Psec;

    //Deadband Softstart
    volatile uint32_t deadband;

    // Pri to sec phase shift
    volatile float theta;
    // PWM Counter value
    volatile uint16_t pwmPeriod;
    volatile uint16_t CMPAVal;

    //ISEC
    volatile float ISEC_RAW;

    //VSEC
    volatile float VSEC_RAW;

    //IPRIM
    volatile float IPRIM_RAW;

    //IPRIM_TANK
    volatile float IPRIM_TANK_RAW;

    //ISEC_TANK
    volatile float ISEC_TANK_RAW;

    //VPRIM
    volatile float VPRIM_RAW;
};
struct CUR_state cur_state;


//// Function to process the SOCA measurements
#pragma FUNC_ALWAYS_INLINE(DAB_SOCA_MEAS)
inline void DAB_SOCA_MEAS(void)
{
    meas1v65 = MEAS_PS_1V65_REF;
    //IPRIM
    cur_state.IPRIM = SCALE_IPRIM(MEAS_DAB_IPRIM);

    //ISEC
    cur_state.ISEC = SCALE_ISEC(MEAS_DAB_ISEC);

    //VSEC
    cur_state.VSEC = SCALE_VSEC(MEAS_DAB_VSEC);

    //IPRIM_TANK
    cur_state.IPRIM_TANK = SCALE_ITANK(MEAS_DAB_IPRIM_TANK);

    //ISEC_TANK
    cur_state.ISEC_TANK = SCALE_ITANK(MEAS_DAB_ISEC_TANK);

    //VSEC
    cur_state.VPRIM = SCALE_VPRIM(MEAS_DAB_VPRIM);

    //*********************************//
    //raw measurements
    //IPRIM
    cur_state.IPRIM_RAW = MEAS_DAB_IPRIM;

    //ISEC
    cur_state.ISEC_RAW = MEAS_DAB_ISEC;

    //VSEC
    cur_state.VSEC_RAW = MEAS_DAB_VSEC;

    //IPRIM_TANK
    cur_state.IPRIM_TANK_RAW = MEAS_DAB_IPRIM_TANK;

    //ISEC_TANK
    cur_state.ISEC_TANK_RAW = MEAS_DAB_ISEC_TANK;

    //VSEC
    cur_state.VPRIM_RAW = SCALE_VPRIM(MEAS_DAB_VPRIM);
}

#define GET_CMPA(base) ((uint16_t)((HWREG(base + EPWM_O_CMPA) &0xFFFF0000UL) >> 16U))

#define GET_CMPA_UP_ACTION(base)   ((HWREGH(base + EPWM_O_AQCTLA) >> ((uint16_t)EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA)) & 3U)
#define GET_CMPA_DOWN_ACTION(base)   ((HWREGH(base + EPWM_O_AQCTLA) >> ((uint16_t)EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA)) & 3U)
// Phase shift controller for primary and secondary lagging phases
 inline void DAB_setPhaseShift_Base(uint32_t base, float32_t phase_shift, uint16_t cmpaVal, uint16_t period)
{
    // All phase shifts are referenced to phase 1 of primary (epwm 8)

    //Wrap the phase shift
    if(phase_shift>1.0)
        phase_shift = 1.0 - phase_shift; // Equivalent to negative phase vs ph pri 1
    if(phase_shift<-1.0)
        phase_shift = phase_shift-1.0; // Equivalent to posistive phase vs ph pri 1

    float phase_shift_scaled = ((phase_shift)*(float)(period)) - (float)DAB_PHASE_SHIFT_DELAY;
       uint32_t phase_shift_int;


       if(phase_shift_scaled > 0){

           // Set CMPB equal to TBPSH Register value -1
           //Set the down count action to the same as CMPA down count action
           //Do nothing on upcount

           // Get action
           EPWM_ActionQualifierOutput output = GET_CMPA_DOWN_ACTION(base);

            // Clear CMPB upcount event
           EPWM_setActionQualifierAction(base,EPWM_AQ_OUTPUT_A,EPWM_AQ_OUTPUT_NO_CHANGE,
                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);


           if(phase_shift_scaled > myEPWM0_TBPRD){
               phase_shift_scaled = myEPWM0_TBPRD;

           }

           phase_shift_int = (uint16_t)phase_shift_scaled;

           // Set CMPB = CMPA
           uint16_t cmpb = cmpaVal;

           // Check if phase_shift is <= CMPA value
           if(phase_shift_int <= cmpb && phase_shift_int>1)
           {
               // Next count after sync will trigger event
               cmpb = (phase_shift_int - 1);
           }

           EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_B, cmpb);

           // Set CMPB downcount evet
           EPWM_setActionQualifierAction(base,EPWM_AQ_OUTPUT_A,output,
                                         EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

           // Set count down on sync
           EPWM_setCountModeAfterSync(base, EPWM_COUNT_MODE_DOWN_AFTER_SYNC);

       } else {


         //Set the up count action to the same as CMPA down count action
         //Do nothing on down count

         // Get action
         EPWM_ActionQualifierOutput output = GET_CMPA_UP_ACTION(base);



        // Clear CMPB downcount evet
        EPWM_setActionQualifierAction(base,EPWM_AQ_OUTPUT_A,EPWM_AQ_OUTPUT_NO_CHANGE,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);


           if(phase_shift_scaled < -myEPWM0_TBPRD){
               phase_shift_scaled = -myEPWM0_TBPRD;
           }


           phase_shift_int = (uint16_t)(-phase_shift_scaled);

           // Set CMPB = CMPA
           uint16_t cmpb = cmpaVal;

           // Check if phase_shift is >= CMPA value
           if(phase_shift_int >= cmpb && phase_shift_int<myEPWM0_TBPRD)
           {
               // Next count after sync will trigger event
               cmpb = (phase_shift_int + 1);
           }

           EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_B, cmpb);

           // Set CMPB upcount event
           EPWM_setActionQualifierAction(base,EPWM_AQ_OUTPUT_A,output,
               EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

           EPWM_setCountModeAfterSync(base, EPWM_COUNT_MODE_UP_AFTER_SYNC);
       }

       //Set the phase shift
       EPWM_setPhaseShift(base, phase_shift_int);

}



//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    // 
    // Board Initialization
    // - Set up the ADC and initialize the SOC
    // - Enable ADC interrupt
    // - Signal Mode           : single-ended
    // - Conversion Resolution : 12-bit;
    //
    Board_init();
    cur_state.deadband = DAB_STD_DEADBAND_DELAY;
    DAB_setDeadband(cur_state.deadband);
    cur_state.theta = 0;
    cur_state.pwmPeriod = myEPWM0_TBPRD;
    cur_state.CMPAVal = cur_state.pwmPeriod*0.5;
    targetTheta = 0;



    //
    // Initialize results buffer
    //
    for(index0 = 0; index0 < RESULTS_BUFFER_SIZE; index0++)
    {
        myADC0Results[index0] = 1;
        myADC1Results[index0] = 1;
    }

    index0 = 0;
    bufferFull = 0;

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop indefinitely
    //
    while(1)
    {

        //
        // Wait while ePWM1 causes ADC conversions which then cause interrupts.
        // When the results buffer is filled, the bufferFull flag will be set.
        //
        while(bufferFull == 0)
        {
        }
        bufferFull = 0;     // Clear the buffer full flag


        //
        // Software breakpoint. At this point, conversion results are stored in
        // myADC0Results.
        //
        // Hit run again to get updated conversions.
        //
        ESTOP0;
    }
}



//
// adcD1ISR - ADC D Interrupt 1 ISR
//
__interrupt void INT_ADCD_BASE_1_ISR(void)
{
    //
    // Add the latest result to the buffer
    //
    DAB_SOCA_MEAS();
//    myADC0Results[index0++] = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER0);

    //
    // Set the bufferFull flag if the buffer is full
    //
    if(RESULTS_BUFFER_SIZE <= index0)
    {
        index0 = 0;
        bufferFull = 1;
    }

    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(ADCD_BASE_BASE, ADC_INT_NUMBER1);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(ADCD_BASE_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(ADCD_BASE_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(ADCD_BASE_BASE, ADC_INT_NUMBER1);
    }

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INT_ADCD_BASE_1_INTERRUPT_ACK_GROUP);
}


//
// adcA1ISR - ADC A Interrupt 1 ISR
//
__interrupt void INT_ADCA_BASE_1_ISR(void)
{
    //
    // Add the latest result to the buffer
    //
    //    myADC1Results[index1++] = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
//    DAB_SOCA_MEAS();
    //
    // Set the bufferFull flag if the buffer is full
    //
    if(RESULTS_BUFFER_SIZE <= index1)
    {
        index1 = 0;
        bufferFull = 1;
    }

    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(ADCA_BASE_BASE, ADC_INT_NUMBER1);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(ADCA_BASE_BASE, ADC_INT_NUMBER1);
    }

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INT_ADCA_BASE_1_INTERRUPT_ACK_GROUP);
}

static inline void DAB_setDeadband(uint32_t delay){
    // Set deadtime. For some reason, the driverlib functions don't work
    HWREGH(myEPWM0_BASE + EPWM_O_DBRED) = delay;
    HWREGH(DAB_PRIM2_BASE + EPWM_O_DBRED) = delay;
    HWREGH(DAB_SEC1_BASE + EPWM_O_DBRED) = delay;
    HWREGH(DAB_SEC2_BASE + EPWM_O_DBRED) = delay;

    HWREGH(myEPWM0_BASE + EPWM_O_DBFED) = delay;
    HWREGH(DAB_PRIM2_BASE + EPWM_O_DBFED) = delay;
    HWREGH(DAB_SEC1_BASE + EPWM_O_DBFED) = delay;
    HWREGH(DAB_SEC2_BASE + EPWM_O_DBFED) = delay;

    HWREGH(myEPWM0_BASE + EPWM_O_DBCTL) |= (1 << 6); // Force shadow-to-active load
    HWREGH(DAB_PRIM2_BASE + EPWM_O_DBCTL) |= (1 << 6);
    HWREGH(DAB_SEC1_BASE + EPWM_O_DBCTL) |= (1 << 6);
    HWREGH(DAB_SEC2_BASE + EPWM_O_DBCTL) |= (1 << 6);
}

void DAB_enablePWM(void){
    cur_state.deadband = DAB_STD_DEADBAND_DELAY;
    DAB_setDeadband(cur_state.deadband);
}

void DAB_ManualPhaseShift(float desired_theta){
    targetTheta = desired_theta;
}


#pragma FUNC_ALWAYS_INLINE(DAB_Control_ISR)
__attribute__((ramfunc)) inline void DAB_Control_ISR(void){
//    if (cur_state.deadband > DAB_STD_DEADBAND_DELAY){
//        DAB_setDeadband(cur_state.deadband);
//        cur_state.deadband -= 1;
//    }
//    else{
    DAB_enablePWM();

    //ramp phase shift
    if(cur_state.theta != targetTheta){
        float delta_theta = targetTheta - cur_state.theta;
        cur_state.theta += (delta_theta > 0 ? 1 : -1) * DAB_RAMP_THETA_STEP;

    }

    // Update operating frequency
    EPWM_setTimeBasePeriod(myEPWM0_BASE, cur_state.pwmPeriod);
    EPWM_setCounterCompareValue(myEPWM0_BASE, EPWM_COUNTER_COMPARE_A, cur_state.CMPAVal);

    DAB_setPhaseShift_Base(DAB_SEC1_BASE, cur_state.theta, cur_state.CMPAVal, cur_state.pwmPeriod);
    DAB_setPhaseShift_Base(DAB_SEC2_BASE, cur_state.theta, cur_state.CMPAVal, cur_state.pwmPeriod);
    //DAB_setPhaseShift(dab_state.theta);
    // Set global one shot latch (enables DAB_PRIM1 sync out oneshot)
    EPWM_setGlobalLoadOneShotLatch(myEPWM0_BASE);
    EPWM_startOneShotSync(myEPWM0_BASE);

}

__attribute__((ramfunc)) __interrupt void INT_myCPUTIMER2_ISR(void){
    DAB_Control_ISR();
}
