/*
 * SONAR.c
 *
 *  Created on: May 7, 2023
 *      Author: Umaar
 */

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxPort.h"
#include "Bsp.h"
#include "UART.h"
#include "STM_Interrupt.h"

#define ECHO         &MODULE_P14,0      /* Echo Pin 22 */
#define TRIG         &MODULE_P14,1      /* Trig Pin 23 */

#define PULSE_TIME   10                 /* 10us */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
double Speed_of_Sound = 343.0;            /* Speed of sound m/s */
double distance;                          /* Unit: cm */

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void SEND_PULSE(void);

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
void SONAR_INIT(void){
    IfxPort_setPinModeOutput(TRIG, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeInput(ECHO, IfxPort_Mode_inputPullDown);      // a pull-down resistor to maintain a logic low by default

}

/* set the Trig pin high for at least 10 microseconds, and then set it low again. */
void SEND_PULSE(void){
    Ifx_TickTime pulse_ticks = IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, PULSE_TIME);

    IfxPort_setPinLow(TRIG);    // Set Trig pin low
    waitTime(pulse_ticks);      // Wait for 10 microseconds
    IfxPort_setPinHigh(TRIG);   // Set Trig pin High
    waitTime(pulse_ticks);      // Wait for 10 microseconds
    IfxPort_setPinLow(TRIG);    // Set Trig pin low
}

/* Function to measure the distance to an object using the HC-SR04 */
double SONAR_MEASURE_DISTANCE(void){

    int timeout = 1000000;  // Timeout in microseconds
    uint64 start_time, end_time, ping;

    // Send a pulse to the HC-SR04
    SEND_PULSE();

    // Wait pulseIn i.e for the Echo pin to go high
    while (!IfxPort_getPinState(ECHO) && timeout > 0) {
        timeout--;
    }

    // Start timer
    start_time = getTime();

    // Wait for the Echo pin to go low
    while (IfxPort_getPinState(ECHO) && timeout > 0) {
        timeout--;
    }

    // Stop timer and calculate elapsed time
    end_time = getTime();
    ping = (end_time - start_time);     // not 100% accurate need to account for cycle time. Accurate upto 10us

    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\rstart_Time: %dus\n\r",start_time);
    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\rend_Time: %dus\n\r",end_time);
    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\rPing: %dus\n\r",ping);

    // Calculate distance from elapsed time
    distance = (double) (((double)ping * Speed_of_Sound) / (double)(2*1000000))*(double)100;

    return distance;
}
