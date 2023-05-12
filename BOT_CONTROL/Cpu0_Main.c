/*
 * Cpu0_Main.c
 *
 *  Created on: Apr 1, 2023
 *      Author: Umaar
 */

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Navigation.h"
#include "GTM_PWM.h"
#include "Bsp.h"
#include "STM_Interrupt.h"
#include "SONAR.h"
#include "UART.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define WAIT_TIME   2000
#define THRESHOLD_DISTANCE 10               /* Object within 10cm will defined as obstacle detected */

/*********************************************************************************************************************/
/*------------------------------------------------------Global Variables-------------------------------------------------------*/
/*********************************************************************************************************************/
int duty = 90;                          /* The PWM signal duty cycle represents the percentage of time the signal remains in the logic high state. */

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;

void core0_main(void)
{
    IfxCpu_enableInterrupts();
    
    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
    
    initGtmPwm();                   /* initialize pwm for h-bridge enable pins */
    initNavigation();               /* initialize in pins for h-bridge input pins for navigation */
    initSonar();                    /* Initialize the sonar sensor module*/
    initPeripherals();              /* Initialize the STM module */

    /* Set the duty cycle. Here the argument duty cycle is in percentage */
    setDutyCycleEn1(duty);
    setDutyCycleEn2(duty);

    // Get ticks for waitTime
    Ifx_TickTime ticks = IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME);

    while(1)
    {
        double sonar_dist = SONAR_MEASURE_DISTANCE();       // API for getting distance calculated with the help of ultrasonic sensor
        IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Distance: %lfcm\n\r",sonar_dist);

        // Repeatedly set duty cycle for changing speed
        setDutyCycleEn1(duty);
        setDutyCycleEn2(duty);

        // g_ascStandardInterface has to be passed as io object
//        IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Current PWM Duty Cycle: %d\n\r", duty);

//        if(sonar_dist > THRESHOLD_DISTANCE)
//            forward();
//        else
//            stop();

        waitTime(ticks);
//        stop();
//        waitTime(ticks);
//
//        hard_left();
//        waitTime(2*ticks);
//        stop();
//        waitTime(ticks);
//
//        hard_right();
//        waitTime(2*ticks);
//        stop();
//        waitTime(ticks);
//
//        backward();
//        waitTime(ticks);
//        stop();
//        waitTime(ticks);
    }
}

