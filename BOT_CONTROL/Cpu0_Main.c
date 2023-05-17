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
#include "Ultrasonic_Based_Pid_Control.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define WAIT_TIME   2000

/*********************************************************************************************************************/
/*------------------------------------------------------Global Variables-------------------------------------------------------*/
/*********************************************************************************************************************/
int duty = 100;                          /* The PWM signal duty cycle represents the percentage of time the signal remains in the logic high state. */

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

    initSonar_1();                  /* Initialize the sonar sensor module*/
    initSonar_2();                  /* Initialize the sonar sensor module*/
    initSonar_3();                  /* Initialize the sonar sensor module*/
    initSonar_4();                  /* Initialize the sonar sensor module*/

    initPeripherals();              /* Initialize the STM module */

    /* Set the duty cycle. Here the argument duty cycle is in percentage */
    setDutyCycleEn1(duty);
    setDutyCycleEn2(duty);

    // Get ticks for waitTime
    Ifx_TickTime ticks = IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME);

    while(1)
    {

        vehicle_control_obstacle_avoidance_mode();

//        forward();
//        waitTime(ticks);
//        stop();
//        waitTime(ticks);
//
//        hard_left();
//        waitTime(ticks);
//        stop();
//        waitTime(ticks);
//
//        hard_right();
//        waitTime(ticks);
//        stop();
//        waitTime(ticks);
//
//        backward();
//        waitTime(ticks);
//        stop();
//        waitTime(ticks);
    }
}

