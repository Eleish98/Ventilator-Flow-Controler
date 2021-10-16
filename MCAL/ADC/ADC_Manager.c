/*
 * ADC_Manager.c
 *
 *  Created on: Dec 28, 2020
 *      Author: Ahmed_Saad
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "APP/Common.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include "inc/tm4c123gh6pm.h"
#include "ADC_Manager.h"



void initADC(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN| SYSCTL_XTAL_16MHZ);                                                                            //Set clock at 40 Mhz , Sometimes                                                                          //ADC may not work at 80Mhz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
    {
    }

    ADCReferenceSet(ADC0_BASE, ADC_REF_INT); //Set reference to the internal reference
                                            // You can set it to 1V or 3 V
    //ADCReferenceSet(ADC1_BASE, ADC_REF_INT); //Set reference to the internal reference
                                             // You can set it to 1V or 3 V
#if MCU==FLOW
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_0); //Configure GPIO as ADC
#elif MCU==MIX
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_1); //Configure GPIO as ADC => A2  => Air Pressure Sensor
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2); //Configure GPIO as ADC => A1  => Oxygen Pressure Sensor
    GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_5); //Configure GPIO as ADC => A11 =>  Oxygen Sensor
#endif

    /*Un comment to increase accuracy*/
    ADCHardwareOversampleConfigure(ADC0_BASE, 64);

    /*  1st Sequencer for channel A1 => Oxygen Pressure Sensor  */
    ADCSequenceDisable(ADC0_BASE, 1); //It is always a good practice to disable ADC prior                                                        //to usage ,else the ADC may not be accurate                                                               //   due to previous initializations
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0); //Use the 3rd Sample sequencer

    ADCSequenceStepConfigure(ADC0_BASE, 1, 0,ADC_CTL_CH1 | ADC_CTL_IE|ADC_CTL_END);
                                                             //Configure ADC to read from channel 8 //

    ADCSequenceEnable(ADC0_BASE, 1);   //Enable the ADC
    ADCIntClear(ADC0_BASE, 1);     //Clear interrupt to proceed to  data capture


    /*  2nd Sequencer for Channel A2    =>  Air Pressure Sensor */
    ADCSequenceDisable(ADC0_BASE, 2); //It is always a good practice to disable ADC prior                                                        //to usage ,else the ADC may not be accurate                                                               //   due to previous initializations
    ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 0); //Use the 3rd Sample sequencer

    ADCSequenceStepConfigure(ADC0_BASE, 2, 0,ADC_CTL_CH2 | ADC_CTL_IE|ADC_CTL_END);
                                                             //Configure ADC to read from channel 8 //

    ADCSequenceEnable(ADC0_BASE, 2);   //Enable the ADC
    ADCIntClear(ADC0_BASE, 2);     //Clear interrupt to proceed to  data capture

    /*  3rd Sequencer for Channel A11   =>  Oxygen Sensor   */
    ADCSequenceDisable(ADC0_BASE, 3); //It is always a good practice to disable ADC prior                                                        //to usage ,else the ADC may not be accurate                                                               //   due to previous initializations
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0); //Use the 3rd Sample sequencer

    ADCSequenceStepConfigure(ADC0_BASE, 3, 0,ADC_CTL_CH11 | ADC_CTL_IE|ADC_CTL_END);
                                                             //Configure ADC to read from channel 8 //

    ADCSequenceEnable(ADC0_BASE, 3);   //Enable the ADC
    ADCIntClear(ADC0_BASE, 3);     //Clear interrupt to proceed to  data capture

}



uint32_t ADC_SampleChannel(uint32_t ui32Base, uint32_t ui32SequenceNum)
{
    uint32_t u32ADCValue;
    ADCProcessorTrigger(ui32Base, ui32SequenceNum);   //Ask processor to trigger ADC
    while (!ADCIntStatus(ui32Base, ui32SequenceNum, false))
    { //Do nothing until interrupt is triggered
    }

    ADCIntClear(ui32Base, ui32SequenceNum); //Clear Interrupt to proceed to next data capture
    ADCSequenceDataGet(ui32Base, ui32SequenceNum, &u32ADCValue); //pui32ADC0Value is the value read

    return u32ADCValue;
}


#ifdef OLD_ADC
#define ADC0_REG_BASE   ((volatile uint32_t *)0x40038000)
#define ADC1_REG_BASE       ((volatile uint32_t *)0x40039000)

