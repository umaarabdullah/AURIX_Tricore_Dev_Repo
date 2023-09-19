/*
 * UART.h
 *
 *  Created on: May 10, 2023
 *      Author: Umaar
 */

#ifndef UART_H_
#define UART_H_

#include "IfxStdIf_DPipe.h"


/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define ENDLINE     "\n\r"

/*------------------------------------------------------Extern Global Variable-------------------------------------------------------*/
extern IfxStdIf_DPipe  g_ascStandardInterface;                                     /* Standard interface object (io object) Had to make it extern so that I can call Dpipe from other functions*/
/*********************************************************************************************************************/
/* Using IfxStdIf_DPipe_print is very similar to C printf
 * 1) include UART.h
 * 2) Give reference of the global standard interface object as first argument and text to show on console as second argument
 * IfxStdIf_DPipe_print(&g_ascStandardInterface, "Format %d %d", var1, var2 )*/
/*********************************************************************************************************************/


/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void initShellInterface(void);
void runShellInterface(void);


#endif /* UART_H_ */
