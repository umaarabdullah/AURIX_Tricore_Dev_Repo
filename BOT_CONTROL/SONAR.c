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

#define ECHO_SONAR_1         &MODULE_P14,0      /* Sonar_1 Echo Pin 22 */
#define TRIG_SONAR_1         &MODULE_P14,1      /* Sonar_1 Trig Pin 23 */

#define ECHO_SONAR_2         &MODULE_P00,1      /* Sonar_2 Echo Pin 27 */
#define TRIG_SONAR_2         &MODULE_P00,8      /* Sonar_2 Trig Pin 26 */

#define ECHO_SONAR_3         &MODULE_P00,3      /* Sonar_3 Echo Pin 31 */
#define TRIG_SONAR_3         &MODULE_P00,10      /* Sonar_3 Trig Pin 30 */

#define ECHO_SONAR_4         &MODULE_P00,5      /* Sonar_4 Echo Pin 35 */
#define TRIG_SONAR_4         &MODULE_P00,12      /* Sonar_4 Trig Pin 34 */

#define PULSE_TIME   10                 /* 10us */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
double Speed_of_Sound = 343.0;            /* Speed of sound m/s *

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void SEND_PULSE_SONAR_1(void);

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

/*********************************************************************************************************************/
/*---------------------------------------------Initialization Functions of the 4 Sonar Sensors----------------------------------------------*/
/*********************************************************************************************************************/
void initSonar_1(void){
    IfxPort_setPinModeOutput(TRIG_SONAR_1, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);                 /* Configure Trig pin as output */
    IfxPort_setPinModeInput(ECHO_SONAR_1, IfxPort_Mode_inputPullDown);                                              /* Configure Echo pin as input with a pull-down resistor enabled to maintain a logic low by default */
}

void initSonar_2(void){
    IfxPort_setPinModeOutput(TRIG_SONAR_2, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);                 /* Configure Trig pin as output */
    IfxPort_setPinModeInput(ECHO_SONAR_2, IfxPort_Mode_inputPullDown);                                              /* Configure Echo pin as input with a pull-down resistor enabled to maintain a logic low by default */
}

void initSonar_3(void){
    IfxPort_setPinModeOutput(TRIG_SONAR_3, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);                 /* Configure Trig pin as output */
    IfxPort_setPinModeInput(ECHO_SONAR_3, IfxPort_Mode_inputPullDown);                                              /* Configure Echo pin as input with a pull-down resistor enabled to maintain a logic low by default */
}

void initSonar_4(void){
    IfxPort_setPinModeOutput(TRIG_SONAR_4, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);                 /* Configure Trig pin as output */
    IfxPort_setPinModeInput(ECHO_SONAR_4, IfxPort_Mode_inputPullDown);                                              /* Configure Echo pin as input with a pull-down resistor enabled to maintain a logic low by default */
}

/*********************************************************************************************************************/
/*---------------------------------------------SEND_PULSE__TRIGGER Functions of the 4 Sonar Sensors----------------------------------------------*/
/*********************************************************************************************************************/
/* set the Trig pin high for at least 10 microseconds, and then set it low again. */
void SEND_PULSE_SONAR_1(void){
    Ifx_TickTime pulse_ticks = IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, PULSE_TIME);

    IfxPort_setPinLow(TRIG_SONAR_1);    // Set Trig pin low
    waitTime(pulse_ticks);              // Wait for 10 microseconds
    IfxPort_setPinHigh(TRIG_SONAR_1);   // Set Trig pin High
    waitTime(pulse_ticks);              // Wait for 10 microseconds
    IfxPort_setPinLow(TRIG_SONAR_1);    // Set Trig pin low
}

/* set the Trig pin high for at least 10 microseconds, and then set it low again. */
void SEND_PULSE_SONAR_2(void){
    Ifx_TickTime pulse_ticks = IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, PULSE_TIME);

    IfxPort_setPinLow(TRIG_SONAR_2);    // Set Trig pin low
    waitTime(pulse_ticks);              // Wait for 10 microseconds
    IfxPort_setPinHigh(TRIG_SONAR_2);   // Set Trig pin High
    waitTime(pulse_ticks);              // Wait for 10 microseconds
    IfxPort_setPinLow(TRIG_SONAR_2);    // Set Trig pin low
}

/* set the Trig pin high for at least 10 microseconds, and then set it low again. */
void SEND_PULSE_SONAR_3(void){
    Ifx_TickTime pulse_ticks = IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, PULSE_TIME);

    IfxPort_setPinLow(TRIG_SONAR_3);    // Set Trig pin low
    waitTime(pulse_ticks);              // Wait for 10 microseconds
    IfxPort_setPinHigh(TRIG_SONAR_3);   // Set Trig pin High
    waitTime(pulse_ticks);              // Wait for 10 microseconds
    IfxPort_setPinLow(TRIG_SONAR_3);    // Set Trig pin low
}

/* set the Trig pin high for at least 10 microseconds, and then set it low again. */
void SEND_PULSE_SONAR_4(void){
    Ifx_TickTime pulse_ticks = IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, PULSE_TIME);

    IfxPort_setPinLow(TRIG_SONAR_4);    // Set Trig pin low
    waitTime(pulse_ticks);              // Wait for 10 microseconds
    IfxPort_setPinHigh(TRIG_SONAR_4);   // Set Trig pin High
    waitTime(pulse_ticks);              // Wait for 10 microseconds
    IfxPort_setPinLow(TRIG_SONAR_4);    // Set Trig pin low
}