typedef struct {
   uint32_t  ACTSS;
   uint32_t  RIS;
   uint32_t  IM;
   uint32_t  ISC;
   uint32_t  OSTAT;
   uint32_t  EMUX;
   uint32_t  USTAT;
   uint32_t  TSSEL;
   uint32_t  SSPRI;
   uint32_t  SPC;
   uint32_t  PSSI;
   uint32_t  RESERVED;
   uint32_t  SAC;
   uint32_t  DCISC;
   uint32_t  CTL;
   uint32_t  RESERVED1;
   uint32_t  SSMUX0;
   uint32_t  SSCTL0;
   uint32_t  SSFIFO0;
   uint32_t  SSFSTAT0;
   uint32_t  SSOP0;
   uint32_t  SSDC0;
   uint32_t  RESERVED2[2];
   uint32_t  SSMUX1;
   uint32_t  SSCTL1;
   uint32_t  SSFIFO1;
   uint32_t  SSFSTAT1;
   uint32_t  SSOP1;
   uint32_t  SSDC1;
   uint32_t  RESERVED3[2];
   uint32_t  SSMUX2;
   uint32_t  SSCTL2;
   uint32_t  SSFIFO2;
   uint32_t  SSFSTAT2;
   uint32_t  SSOP2;
   uint32_t  SSDC2;
   uint32_t  RESERVED4[2];
   uint32_t  SSMUX3;
   uint32_t  SSCTL3;
   uint32_t  SSFIFO3;
   uint32_t  SSFSTAT3;
   uint32_t  SSOP3;
   uint32_t  SSDC3;
   uint32_t  RESERVED5[786];
   uint32_t  DCRIC;
   uint32_t  RESERVED6[63];
   uint32_t  DCCTL0;
   uint32_t  DCCTL1;
   uint32_t  DCCTL2;
   uint32_t  DCCTL3;
   uint32_t  DCCTL4;
   uint32_t  DCCTL5;
   uint32_t  DCCTL6;
   uint32_t  DCCTL7;
   uint32_t  RESERVED7[8];
   uint32_t  DCCMP0;
   uint32_t  DCCMP1;
   uint32_t  DCCMP2;
   uint32_t  DCCMP3;
   uint32_t  DCCMP4;
   uint32_t  DCCMP5;
   uint32_t  DCCMP6;
   uint32_t  DCCMP7;
   uint32_t  RESERVED8[88];
   uint32_t  PP;
   uint32_t  PC;
   uint32_t  CC;
} ADCRegs_t;

const volatile uint32_t * ADCBaseAddress[] = {
    ADC0_REG_BASE,
    ADC1_REG_BASE,
};

void ADC_Enable(ADCModule module, ADCChannel channel)
{
        uint8_t moduleBit = 0x1 << ((uint8_t)module);

        switch (channel) {

            case AIN0:
                // Initialize PORTE and enable PE3
                GPIO_InitPort(GPIO_PORTE_BASE);
                GPIO_EnableAltAnalog(GPIO_PORTE_BASE, 0x08);
                break;

            default:
                // TODO:  Implement for other channels as needed.
                abort();
                break;
        }

        // Enable the ADC module.
        SYSCTL_RCGCADC_R |= moduleBit;

        // Wait for the ADC peripheral to be ready...
        while (!(SYSCTL_PRADC_R & moduleBit )){}

        // Overlay the ADC register structure on top of the ADCx memory region...
        volatile ADCRegs_t* adc = (volatile ADCRegs_t*)ADCBaseAddress[module];

        // Disable SS3 during configuration
        adc->ACTSS &= ~0x08;

        // Software trigger conversion.
        adc->EMUX &= ~0xF000;

        // Select channel
        adc->SSMUX3 = channel;

        // Single-ended, one conversion, raw interrupt.
        adc->SSCTL3 |= 6;

        // Enable SS3
        adc->ACTSS |= 0x08;

}



uint32_t ADC_Sample(ADCModule module)
{
    volatile uint32_t result;
    volatile ADCRegs_t* adc = (volatile ADCRegs_t*)ADCBaseAddress[module];

    // Begin sampling on SS3.
    adc->PSSI |= 0x08;

    // Wait for SS3 raw interrupt status to complete.
    while ((adc->RIS & 0x08) == 0);

    // Read conversion result.
    result = adc->SSFIFO3;

    // Clear completion flag.
    adc->ISC |= 0x08;

    return result;
}

#endif
