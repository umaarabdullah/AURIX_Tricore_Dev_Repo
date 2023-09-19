/*
 * UART.c
 *
 *  Created on: May 10, 2023
 *      Author: Umaar
 */

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "UART.h"
#include "Ifx_Types.h"
#include "IfxAsclin_Asc.h"
#include "Ifx_Shell.h"
#include "Ifx_Console.h"
#include "IfxPort.h"
#include "IfxPort_regdef.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
/* Communication parameters */
#define ISR_PRIORITY_ASCLIN_TX      9                                       /* Priority for interrupt ISR Transmit  */
#define ISR_PRIORITY_ASCLIN_RX      5                                       /* Priority for interrupt ISR Receive   */
#define ISR_PRIORITY_ASCLIN_ER      13                                      /* Priority for interrupt ISR Errors    */
#define ASC_TX_BUFFER_SIZE          256                                     /* Define the TX buffer size in byte    */
#define ASC_RX_BUFFER_SIZE          256                                     /* Define the RX buffer size in byte    */
#define ASC_BAUDRATE                115200                                  /* Define the UART baud rate            */

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

void initSerialInterfaceForShell(void);
void printInfo(IfxStdIf_DPipe *io);
boolean printShellInfo(pchar args, void *data, IfxStdIf_DPipe *io);
boolean toggleLEDShell(pchar args, void *data, IfxStdIf_DPipe *io, Ifx_P *port, uint8 pinIndex);

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IfxStdIf_DPipe  g_ascStandardInterface;                                     /* Declare  ASC Interface Here Once */
IfxAsclin_Asc   g_asclin_shell;                                                   /* ASCLIN module object                 */
Ifx_Shell       g_shellInterface;                                           /* Shell interface object               */

/* The transfer buffers allocate memory for the data itself and for FIFO runtime variables.
 * 8 more bytes have to be added to ensure a proper circular buffer handling independent from
 * the address to which the buffers have been located.
 */
uint8 g_uartTxBuffer_shell[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
uint8 g_uartRxBuffer_shell[ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

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
IFX_INTERRUPT(asc1TxISR, 0, ISR_PRIORITY_ASCLIN_TX);

void asc1TxISR(void)
{
    IfxStdIf_DPipe_onTransmit(&g_ascStandardInterface);
}

IFX_INTERRUPT(asc1RxISR, 0, ISR_PRIORITY_ASCLIN_RX);

void asc1RxISR(void)
{
    IfxStdIf_DPipe_onReceive(&g_ascStandardInterface);
}

IFX_INTERRUPT(asc1ErrISR, 0, ISR_PRIORITY_ASCLIN_ER);

void asc1ErrISR(void)
{
    IfxStdIf_DPipe_onError(&g_ascStandardInterface);
}

/* Function to print info in the console */
void printInfo(IfxStdIf_DPipe *io)
{
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDLINE);
    IfxStdIf_DPipe_print(io, "This is an example that shows how to use the Infineon Shell from iLLDs.       "ENDLINE);
    IfxStdIf_DPipe_print(io, "following parameters:                                                         "ENDLINE);
    IfxStdIf_DPipe_print(io, "  - '1': toggles the LED                                                      "ENDLINE);
    IfxStdIf_DPipe_print(io, "Any other parameter turns off the LED and reports a Shell command error.      "ENDLINE);
    IfxStdIf_DPipe_print(io, "Number Print "ENDLINE);
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDLINE);
}

/* Function to show information through the shell */
boolean printShellInfo(pchar args, void *data, IfxStdIf_DPipe *io)
{
    printInfo(io);
    return TRUE;
}

/* Function to toggle a LED */
boolean toggleLEDShell(pchar args, void *data, IfxStdIf_DPipe *io, Ifx_P *port, uint8 pinIndex)
{
    // Dynamically define a macro LED
    #undef LED                          // undefine the macro to remove any previous definitions
    #define LED port,pinIndex           // redefine the macro with the new value

    if(args[0] == '1')
    {
        IfxPort_setPinState(LED, IfxPort_State_toggled);
        IfxStdIf_DPipe_print(io, "Toggled LED!" ENDLINE ENDLINE);
    }
    else
    {
        IfxPort_setPinState(LED, IfxPort_State_low);
        IfxStdIf_DPipe_print(io, "Command syntax not correct.");
        return FALSE; /* Returning false triggers a Shell command error */
    }
    return TRUE;
}

/* Function to initialize ASCLIN module */
void initSerialInterfaceForShell(void)
{
    IfxAsclin_Asc_Config ascConf;

    /* Set default configurations */
    IfxAsclin_Asc_initModuleConfig(&ascConf, &MODULE_ASCLIN3); /* Initialize the structure with default values      */

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
            .rx         = &IfxAsclin3_RXD_P32_2_IN ,        /* Select the pin for RX connected to the USB port      */
            .rxMode     = IfxPort_InputMode_pullUp,         /* RX pin                                               */
            .rts        = NULL_PTR,                         /* RTS pin not used                                     */
            .rtsMode    = IfxPort_OutputMode_pushPull,
            .tx         = &IfxAsclin3_TX_P15_7_OUT,         /* Select the pin for TX connected to the USB port      */
            .txMode     = IfxPort_OutputMode_pushPull,      /* TX pin                                               */
            .pinDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConf.pins = &pins;

    /* FIFO buffers configuration */
    ascConf.txBuffer = g_uartTxBuffer_shell;                      /* Set the transmission buffer                          */
    ascConf.txBufferSize = ASC_TX_BUFFER_SIZE;              /* Set the transmission buffer size                     */
    ascConf.rxBuffer = g_uartRxBuffer_shell;                      /* Set the receiving buffer                             */
    ascConf.rxBufferSize = ASC_RX_BUFFER_SIZE;              /* Set the receiving buffer size                        */

    /* Init ASCLIN module */
    IfxAsclin_Asc_initModule(&g_asclin_shell, &ascConf);          /* Initialize the module with the given configuration   */
}

/* Function to initialize the Shell */
void initShellInterface(void)
{
    /* Initialize the hardware peripherals */
    initSerialInterfaceForShell();

    /* Initialize the Standard Interface */
    IfxAsclin_Asc_stdIfDPipeInit(&g_ascStandardInterface, &g_asclin_shell);

    /* Initialize the Console */
    Ifx_Console_init(&g_ascStandardInterface);

//    Ifx_Console_print(ENDLINE "Enter '" "' to see the available commands" ENDLINE);

    /* Initialize the shell */
    Ifx_Shell_Config shellConf;
    Ifx_Shell_initConfig(&shellConf);                       /* Initialize the structure with default values         */

    shellConf.standardIo = &g_ascStandardInterface;         /* Set a pointer to the standard interface              */

    Ifx_Shell_init(&g_shellInterface, &shellConf);          /* Initialize the Shell with the given configuration    */
}

/* Function to process the incoming received data */
/* UART RECEPTION */
void runShellInterface(void)
{
    /* Process the received data */
    Ifx_Shell_process(&g_shellInterface);
}