/*********************************************************************************************************************/
/*---------------------------------------------CALCULATE_DISTANCE__FROM_ECHO Functions of the 4 Sonar Sensors----------------------------------------------*/
/*********************************************************************************************************************/
/*
 * Function to read the distance from the ultrasonic sensor
 * Return the distance in centimeters
*/
double read_distance_sonar_1(void){

    double distance;                        // Unit: CM
    int timeout = 1000000;                  // Timeout in microseconds
    uint64 start_time = 0, end_time = 0, elapsed_time = 0;

    // Send a pulse to the HC-SR04
    SEND_PULSE_SONAR_1();

    // Wait pulseIn i.e for the Echo pin to go high
    while (!IfxPort_getPinState(ECHO_SONAR_1) && timeout > 0) {
        timeout--;
    }

    start_time = getTime();

    // Wait for the Echo pin to go low
    while (IfxPort_getPinState(ECHO_SONAR_1) && timeout > 0) {
        timeout--;
    }

    // Get pulseIn time
    end_time = getTime();
    elapsed_time = (end_time - start_time);     // not 100% accurate need to account for cycle time. Accurate upto 10us

//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r start_Time: %llu us\n\r",start_time);
//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r end_Time: %llu us\n\r",end_time);
//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Sonar ECHO time: %llu us\n\r",elapsed_time);
//elapsed(since)
    if(elapsed_time <= 0)
        return 0.0;
    // Calculate distance from elapsed time
    distance = (double) (((double)elapsed_time * Speed_of_Sound) / (double)(2*1000000))*(double)100;

    return distance;
}

double read_distance_sonar_2(void){

    double distance;                        // Unit: CM
    int timeout = 1000000;                  // Timeout in microseconds
    uint64 start_time = 0, end_time = 0, elapsed_time = 0;

    // Send a pulse to the HC-SR04
    SEND_PULSE_SONAR_2();

    // Wait pulseIn i.e for the Echo pin to go high
    while (!IfxPort_getPinState(ECHO_SONAR_2) && timeout > 0) {
        timeout--;
    }

    start_time = getTime();

    // Wait for the Echo pin to go low
    while (IfxPort_getPinState(ECHO_SONAR_2) && timeout > 0) {
        timeout--;
    }

    // Get pulseIn time
    end_time = getTime();
    elapsed_time = (end_time - start_time);     // not 100% accurate need to account for cycle time. Accurate upto 10us

//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r start_Time: %llu us\n\r",start_time);
//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r end_Time: %llu us\n\r",end_time);
//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Sonar ECHO time: %llu us\n\r",elapsed_time);
//elapsed(since)
    if(elapsed_time <= 0)
        return 0.0;
    // Calculate distance from elapsed time
    distance = (double) (((double)elapsed_time * Speed_of_Sound) / (double)(2*1000000))*(double)100;

    return distance;
}

double read_distance_sonar_3(void){

    double distance;                        // Unit: CM
    int timeout = 1000000;                  // Timeout in microseconds
    uint64 start_time = 0, end_time = 0, elapsed_time = 0;

    // Send a pulse to the HC-SR04
    SEND_PULSE_SONAR_3();

    // Wait pulseIn i.e for the Echo pin to go high
    while (!IfxPort_getPinState(ECHO_SONAR_3) && timeout > 0) {
        timeout--;
    }

    start_time = getTime();

    // Wait for the Echo pin to go low
    while (IfxPort_getPinState(ECHO_SONAR_3) && timeout > 0) {
        timeout--;
    }

    // Get pulseIn time
    end_time = getTime();
    elapsed_time = (end_time - start_time);     // not 100% accurate need to account for cycle time. Accurate upto 10us

//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r start_Time: %llu us\n\r",start_time);
//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r end_Time: %llu us\n\r",end_time);
//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Sonar ECHO time: %llu us\n\r",elapsed_time);
//elapsed(since)
    if(elapsed_time <= 0)
        return 0.0;
    // Calculate distance from elapsed time
    distance = (double) (((double)elapsed_time * Speed_of_Sound) / (double)(2*1000000))*(double)100;

    return distance;
}

double read_distance_sonar_4(void){

    double distance;                        // Unit: CM
    int timeout = 1000000;                  // Timeout in microseconds
    uint64 start_time = 0, end_time = 0, elapsed_time = 0;

    // Send a pulse to the HC-SR04
    SEND_PULSE_SONAR_4();

    // Wait pulseIn i.e for the Echo pin to go high
    while (!IfxPort_getPinState(ECHO_SONAR_4) && timeout > 0) {
        timeout--;
    }

    start_time = getTime();

    // Wait for the Echo pin to go low
    while (IfxPort_getPinState(ECHO_SONAR_4) && timeout > 0) {
        timeout--;
    }

    // Get pulseIn time
    end_time = getTime();
    elapsed_time = (end_time - start_time);     // not 100% accurate need to account for cycle time. Accurate upto 10us

//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r start_Time: %llu us\n\r",start_time);
//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r end_Time: %llu us\n\r",end_time);
//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Sonar ECHO time: %llu us\n\r",elapsed_time);
//elapsed(since)
    if(elapsed_time <= 0)
        return 0.0;
    // Calculate distance from elapsed time
    distance = (double) (((double)elapsed_time * Speed_of_Sound) / (double)(2*1000000))*(double)100;

    return distance;
}

