/*
 * SystemTimer.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Umaar
 */


#ifndef SYSTEMTIMER_H_
#define SYSTEMTIMER_H_

/*-----------------------------------------------------Includes------------------------------------------------------*/
#include "Platform_Types.h"

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void initPeripherals(void);
uint64 getTime(void);           // Get system time in microseconds


#endif /* SYSTEMTIMER_H_ */