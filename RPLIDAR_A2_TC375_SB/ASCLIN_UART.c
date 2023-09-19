/*
 * ASCLIN_UART.c
 *
 *  Created on: Sep 3, 2023
 *      Author: Umaar
 */

#include "ASCLIN_UART.h"
#include "Ifx_Types.h"
#include "IfxAsclin_Asc.h"
#include "IfxPort.h"
#include "stdint.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
/* Communication parameters */
#define ISR_PRIORITY_ASCLIN_TX      8                                       /* Priority for interrupt ISR Transmit  */
#define ISR_PRIORITY_ASCLIN_RX      4                                       /* Priority for interrupt ISR Receive   */
#define ISR_PRIORITY_ASCLIN_ER      12                                      /* Priority for interrupt ISR Errors    */
#define ASC_TX_BUFFER_SIZE          256                                     /* Define the TX buffer size in byte    */
#define ASC_RX_BUFFER_SIZE          256                                     /* Define the RX buffer size in byte    */
#define ASC_BAUDRATE                115200                                  /* Define the UART baud rate            */

/* TX RX Pin Assignment */
#define UART_PIN_RX             &IfxAsclin0_RXB_P15_3_IN                 /* UART receive port pin                    */
#define UART_PIN_TX             &IfxAsclin0_TX_P15_2_OUT                 /* UART transmit port pin                   */
#define SIZE                    5                                       /* Size of the string                       */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IfxAsclin_Asc   g_asclin;                                                   /* ASCLIN module object                 */

/* The transfer buffers allocate memory for the data itself and for FIFO runtime variables.
 * 8 more bytes have to be added to ensure a proper circular buffer handling independent from
 * the address to which the buffers have been located.
 */
uint8 g_uartTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
uint8 g_uartRxBuffer[ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

/* Definition of txData and rxData */
uint8 g_txData[] = {0xA5,0x52}; // get health command
uint8 g_rxData[SIZE] = {''};

/* Size of the message */
Ifx_SizeT g_count = sizeof(g_txData);


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
IFX_INTERRUPT(asc0TxISR, 0, ISR_PRIORITY_ASCLIN_TX);
void asc0TxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_asclin);
}

IFX_INTERRUPT(asc0RxISR, 0, ISR_PRIORITY_ASCLIN_RX);
void asc0RxISR(void)
{
    IfxAsclin_Asc_isrReceive(&g_asclin);
}

IFX_INTERRUPT(asc0ErrISR, 0, ISR_PRIORITY_ASCLIN_ER);
void asc0ErrISR(void)
{
    IfxAsclin_Asc_isrError(&g_asclin);
}

/* Function to initialize ASCLIN module */
void initSerialInterface(void)
{
    IfxAsclin_Asc_Config ascConf;

    /* Set default configurations */
    IfxAsclin_Asc_initModuleConfig(&ascConf, &MODULE_ASCLIN0); /* Initialize the structure with default values      */

    /* Set the desired baud rate */
    ascConf.baudrate.baudrate = ASC_BAUDRATE;                                   /* Set the baud rate in bit/s       */
    ascConf.baudrate.oversampling = IfxAsclin_OversamplingFactor_16;            /* Set the oversampling factor      */

    /* Configure the sampling mode */
    ascConf.bitTiming.medianFilter = IfxAsclin_SamplesPerBit_three;             /* Set the number of samples per bit*/
    ascConf.bitTiming.samplePointPosition = IfxAsclin_SamplePointPosition_8;    /* Set the first sample position    */

    /* ISR priorities and interrupt target */
    ascConf.interrupt.txPriority = ISR_PRIORITY_ASCLIN_TX;  /* Set the interrupt priority for TX events             */
    ascConf.interrupt.rxPriority = ISR_PRIORITY_ASCLIN_RX;  /* Set the interrupt priority for RX events             */
    ascConf.interrupt.erPriority = ISR_PRIORITY_ASCLIN_ER;  /* Set the interrupt priority for Error events          */
    ascConf.interrupt.typeOfService = IfxSrc_Tos_cpu0;

    /* Pin configuration */
    const IfxAsclin_Asc_Pins pins = {
            .cts        = NULL_PTR,                         /* CTS pin not used                                     */
            .ctsMode    = IfxPort_InputMode_pullUp,
            .rx         = UART_PIN_RX,        /* Select the pin for RX connected to the USB port      */
            .rxMode     = IfxPort_InputMode_pullUp,         /* RX pin                                               */
            .rts        = NULL_PTR,                         /* RTS pin not used                                     */
            .rtsMode    = IfxPort_OutputMode_pushPull,
            .tx         = UART_PIN_TX,         /* Select the pin for TX connected to the USB port      */
            .txMode     = IfxPort_OutputMode_pushPull,      /* TX pin                                               */
            .pinDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConf.pins = &pins;

    /* FIFO buffers configuration */
    ascConf.txBuffer = g_uartTxBuffer;                      /* Set the transmission buffer                          */
    ascConf.txBufferSize = ASC_TX_BUFFER_SIZE;              /* Set the transmission buffer size                     */
    ascConf.rxBuffer = g_uartRxBuffer;                      /* Set the receiving buffer                             */
    ascConf.rxBufferSize = ASC_RX_BUFFER_SIZE;              /* Set the receiving buffer size                        */

    /* Init ASCLIN module */
    IfxAsclin_Asc_initModule(&g_asclin, &ascConf);          /* Initialize the module with the given configuration   */
}

/* This function sends and receives the string "Hello World!" */
void send_receive_ASCLIN_UART_message(void)
{
    IfxAsclin_Asc_write(&g_asclin, g_txData, &g_count, TIME_INFINITE);   /* Transmit data via TX */
    g_count = 7;    // receive 7 bytes of a response descriptor packet
    IfxAsclin_Asc_read(&g_asclin, g_rxData, &g_count, 10000);    /* Receive data via RX  */
    // print the received the packet
}


/* Define the RPLIDAR A2 response packet size */
#define RPLIDAR_RESPONSE_SIZE 7

/* Function to send a request to the RPLIDAR A2 and check its health */
bool checkRPLIDARHealth(void)
{
    uint8_t requestPacket[] = {0xA5, 0x52};  // Request packet

    /* Send the request packet to the RPLIDAR A2 */
    Ifx_SizeT requestSize = sizeof(requestPacket);
    Ifx_SizeT responseSize = RPLIDAR_RESPONSE_SIZE;

    // write to serial tx
    IfxAsclin_Asc_write(&g_asclin, requestPacket, &requestSize, TIME_INFINITE);

    /* Receive the response from the RPLIDAR A2 */
    IfxAsclin_Asc_read(&g_asclin, g_rxData, &responseSize, 10000);

    /* Check if the received response matches the expected size and content */
    if (responseSize == RPLIDAR_RESPONSE_SIZE &&
        g_rxData[0] == 0xA5 &&
        g_rxData[1] == 0x5A &&
        g_rxData[2] == 0x05) {
        /* The lidar health check was successful */
        return true;
    } else {
        /* Lidar health check failed */
        return false;
    }
}

