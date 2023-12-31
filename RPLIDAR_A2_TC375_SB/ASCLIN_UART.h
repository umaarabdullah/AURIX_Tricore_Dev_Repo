/*
 * ASCLIN_UART.h
 *
 *  Created on: Sep 3, 2023
 *      Author: Umaar
 */

#ifndef ASCLIN_UART_H_
#define ASCLIN_UART_H_

#include "stdbool.h"
#include "Ifx_Types.h"

void initSerialInterface(void);
void send_receive_ASCLIN_UART_message(void);    /* Function to test the UART communication by sending a message and waiting for a response. */
size_t serialWrite(const uint8 *data);
uint8 serialRead(uint8 num_bytes_to_receive);

//bool checkRPLIDARHealth(void);

#endif /* ASCLIN_UART_H_ */
