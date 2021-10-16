/*
 * Pins.c
 *
 *  Created on: May 24, 2020
 *      Author: Ahmed_Saad
 */

#include <stdbool.h>
#include <stdint.h>
#include "sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "APP/Common.h"

#define NUMBER_OF_INPUT_PINS 0
#define NUMBER_OF_OUTPUT_PINS 4


typedef struct{
    uint32_t u32Port;
    uint8_t u8Pin;
}Pins_T;

#if NUMBER_OF_INPUT_PINS!=0
Pins_T astrInputPins[NUMBER_OF_INPUT_PINS] = {{GPIO_PORTB_BASE,GPIO_PIN_0},{GPIO_PORTA_BASE,GPIO_PIN_6},
                                              {GPIO_PORTA_BASE,GPIO_PIN_7}};
#endif

Pins_T astrOutputPins[NUMBER_OF_OUTPUT_PINS] = {
#if MCU == MIX
                                                {GPIO_PORTB_BASE,GPIO_PIN_6},{GPIO_PORTB_BASE,GPIO_PIN_7},
                                                {GPIO_PORTA_BASE,GPIO_PIN_3},{GPIO_PORTA_BASE,GPIO_PIN_4}
#elif MCU==FLOW
                                                {GPIO_PORTD_BASE,GPIO_PIN_2},{GPIO_PORTD_BASE,GPIO_PIN_3},
                                                {GPIO_PORTE_BASE,GPIO_PIN_1},{GPIO_PORTE_BASE,GPIO_PIN_2}
#endif
};

void PIN_vidInit(void)
{
    uint8_t u8Index=0;

    /* Enable GPIO PortA peripheral clock */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlDelay(3);
    /* Enable GPIO PortB peripheral clock */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlDelay(3);
    /* Enable GPIO PortD peripheral clock */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlDelay(3);
    /* Enable GPIO PortE peripheral clock */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlDelay(3);

#if NUMBER_OF_INPUT_PINS!=0
    for(u8Index=0 ; u8Index<NUMBER_OF_INPUT_PINS ;u8Index++)
    {
        /*Input pins with internal pull-Down*/
        GPIOPinTypeGPIOInput(astrInputPins[u8Index].u32Port, astrInputPins[u8Index].u8Pin);
        GPIOPadConfigSet(astrInputPins[u8Index].u32Port ,astrInputPins[u8Index].u8Pin ,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPD);
    }
#endif
    for(u8Index=0 ; u8Index<NUMBER_OF_OUTPUT_PINS ;u8Index++)
    {
        /*Output Pins */
        GPIOPinTypeGPIOOutput(astrOutputPins[u8Index].u32Port, astrOutputPins[u8Index].u8Pin);
    }


}



void PIN_vidSetPin(uint32_t ui32Port, uint8_t ui8Pins,uint8_t ui8Val)
{
    GPIOPinWrite(ui32Port,ui8Pins,ui8Val);
}


//    value= GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0);
//    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, GPIO_PIN_1);

