/*
 * PWM.c
 *
 *  Created on: May 15, 2020
 *      Author: m7mod
 */

#include "driverlib/pin_map.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include"PWM.h"
#include"sysctl.h"

uint8_t InitPwmChannel(uint8_t ui8Port, uint8_t ui8PinNumber,uint8_t ui8Pwm )
{
    SysCtlPWMClockSet(PWM_CLOCK);
    uint8_t ui8Error=0;
    switch (ui8Port) {
    case PORTA:
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
        PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
        switch (ui8PinNumber) {
        case 6:
            GPIOPinConfigure(GPIO_PA6_M1PWM2);
            GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_6);
            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM1_BASE, PWM_GEN_1);
            // Turn on the Output pins
            PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
            break;
        case 7:
            GPIOPinConfigure(GPIO_PA7_M1PWM3);
            GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_7);
            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM1_BASE, PWM_GEN_1);
            // Turn on the Output pins
            PWMOutputState(PWM1_BASE, PWM_OUT_3_BIT, true);
            break;
        default:
            ui8Error=1;
            break;
        }
    }
    break;
    case PORTB:
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
        switch (ui8PinNumber) {
        case 4:
            GPIOPinConfigure(GPIO_PB4_M0PWM2);
            GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);

            PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM0_BASE, PWM_GEN_1);
            // Turn on the Output pins
            PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
            break;
        case 5:
            GPIOPinConfigure(GPIO_PB5_M0PWM3);
            GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5);
            PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM0_BASE, PWM_GEN_1);
            // Turn on the Output pins
            PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, true);
            break;
        case 6:
            GPIOPinConfigure(GPIO_PB6_M0PWM0);
            GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);
            PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM0_BASE, PWM_GEN_0);
            // Turn on the Output pins
            PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
            break;
        case 7:
            GPIOPinConfigure(GPIO_PB7_M0PWM1);
            GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
            PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM0_BASE, PWM_GEN_0);
            // Turn on the Output pins
            PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
            break;
        default:
            ui8Error=1;
            break;
        }
    }
    break;
    case PORTC:
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
        PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
        switch (ui8PinNumber) {
        case 4:
            GPIOPinConfigure(GPIO_PC4_M0PWM6);
            GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_4);
            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM0_BASE, PWM_GEN_3);
            // Turn on the Output pins
            PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true);
            break;
        case 5:
            GPIOPinConfigure(GPIO_PC5_M0PWM7);
            GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_5);
            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM0_BASE, PWM_GEN_3);
            // Turn on the Output pins
            PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);
            break;
        default:
            ui8Error=1;
            break;
        }
    }
    break;
    case PORTD:
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
        PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
        switch (ui8PinNumber) {
        case 0:
            GPIOPinConfigure(GPIO_PD0_M1PWM0);
            GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM1_BASE, PWM_GEN_0);
            // Turn on the Output pins
            PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
            break;
        case 1:
            GPIOPinConfigure(GPIO_PD1_M1PWM1);
            GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_1);
            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM1_BASE, PWM_GEN_0);
            // Turn on the Output pins
            PWMOutputState(PWM1_BASE, PWM_OUT_1_BIT, true);
            break;
        default:
            ui8Error=1;
            break;
        }
    }
    break;
    case PORTE:
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
        PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
        switch (ui8PinNumber) {
        case 4:
            GPIOPinConfigure(GPIO_PE4_M0PWM4);
            GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);
            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM0_BASE, PWM_GEN_2);
            // Turn on the Output pins
            PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
            break;
        case 5:
            GPIOPinConfigure(GPIO_PE5_M0PWM5);
            GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_5);


            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM0_BASE, PWM_GEN_2);
            // Turn on the Output pins
            PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, true);
            break;
        default:
            ui8Error=1;
            break;
        }
    }
    break;
    case PORTF:
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
        switch (ui8PinNumber) {
        case 0:
            GPIOPinConfigure(GPIO_PF0_M1PWM4);
            GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);
            PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM1_BASE, PWM_GEN_2);
            // Turn on the Output pins
            PWMOutputState(PWM1_BASE, PWM_OUT_4_BIT, true);
            break;
        case 1:
            GPIOPinConfigure(GPIO_PF1_M1PWM5);
            GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);
            PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM1_BASE, PWM_GEN_2);
            // Turn on the Output pins
            PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
            break;
        case 2:
            GPIOPinConfigure(GPIO_PF2_M1PWM6);
            GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);
            PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM1_BASE, PWM_GEN_3);
            // Turn on the Output pins
            PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
            break;
        case 3:
            GPIOPinConfigure(GPIO_PF3_M1PWM7);
            GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);
            PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

            //Set the Period (expressed in clock ticks)
            PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, PWM_PERIOD);
            //Set PWM duty-50% (Period /2)
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, (ui8Pwm*PWM_PERIOD)/100 );
            // Enable the PWM generator
            PWMGenEnable(PWM1_BASE, PWM_GEN_3);
            // Turn on the Output pins
            PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
            break;
        default:
            ui8Error=1;
            break;
        }
    }
    break;
    default:
        break;
    }
    return ui8Error;
}

uint8_t ChangeDutyCycle(uint8_t ui8Port, uint8_t ui8PinNumber,uint8_t ui8Pwm )
{
    uint8_t ui8Error=0;
    switch (ui8Port) {
    case PORTA:
    {
        switch (ui8PinNumber) {
        case 6:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, false);
            }else
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        case 7:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_3_BIT, false);
            }else
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_3_BIT, true);
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        default:
            ui8Error=1;
            break;
        }
    }
    break;
    case PORTB:
    {
        switch (ui8PinNumber) {
        case 4:
            if(ui8Pwm)
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, false);
            }else
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        case 5:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, false);
            }else
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, true);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        case 6:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, false);
            }else
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        case 7:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, false);
            }else
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        default:
            ui8Error=1;
            break;
        }
    }
    break;
    case PORTC:
    {
        switch (ui8PinNumber) {
        case 4:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, false);
            }else
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        case 5:
            if(ui8Pwm)
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, false);
            }else
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        default:
            ui8Error=1;
            break;
        }
    }
    break;
    case PORTD:
    {
        switch (ui8PinNumber) {
        case 0:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, false);
            }else
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        case 1:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_1_BIT, false);
            }else
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_1_BIT, true);
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        default:
            ui8Error=1;
            break;
        }
    }
    break;
    case PORTE:
    {
        switch (ui8PinNumber) {
        case 4:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, false);
            }else
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
            }
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, (ui8Pwm*PWM_PERIOD)/100 );
            break;
        case 5:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, false);
            }else
            {
                PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, true);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        default:
            ui8Error=1;
            break;
        }
    }
    break;
    case PORTF:
    {
        switch (ui8PinNumber) {
        case 0:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_4_BIT, false);
            }else
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_4_BIT, true);
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        case 1:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, false);
            }else
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        case 2:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, false);
            }else
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        case 3:
            if(ui8Pwm==0)
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, false);
            }else
            {
                PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, (ui8Pwm*PWM_PERIOD)/100 );
            }
            break;
        default:
            ui8Error=1;
            break;
        }
    }
    break;
    default:
        break;
    }
    return ui8Error;
}

