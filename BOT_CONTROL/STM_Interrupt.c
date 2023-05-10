/*
 * STM_Interrupt.c
 *
 *  Created on: May 7, 2023
 *      Author: Umaar
 */

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "STM_Interrupt.h"
#include "Bsp.h"
#include "IfxPort.h"
#include "IfxStm.h"
#include "UART.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define ISR_PRIORITY_STM        40                              /* Priority for interrupt ISR                       */
#define TIMER_INT_TIME          10                              /* Time between interrupts in us. Interrupt will be triggered every 10us                    */

#define LED                     &MODULE_P10,2                   /* LED toggled in Interrupt Service Routine (ISR)   */
#define STM                     &MODULE_STM0                    /* STM0 is used in this example                     */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IfxStm_CompareConfig g_STMConf;                                 /* STM configuration structure                      */
Ifx_TickTime g_ticksForDelayus;                                 /* Variable to store the number of ticks to wait    */

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void initLED(void);
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

uint64 uscount;

uint64 getTime(void){
    return uscount;
}

void isrSTM(void)
{
    uscount+=TIMER_INT_TIME;
    /* Update the compare register value that will trigger the next interrupt and toggle the LED */
    IfxStm_increaseCompare(STM, g_STMConf.comparator, g_ticksForDelayus);
}

/* Function to initialize the STM */
void initSTM(void)
{
    uscount = 0;

    IfxStm_initCompareConfig(&g_STMConf);           /* Initialize the configuration structure with default values   */

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

    initSTM();                                      /* Configure the STM module                                     */
}
