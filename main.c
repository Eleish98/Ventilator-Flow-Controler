
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sysctl.h>
#include"Timer/Timer_Manage.h"
#include"APP/schedule/Schedule.h"
#include "FreeRTOS.h"
#include "OS/FreeRTOS/Source/include/task.h"

#include "HAL/Flow_Sensor/Flow_Sensor.h"
#include "HAL/Pressure_Sensor/Pressure_Sensor.h"
#include "MCAL/UART/UART_Manager.h"
#include "HAL/PropValve/Prop_Valve.h"
/**
 * main.c
 */

volatile int16_t Inspiration_Flow;
volatile int16_t Expiration_Flow;

volatile uint32_t Inspiration_Pressure;
volatile uint32_t Expiration_Pressure;

 char S[100];

static void StringUARTSend(char* String){
    while(*String)
        UART_vidSend((unsigned char)(*String++));
}

int main(void)
{
    (void)bDriverInit();

    //StringUARTSend("UART Initiated\n");
    int i = 0;
    while(1){
        /*
        Inspiration_Flow = s16ReadFlow(FLOW_SENSOR_INSPIRATION);
        Expiration_Flow = s16ReadFlow(FLOW_SENSOR_EXPIRATION);

        Inspiration_Pressure = u32ReadPressure(PRESSURE_SENSOR_INSPIRATION);
        Expiration_Pressure - u32ReadPressure(PRESSURE_SENSOR_EXPIRATION);

        sprintf(S,"Flow Readings:\n\tInspiration:\t%d\n\tExpiration:\t%d\n",Inspiration_Flow,Expiration_Flow);
        StringUARTSend(S);
        sprintf(S,"Pressure Readings:\n\tInspiration:\t%lu\n\tExpiration:\t%lu\n",Inspiration_Pressure,Expiration_Pressure);
        StringUARTSend(S);
        //Delay for one second
         */
        SetValveVoltage(i);
        //SysCtlDelay(50000000);
    }
}
