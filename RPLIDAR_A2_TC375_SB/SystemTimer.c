/*
 * SystemTimer.c
 *
 *  Created on: Dec 30, 2023
 *      Author: Umaar
 */

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "SystemTimer.h"
#include "Bsp.h"
#include "IfxPort.h"
#include "IfxStm.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define ISR_PRIORITY_STM        40                              /* Priority for interrupt ISR                       */
#define TIMER_INT_TIME          10                              /* Time between interrupts in us. Interrupt will be triggered every 10us                    */

#define STM                     &MODULE_STM0                    /* STM0 is used in this example                     */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IfxStm_CompareConfig g_STMConf;                                 /* STM configuration structure                      */
Ifx_TickTime g_ticksForDelayus;                                 /* Variable to store the number of ticks to wait    */
uint32 stm_clock_frequency;                                     /* STM Clock frequency in HZ */
uint32 stm_comp_reg_val;                                        /* STM Comparator_0 register value */

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void initSTM(void);

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Macro to define Interrupt Service Routine.
 * This macro makes following definitions:
 * 1) Define linker section as .intvec_tc<vector number>_<interrupt priority>.
 * 2) define compiler specific attribute for the interrupt functions.
 * 3) define the Interrupt service routine as ISR function.
 *
 * IFX_INTERRUPT(isr, vectabNum, priority)
 *  - isr: Name of the ISR function.
 *  - vectabNum: Vector table number.
 *  - priority: Interrupt priority. Refer Usage of Interrupt Macro for more details.
 */
IFX_INTERRUPT(isrSTM, 0, ISR_PRIORITY_STM);

uint64 __uscount;

uint64 getTime(void){

    /* Here STM refers to System Timer Module */

    uint64 stm_val = IfxStm_get(STM);

    // Compare last updated compare value and stm value to get how many ticks(clock pulses) has elapsed so far
    uint64 extra_ticks = (stm_val - (uint64)stm_comp_reg_val);
    uint64 inverse_clock_period_us = (uint64)stm_clock_frequency / (uint64)1000000;
    uint64 extra_time_us = extra_ticks/inverse_clock_period_us;

    // how many ticks it has already counted before triggering the interrupt divided by the freq to get microsecond time
    return (__uscount + extra_time_us);
}

void isrSTM(void)
{
    __uscount+=TIMER_INT_TIME;

    // comparator value gets updated with fixed number of ticks at each interrupt *** ticks = g_ticksForDelayus ***
    stm_comp_reg_val = IfxStm_getCompare(STM, IfxStm_Comparator_0);

    /* Update the compare register value that will trigger the next interrupt and toggle the LED */
    IfxStm_increaseCompare(STM, g_STMConf.comparator, g_ticksForDelayus);
}

/* Function to initialize the STM */
void initSTM(void)
{
    __uscount = 0;

    IfxStm_initCompareConfig(&g_STMConf);           /* Initialize the configuration structure with default values   */

    g_STMConf.comparator = IfxStm_Comparator_0;     /* Set Comparator_0 as the selected comparator of the timer     */

    g_STMConf.triggerPriority = ISR_PRIORITY_STM;   /* Set the priority of the interrupt                            */
    g_STMConf.typeOfService = IfxSrc_Tos_cpu0;      /* Set the service provider for the interrupts                  */
    g_STMConf.ticks = g_ticksForDelayus;            /* Set the number of ticks after which the timer triggers an
                                                     * interrupt for the first time                                 */
    IfxStm_initCompare(STM, &g_STMConf);            /* Initialize the STM with the user configuration               */
}

/* Function to initialize all the peripherals and variables used */
void initPeripherals(void)
{
    /* Initialize time constant for microsecond delay */
    g_ticksForDelayus = IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, TIMER_INT_TIME);

    stm_clock_frequency = (uint32)IfxStm_getFrequency(STM);

    initSTM();                                      /* Configure the STM module                                     */
}