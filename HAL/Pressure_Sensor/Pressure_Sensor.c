/*
 * Pressure_Sensor.c
 *
 *  Created on: Aug 22, 2020
 *      Author: Ahmed_Saad
 */
#define SENSOR_10KPA

#include "stdint.h"
#include "MCAL/I2C/I2C_Manage.h"

#include "Pressure_Sensor.h"

#define PRESSURE_SENSOR_ADD 0x6Du
#define PRESSURE_LOW_RANGE 0
#ifdef  SENSOR_10KPA
#define PRESSURE_HIGH_RANGE 1019   /*10 KPA * 10 * 10.1972 = CmH2O*/
#elif defined(SENSOR_4BAR)
#define PRESSURE_HIGH_RANGE 400   /*4 bar * 100 = KPA*/
#elif defined(SENSOR_5BAR)
#define PRESSURE_HIGH_RANGE 500   /*5 bar * 100 = KPA*/
#endif

#define PRESSURE_RANGE (PRESSURE_HIGH_RANGE-PRESSURE_LOW_RANGE)

static uint8_t PressureI2Cs[2] = {I2C_2,I2C_1};

uint32_t u32ReadPressure(uint8_t SensorID)
{
    uint8_t SensorI2C = PressureI2Cs[SensorID];
    uint8_t command[] = {6};
    uint32_t u32ReadValue = 0;
    uint32_t u32ConvertValue = 0;
    uint32_t u32ADC = 0;
    int32_t u32Pressure =0x7FFFFFFF;
    uint8_t ReceivedData[3] = {0,0,0};
    uint32_t u32Error = 0;

    u32Error = I2CReadBytes(SensorI2C, PRESSURE_SENSOR_ADD, command, 3, ReceivedData);

    if(u32Error == 0 )
    {
        u32ReadValue = (   ( ((uint32_t)ReceivedData[0] << 16) & 0xFF0000 )
                    | ( ((uint32_t)ReceivedData[1] << 8) & 0xFF00 )
                    | ( ((uint32_t)ReceivedData[2] << 0) & 0xFF ));


            if(u32ReadValue & 0x800000)
            {
                u32ConvertValue = u32ReadValue - 16777216;
            }
            else
            {
                u32ConvertValue = u32ReadValue;
            }

            u32ADC = (( 330 * u32ConvertValue) / 8388608);

           /*In case of SENSOR_10KPA :-
            * The pressure value will be on .1 cmh2o accuracy, So 5 mean .5 cmh2o
            * ADC * 100 and pressure range *10, Then divide by 2*100,
            * So the output with .1 accuracy*/

            /*In case of SENSOR_4BAR or SENSOR_5BAR :-
             * The pressure value will be on 1 KPA accuracy, So 1 mean 1 KPA
             * ADC * 100, Then divide by 2*100,
             * So the output with 1 accuracy*/

            u32Pressure = (((int32_t)PRESSURE_RANGE * ((int32_t)u32ADC-(int32_t)50) )
                    / ((int32_t)200)) + (int32_t)PRESSURE_LOW_RANGE;
    }
        return u32Pressure;
}






uint32_t u32ReadTemp(uint8_t SensorID)
{
    uint8_t SensorI2C = PressureI2Cs[SensorID];
    uint8_t command[] = {9};
    uint32_t u32ReadValue = 0;
    uint32_t u32Temp = 0xFFFFFFFF;
    int32_t s32ConvertValue = 0;
    uint8_t ReceivedData[3] = {0,0,0};
    uint32_t u32Error = 0;

    u32Error = I2CReadBytes(SensorI2C, PRESSURE_SENSOR_ADD, command, 3, ReceivedData);


   if(u32Error == 0)
   {
       u32ReadValue = (   ( ((uint32_t)ReceivedData[0] << 16) & 0xFF0000 )
               | ( ((uint32_t)ReceivedData[1] << 8) & 0xFF00 )
               | ( ((uint32_t)ReceivedData[2] << 0) & 0xFF ));


       if(u32ReadValue & 0x800000)
       {
           s32ConvertValue = u32ReadValue - 16777216;
       }
       else
       {
           s32ConvertValue = u32ReadValue;
       }

       u32Temp = ( 25 +  (s32ConvertValue / 65536) );

   }


    return u32Temp;
}
