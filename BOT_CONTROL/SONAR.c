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

/***
 ****************************************Algorithm******************************************************************
 * 1. Send a short trigger pulse to the ultrasonic sensor.
        * Set the trigger pin of the ultrasonic sensor to logic high for a short duration (typically 10 microseconds).
        * Wait for the pulse to complete by setting the trigger pin to logic low.

   2. Wait for the ultrasonic sensor to send a response pulse.
        * Wait for the echo pin of the ultrasonic sensor to go high.
        * Start a timer to measure the time between the trigger pulse and the echo pulse.

   3. Measure the time it takes for the response pulse to return.

        * Wait for the echo pin of the ultrasonic sensor to go low.
        * Stop the timer and record the elapsed time.

   4. Calculate the distance based on the time of flight of the pulse and the speed of sound in air.
        * Calculate the time of flight by dividing the elapsed time by two (since the sound wave travels to and from the object).
        * Calculate the distance by multiplying the time of flight by the speed of sound in air (typically 343 meters per second).
        * Convert the distance to the desired unit (e.g. centimeters or inches) and return it.

    Note that the accuracy of the distance measurement may be affected by
    factors such as the temperature and humidity of the air, the shape and size of the objects in the path
    of the sound wave, and the accuracy of the timer and speed of sound calculations.
 *
 * */

void initSonar(void){
    IfxPort_setPinModeOutput(TRIG, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);                 /* Configure Trig pin as output */
    IfxPort_setPinModeInput(ECHO, IfxPort_Mode_inputPullDown);                                              /* Configure Echo pin as input with a pull-down resistor enabled to maintain a logic low by default */
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
    uint64 start_time, end_time, elapsed_time;

    // Send a pulse to the HC-SR04
    SEND_PULSE();

    // Wait pulseIn i.e for the Echo pin to go high
    while (!IfxPort_getPinState(ECHO) && timeout > 0) {
        timeout--;
    }

    start_time = getTime();

    // Wait for the Echo pin to go low
    while (IfxPort_getPinState(ECHO) && timeout > 0) {
        timeout--;
    }

    // Get pulseIn time
    end_time = getTime();
    elapsed_time = (end_time - start_time);     // not 100% accurate need to account for cycle time. Accurate upto 10us

    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\rstart_Time: %dus\n\r",start_time);
    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\rend_Time: %dus\n\r",end_time);
    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\relapsed_time: %dus\n\r",elapsed_time);

    // Calculate distance from elapsed time
    distance = (double) (((double)elapsed_time * Speed_of_Sound) / (double)(2*1000000))*(double)100;

    return distance;
}

