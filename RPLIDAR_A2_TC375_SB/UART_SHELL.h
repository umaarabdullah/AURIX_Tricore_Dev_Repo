/*
 * UART.h
 *
 *  Created on: May 10, 2023
 *      Author: Umaar
 */

#ifndef UART_SHELL_H_
#define UART_SHELL_H_

#include "IfxStdIf_DPipe.h"


/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define ENDLINE     "\n\r"

/*------------------------------------------------------Extern Global Variable-------------------------------------------------------*/
extern IfxStdIf_DPipe  g_ascStandardInterface;                                     /* Standard interface object (io object) Had to make it extern so that I can call Dpipe from other functions*/

/*********************************************************************************************************************/
/**
 * @brief   Print formatted data to the console using the IfxStdIf_DPipe_print function.
 *
 * To use IfxStdIf_DPipe_print, follow these steps:
 * 1) Include the UART.h header in your source file.
 * 2) Provide the global standard interface object as the first argument and the text to be displayed on the console
 *    as the second argument, along with optional format specifiers for additional variables.
 *
 * Example usage:
 * IfxStdIf_DPipe_print(&g_ascStandardInterface, "Format %d %d", var1, var2);
 */
/*********************************************************************************************************************/


/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void initShellInterface(void);
void runShellInterface(void);
void print(const char *, ...);  /* Print a formatted message to the console using variable arguments. */
void println(const char *, ...);


#endif /* UART_SHELL_H_ */
