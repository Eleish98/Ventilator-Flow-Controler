/*
 * ADC_Manager.h
 *
 *  Created on: Dec 28, 2020
 *      Author: Ahmed_Saad
 */

#ifndef MCAL_ADC_ADC_MANAGER_H_
#define MCAL_ADC_ADC_MANAGER_H_

typedef enum {
    AIN0 = 0,
    AIN1 = 1,
    AIN2 = 2,
    AIN3 = 3,
    AIN4 = 4,
    AIN5 = 5,
    AIN6 = 6,
    AIN7 = 7,
    AIN8 = 8,
    AIN9 = 9,
    AIN10 = 10,
    AIN11 = 11
} ADCChannel;


typedef enum {
    ADC0 = 0,
    ADC1 = 1
} ADCModule;


void initADC(void);

uint32_t ADC_SampleChannel(uint32_t ui32Base, uint32_t ui32SequenceNum);

#endif /* MCAL_ADC_ADC_MANAGER_H_ */
