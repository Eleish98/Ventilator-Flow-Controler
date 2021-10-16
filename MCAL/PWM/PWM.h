/*
 * PWM.h
 *
 *  Created on: May 15, 2020
 *      Author: m7mod
 */

#ifndef PWM_H_
#define PWM_H_

#define PWM_CLOCK           SYSCTL_PWMDIV_1
#define PWM_PERIOD          320
enum Ports{PORTA,PORTB,PORTC,PORTD,PORTE,PORTF};


uint8_t InitPwmChannel(uint8_t ui8Port, uint8_t ui8PinNumber,uint8_t ui8Pwm );
uint8_t ChangeDutyCycle(uint8_t ui8Port, uint8_t ui8PinNumber,uint8_t ui8Pwm );

//
//M0 01234567
//M1 01234567

//GPIO_PA6_M1PWM2
//GPIO_PA7_M1PWM3
//GPIO_PB4_M0PWM2
//GPIO_PB5_M0PWM3
//GPIO_PB6_M0PWM0
//GPIO_PB7_M0PWM1
//GPIO_PC4_M0PWM6
//GPIO_PC5_M0PWM7
//GPIO_PD0_M0PWM6
//GPIO_PD0_M1PWM0
//GPIO_PD1_M0PWM7
//GPIO_PD1_M1PWM1
//GPIO_PE4_M0PWM4
//GPIO_PE4_M1PWM2
//GPIO_PE5_M0PWM5
//GPIO_PE5_M1PWM3
//GPIO_PF0_M1PWM4
//GPIO_PF1_M1PWM5
//GPIO_PF2_M1PWM6
//GPIO_PF3_M1PWM7


#endif /* PWM_H_ */
