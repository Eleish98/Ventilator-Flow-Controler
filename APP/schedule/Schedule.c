/*
 * Schedule.c
 *
 *  Created on: Jun 3, 2020
 *      Author: Ahmed_Saad
 */
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "OS/priorities.h"
#include "OS/FreeRTOS/Source/include/task.h"
#include "sysctl.h"
#include "MCAL/Pins/Pins.h"
#include "MCAL/I2C/I2C_Manage.h"
#include "MCAL/Timer/Timer_Manage.h"
#include "MCAL/ADC/ADC_Manager.h"
#include "MCAL/UART/UART_Manager.h"

#include "Schedule.h"

#define SCHEDULETASKSTACKSIZE        128         // Stack size in words


//*****************************************************************************
// This hook is called by FreeRTOS when an stack overflow error is detected.
//*****************************************************************************
void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}
//*****************************************************************************
// This task run or schedule
//*****************************************************************************
static void ScheduleTask(void *pvParameters)
{
    portTickType ui16LastTime;
    uint32_t ui32ScheduleDelay = 10;

    /* Get the current tick count */
    ui16LastTime = xTaskGetTickCount();


    /* Loop forever */
    while(1)
    {

        //SCH_vidSysManager();

        /* Wait for the required amount of time to check back */
        vTaskDelayUntil(&ui16LastTime, ui32ScheduleDelay / portTICK_RATE_MS);
    }
}


//*****************************************************************************
// Initializes the Schedule task.
//*****************************************************************************
uint32_t ScheduleTaskInit(void)
{
    //
    // Create the switch task.
    //
    if(xTaskCreate(ScheduleTask, (const portCHAR *)"Schedule",
                   SCHEDULETASKSTACKSIZE, NULL, tskIDLE_PRIORITY +
                   PRIORITY_SCHEDULE_TASK, NULL) != pdTRUE)
    {
        return(1);
    }

    //
    // Success.
    //
    return(0);
}


//*****************************************************************************
// Initializes Drivers.
//*****************************************************************************
bool bDriverInit(void)
{
    /* Set the clocking to run at 50 MHz from the PLL */
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);

    TimervidInit();
    PIN_vidInit();
    InitI2C();
    UART_vidInit();
    //InitI2C1();
    //initADC();

    return 1;
}
