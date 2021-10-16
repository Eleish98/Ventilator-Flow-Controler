/*
 * Flow_Sensor.c
 *
 *  Created on: Aug 22, 2020
 *      Author: Ahmed_Saad
 */
#include "stdint.h"
#include "MCAL/I2C/I2C_Manage.h"

#include "Flow_Sensor.h"

#define SENSOR_ADD 0x40u

#define INVALID_FRAME 0xFFFF

#define AIR_COFF 1400
#define OXYGEN_COFF 1428

#define USED_COFF AIR_COFF

static uint8_t FlowCheck_CRC8(uint8_t * u8Data,uint8_t u8ByteNum);


static uint8_t SensorsI2Cs[2] = {I2C_3,I2C_0};


static uint8_t FlowCheck_CRC8(uint8_t * u8Data,uint8_t u8ByteNum)
{
    uint8_t bit,byte,crc =0;
    uint8_t bRetValue = 0;

    for(byte = 0; byte < u8ByteNum; byte++)
    {
       crc ^= u8Data[byte];

       for(bit=8; bit>0; bit--)
       {
          if(crc & 0x80)
          {
              crc = (crc<<1) ^ 0x131;
          }
          else
          {
              crc = (crc<<1);
          }
       }
    }


    if(crc == u8Data[byte])
    {
        bRetValue = 1;
    }
    else
    {
        bRetValue = 0;
    }

    return bRetValue;
}




int16_t s16ReadFlow(uint8_t SensorID)
{
    uint8_t SensorI2C = SensorsI2Cs[SensorID];
    uint8_t command[2] = {0x00,0x10};
    uint16_t u16ReadValue = 0;
    int16_t sFlowValue = INVALID_FRAME;
    uint8_t bCRCCheck = 0;
    uint8_t ReceivedData[3] = {0,0,0};

    I2CReadBytes(SensorI2C, SENSOR_ADD, command, 3, ReceivedData);

    bCRCCheck = FlowCheck_CRC8(ReceivedData,2);

    if(bCRCCheck == 1)
    {
        u16ReadValue = ( ( ((uint16_t)ReceivedData[0] << 8) & 0xFF00 )
                       |   ( ((uint16_t)ReceivedData[1] << 0) & 0xFF ) );


          sFlowValue = (int16_t) ( (((int32_t)u16ReadValue - (int32_t)32000)* 10)
                  / (int32_t)USED_COFF);
    }


    return sFlowValue;
}


uint32_t u32ReadSensorID(uint8_t SensorID)
{
    uint8_t SensorI2C = SensorsI2Cs[SensorID];
    uint8_t command[2] = {0xAE,0x31};
    uint32_t u32SensorID = 0xFFFFFFFF;
    uint8_t bCRCCheck = 0;
    uint8_t ReceivedData[5] = {0,0,0,0,0};

    I2CReadBytes(SensorI2C, SENSOR_ADD, command, 5, ReceivedData);

    bCRCCheck = FlowCheck_CRC8(ReceivedData,4);

    if(bCRCCheck == 1)
    {
        u32SensorID = (    ( ((uint32_t)ReceivedData[0] << 24) & 0xFF000000 )
                       |   ( ((uint32_t)ReceivedData[1] << 16) & 0xFF0000 )
                       |   ( ((uint32_t)ReceivedData[2] << 8) & 0xFF00 )
                       |   ( ((uint32_t)ReceivedData[3] << 0) & 0xFF ));

    }


    return u32SensorID;
}

void vidSensorReset(uint8_t SensorID)
{
    uint8_t SensorI2C = SensorsI2Cs[SensorID];
    uint8_t command[3] = {0x20,0x00,0XFF};

    I2CSendString(SensorI2C, SENSOR_ADD, command);
}
