/*
 * Timer_Manage.c
 *
 *  Created on: May 15, 2020
 *      Author: Ahmed_Saad
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "Timer_Manage.h"


#define TIMER_PRESCALER (uint32_t)8
#define TIMER_LOAD_VALUE (uint32_t)25000



static bool bTimerFlag = false;

static void Timer_vidISRHandler(void)
{
    TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    bTimerFlag = true;
}



void TimervidInit(void)
{

    //enable Timer0 module 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    //reset module
  //  SysCtlPeripheralReset(SYSCTL_PERIPH_TIMER0);

    /* Configure time in periodic */
    TimerConfigure(TIMER0_BASE,(TIMER_CFG_A_PERIODIC|TIMER_CFG_SPLIT_PAIR));

   // TimerConfigure(TIMER0_BASE,(TIMER_CFG_PERIODIC));

  //  TimerConfigure(TIMER0_BASE,(0x12|TIMER_CFG_SPLIT_PAIR));
    /* Time period 25000 tick, time = 25000 * ( 32 / 80 * 10^6 )*/
    TimerLoadSet(TIMER0_BASE,TIMER_A,TIMER_LOAD_VALUE);
    /*Set pre-scale 32*/
    TimerPrescaleSet(TIMER0_BASE,TIMER_A,TIMER_PRESCALER);

    /* Set ISR handler with function Timer_vidISRHandler */
    TimerIntRegister(TIMER0_BASE,TIMER_A,Timer_vidISRHandler);
    /* Enable interrupt in interrupt peripheral*/
    IntEnable(INT_TIMER0A);
    /*Enable interrupt in timer peripheral*/
    TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    /* Enable timer */
    TimerEnable(TIMER0_BASE,TIMER_A);
}


bool TIM_bGetTimerFlag(void)
{
    return bTimerFlag;
}

void TIM_vidClearTimerFlag(void)
{
    bTimerFlag = false;
}
