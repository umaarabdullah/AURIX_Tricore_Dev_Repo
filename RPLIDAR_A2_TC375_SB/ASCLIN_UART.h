/*
 * ASCLIN_UART.h
 *
 *  Created on: Sep 3, 2023
 *      Author: Umaar
 */

#ifndef ASCLIN_UART_H_
#define ASCLIN_UART_H_

#include "stdbool.h"

void initSerialInterface(void);
void send_receive_ASCLIN_UART_message(void);    /* Function to test the UART communication by sending a message and waiting for a response. */
//bool checkRPLIDARHealth(void);  /* Function to send a request to the RPLIDAR A2 and check its health */


#endif /* ASCLIN_UART_H_ */
