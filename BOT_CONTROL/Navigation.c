/*
 * Navigation.c
 *
 *  Created on: Mar 31, 2023
 *      Author: plabon
 */


#include "IfxPort.h"

#define IN_1         &MODULE_P10,2
#define IN_2         &MODULE_P10,1
#define IN_3         &MODULE_P10,3
#define IN_4         &MODULE_P10,5

/*----------------------------------Function Implementations------------------------------*/

void initNavigation(void)
{
    /* Initialization of the input pins for motor driver */
    IfxPort_setPinModeOutput(IN_1, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(IN_2, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(IN_3, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(IN_4, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(IN_1);
    IfxPort_setPinLow(IN_2);
    IfxPort_setPinLow(IN_3);
    IfxPort_setPinLow(IN_4);
}


void forward (void)
{
    // left side forward
    IfxPort_setPinLow(IN_3);        // 0
    IfxPort_setPinHigh(IN_4);       // 1
    // right side forward
    IfxPort_setPinLow(IN_1);        // 0
    IfxPort_setPinHigh(IN_2);       // 1

}

void backward(void){
    // left side reverse
    IfxPort_setPinHigh(IN_3);
    IfxPort_setPinLow(IN_4);
    // right side reverse
    IfxPort_setPinHigh(IN_1);
    IfxPort_setPinLow(IN_2);
}

void hard_left (void)
{
    // left side reverse
    IfxPort_setPinHigh(IN_3);
    IfxPort_setPinLow(IN_4);
    // right side forward
    IfxPort_setPinLow(IN_1);
    IfxPort_setPinHigh(IN_2);
}

void hard_right (void)
{
    // left side forward
    IfxPort_setPinLow(IN_3);
    IfxPort_setPinHigh(IN_4);
    // right side reverse
    IfxPort_setPinHigh(IN_1);
    IfxPort_setPinLow(IN_2);
}

void stop(void){            // 0 0 0 0
    IfxPort_setPinLow(IN_1);
    IfxPort_setPinLow(IN_2);
    IfxPort_setPinLow(IN_3);
    IfxPort_setPinLow(IN_4);
}










