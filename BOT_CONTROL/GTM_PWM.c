/*
 * GTM_PWM.c
 *
 *  Created on: Apr 1, 2023
 *      Author: plabon
 */

#include "GTM_PWM.h"
#include "Ifx_Types.h"
#include "IfxGtm_Tom_Pwm.h"


#define ISR_PRIORITY_TOM    20                                      /* Interrupt priority number                    */
#define EN1                 IfxGtm_TOM1_0N_TOUT7_P02_7_OUT          /*PWM pin 8                                     */
#define EN2                 IfxGtm_TOM0_3N_TOUT6_P02_6_OUT          /*PWM pin 9                                     */
#define PWM_PERIOD          50000                                   /* PWM period for the TOM (2khz PWM frequency)  */


/*-------------Global variables-----------------*/

IfxGtm_Tom_Pwm_Config g_tomConfig1;                                  /* Timer configuration structure                */
IfxGtm_Tom_Pwm_Driver g_tomDriver1;                                  /* Timer Driver structure                       */
IfxGtm_Tom_Pwm_Config g_tomConfig2;                                  /* Timer configuration structure                */
IfxGtm_Tom_Pwm_Driver g_tomDriver2;                                  /* Timer Driver structure                       */


/*-----------Function Implementations------------*/

/* This function initializes the TOM PWM for p02_7(en1) p02_6(en2) */
void initGtmPwm(void)
{
    IfxGtm_enable(&MODULE_GTM);                                     /* Enable GTM                                   */

    IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_FXCLK);   /* Enable the FXU clock                         */

    /* Initialize the configuration structure with default parameters */
    IfxGtm_Tom_Pwm_initConfig(&g_tomConfig1, &MODULE_GTM);
    IfxGtm_Tom_Pwm_initConfig(&g_tomConfig2, &MODULE_GTM);

    /*configuration for EN1*/
    g_tomConfig1.tom = EN1.tom;                                      /* Select the TOM depending on the LED          */
    g_tomConfig1.tomChannel = EN1.channel;                           /* Select the channel depending on the LED      */
    g_tomConfig1.period = PWM_PERIOD;                                /* Set the timer period                         */
    g_tomConfig1.pin.outputPin = &EN1;                               /* Set the LED port pin as output               */
    g_tomConfig1.synchronousUpdateEnabled = TRUE;                    /* Enable synchronous update                    */

    /*configuration for EN2*/
    g_tomConfig2.tom = EN2.tom;                                      /* Select the TOM depending on the LED          */
    g_tomConfig2.tomChannel = EN2.channel;                           /* Select the channel depending on the LED      */
    g_tomConfig2.period = PWM_PERIOD;                                /* Set the timer period                         */
    g_tomConfig2.pin.outputPin = &EN2;                               /* Set the LED port pin as output               */
    g_tomConfig2.synchronousUpdateEnabled = TRUE;                    /* Enable synchronous update                    */

    IfxGtm_Tom_Pwm_init(&g_tomDriver1, &g_tomConfig1);               /* Initialize the GTM TOM                       */
    IfxGtm_Tom_Pwm_start(&g_tomDriver1, TRUE);                       /* Start the PWM                                */

    IfxGtm_Tom_Pwm_init(&g_tomDriver2, &g_tomConfig2);               /* Initialize the GTM TOM                       */
    IfxGtm_Tom_Pwm_start(&g_tomDriver2, TRUE);                       /* Start the PWM                                */
}

/* This function sets the duty cycle of the PWM EN1 */
void setDutyCycleEn1(uint32 dutyCycle)
{
    g_tomConfig1.dutyCycle = (PWM_PERIOD/100)* dutyCycle;             /* Change the value of the duty cycle           */
    IfxGtm_Tom_Pwm_init(&g_tomDriver1, &g_tomConfig1);                /* Re-initialize the PWM                        */
}

/* This function sets the duty cycle of the PWM EN2 */
void setDutyCycleEn2(uint32 dutyCycle)
{
    g_tomConfig2.dutyCycle = (PWM_PERIOD/100)* dutyCycle;             /* Change the value of the duty cycle           */
    IfxGtm_Tom_Pwm_init(&g_tomDriver2, &g_tomConfig2);                /* Re-initialize the PWM                        */
}





