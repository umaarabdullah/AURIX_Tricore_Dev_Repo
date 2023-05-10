/*
 * Cpu0_Main.c
 *
 *  Created on: May 7, 2023
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

#define WAIT_TIME   2000
int duty=90;

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
    
    initGtmPwm();
    initNavigation();
    setDutyCycleEn1(duty);
    setDutyCycleEn2(duty);

    Ifx_TickTime ticks = IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME);

    SONAR_INIT();       /* Initialize the sonar sensor module*/
    initPeripherals();  /* Initialize the STM module */

    while(1)
    {
        double sonar_dist = SONAR_MEASURE_DISTANCE();
        IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\rDistance: %lfcm\n\r",sonar_dist);

        setDutyCycleEn1(duty);
        setDutyCycleEn2(duty);

        // g_ascStandardInterface has to be passed as io object
        IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\rCurrent PWM Duty Cycle: %d\n\r", duty);

//        forward();
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

