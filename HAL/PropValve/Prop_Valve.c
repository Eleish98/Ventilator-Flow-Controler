/*
 * Prop_Valve.c
 *
 *  Created on: Dec 4, 2020
 *      Author: Ahmed_Saad
 */
#include "stdint.h"
#include "MCAL/I2C/I2C_Manage.h"

#include "Prop_Valve.h"


uint32_t SetValveVoltage(uint16_t u16Valve2Voltage)
{

    uint8_t DataArray[3]={0,0,0xFF};
    uint32_t u32Error = 0;

    DataArray[0]= (uint8_t)((uint8_t)(u16Valve2Voltage>>8)&0xF);
    DataArray[1]=(uint8_t)(u16Valve2Voltage&0xFF);

    u32Error = I2CSendString(I2C_3,(uint8_t)0x60,(uint8_t*)DataArray);

    return u32Error;
}
