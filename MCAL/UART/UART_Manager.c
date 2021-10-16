/*
 * UART_Manager.c
 *
 *  Created on: May 30, 2020
 *      Author: Ahmed_Saad
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "sysctl.h"
#include "pin_map.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"



#define BAUD_RATE 9600





void ISR_UART1IntHandler(void)
{
    unsigned long ulStatus;
    volatile uint8_t u8Data = 0;
    // Get the interrrupt status.
    ulStatus = UARTIntStatus(UART1_BASE, true);

    // Clear the asserted interrupts.
    UARTIntClear(UART1_BASE, ulStatus);

    u8Data = UARTCharGetNonBlocking(UART1_BASE);
//    // Loop while there are characters in the receive FIFO.
//    while(UARTCharsAvail(UART1_BASE))
//    {
//        // Read the next character from the UART and write it back to the UART.
//        UARTCharPutNonBlocking(UART1_BASE,
//                                   UARTCharGetNonBlocking(UART1_BASE));
//
//    }
}




void UART_vidInit(void)
{
  //uint8_t data=0;

    //enable peripheral clock for UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    //
    // Wait for the UART0 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART1))
    {
    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);



    UARTClockSourceSet(UART1_BASE, UART_CLOCK_SYSTEM) ; // Set System Clock for UART

    GPIOPinConfigure( GPIO_PB0_U1RX );
    GPIOPinConfigure( GPIO_PB1_U1TX );
    GPIOPinTypeUART( GPIO_PORTB_BASE , GPIO_PIN_0 | GPIO_PIN_1 );

    //disable UART0
    UARTDisable(UART1_BASE);

    // Initialize the UART. Set the baud rate, number of data bits, turn off
    // parity, number of stop bits, and stick mod. The UART is enabled by the
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), BAUD_RATE,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));

    /*enable FIFO is enabled automatically when UARTEnable() is called*/


    UARTFIFODisable(UART1_BASE);
    UARTFlowControlSet(UART1_BASE, UART_FLOWCONTROL_NONE) ; // Set UART flow control - NONE


  //  UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX4_8, UART_FIFO_RX4_8); // FIFO 8 chars
    //UARTFIFOEnable(UART1_BASE);


#ifdef UART_INTERRUPT
    UARTTxIntModeSet(UART1_BASE, UART_TXINT_MODE_EOT);
    //enable UART1 interrupt
     UARTIntRegister(UART1_BASE, ISR_UART1IntHandler);
    //enable individual UART interrupt source
    UARTIntEnable(UART1_BASE, UART_INT_TX | UART_INT_RX | UART_INT_RT); // or whatever you need
    IntEnable(INT_UART1);
    //enable processor interrupt
    IntMasterEnable();
#endif
    //enable UART1
    UARTEnable(UART1_BASE);



   // UARTCharPut(UART1_BASE,data) ;
}


uint32_t UART_vidReceive(uint8_t u8Wait)
{
    uint32_t RecData = 0;

    if(u8Wait == 1)
    {
        // Check for characters. Spin here until a character is placed into the receive FIFO.
        while(!UARTCharsAvail(UART1_BASE))
        {
        }

    }
    RecData = UARTCharGetNonBlocking(UART1_BASE);

    return RecData;
}




void UART_vidSend(unsigned char ucData)
{
    //
    // Put a character in the output buffer.
    //
    UARTCharPut(UART1_BASE, ucData);
}



#ifdef UARTNUM0
void Configure_UART(void)

{
SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0) ; // Enable UART0 peripheral
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA) ; // Enable PortA peripheral

GPIOPinConfigure(GPIO_PA0_U0RX);
GPIOPinConfigure(GPIO_PA1_U0TX);

GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1) ; // Configure Port A, Pins 0 & 1, for UART

UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM) ; // Set System Clock for UART

/*Configure UART through Clock Rate, 115.2 KBaud, 8 data_bits, No_Parity, 1 Step Bit Operation.*/

UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
UART_CONFIG_PAR_NONE)) ;

UARTFlowControlSet(UART0_BASE, UART_FLOWCONTROL_NONE) ; // Set UART flow control - NONE
UARTFIFOEnable(UART0_BASE) ; // UART FIFO enable

IntEnable(INT_UART0); // Interrupt Enable
}
#endif


//UARTParityModeSet
//UARTFIFOLevelSet
//UARTConfigSetExpClk
//UARTEnable
//UARTDisable
//UARTFIFOEnable
//UARTFIFODisable
//UARTTxIntModeSet
//UARTCharsAvail
//UARTSpaceAvail
//UARTCharGetNonBlocking
//UARTCharGet
//UARTCharPutNonBlocking
//UARTCharPut
//UARTBusy
//UARTIntRegister
//UARTIntEnable
//UARTIntStatus
//UARTIntClear
//UARTRxErrorGet
//UARTRxErrorClear
//UARTClockSourceSet
