/*
 * GTM_PWM.h
 *
 *  Created on: Apr 1, 2023
 *      Author: plabon
 */

#include "Ifx_Types.h"
#ifndef GTM_PWM_H_
#define GTM_PWM_H_


void initGtmPwm(void);
void setDutyCycleEn1(uint32 dutyCycle);
void setDutyCycleEn2(uint32 dutyCycle);


#endif /* GTM_PWM_H_ */
