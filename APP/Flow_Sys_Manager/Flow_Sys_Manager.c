/*
 * Sys_Manager.c
 *
 *  Created on: Jun 8, 2020
 *      Author: Ahmed_Saad
 */
#include <APP/Flow_Sys_Manager/Flow_Sys_Manager.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "HAL/Flow_Sensor/Flow_Sensor.h"
#include "HAL/Pressure_Sensor/Pressure_Sensor.h"
#include "HAL/PropValve/Prop_Valve.h"
#include "MCAL/I2C/I2C_Manage.h"

#if 0
typedef enum {
    CMV,
    SIMV,
    AC,
}Mode_Of_Operation_T;

typedef struct {
    Mode_Of_Operation_T modeOfOperation;
    uint8_t inspiration;
    uint8_t expiration;
    uint8_t ratePerMinute;
    uint8_t tidelVolume;
    uint8_t pepVolume;
    uint8_t pepPressure;
}Flow_DoctorInputs_T;


typedef enum {
    INIT,
    MandatoryInspiration,
    Expiration,
    FlowMonitor,
    SaveState,
    Spontaneous,
    AssistedControl,
}Flow_System_States_T;


static Flow_System_States_T enuFlowSysCurrentState = INIT;
static Flow_DoctorInputs_T doctorInputs;
/******************************Stubs***************************************/
bool Stub_readDoctorInputs()
{
    doctorInputs.modeOfOperation = CMV;
    /*Wait to receive inputs one by one till trigger button pressed*/

    bool ReadDoctorInputs = false;

    return ReadDoctorInputs;

}
/*************************************************************************/

void SCH_vidFlowSysManager(void)
{
   static uint32_t u32InsExptimer = 0;
   static uint32_t u32CycleTimer = 0;
   static uint32_t inspirationTicks = 0;
   static uint32_t expirationTicks = 0;
   uint32_t u32Pressure;
   static uint32_t u32CalValveOpeningValue = 0;
   static uint32_t u32AdjustedValveOpeningValue = 0;
   int16_t FlowSensorValue;
   uint32_t CalculatedVolume=0;
   bool triggerPin = false;


  switch (enuFlowSysCurrentState)
  {
  case INIT:

            triggerPin = Stub_readDoctorInputs();

            if(triggerPin == true)
            {
                 inspirationTicks = doctorInputs.inspiration * 100;
                 expirationTicks = doctorInputs.expiration * 100;

                 if((doctorInputs.modeOfOperation == CMV)||(doctorInputs.modeOfOperation == SIMV))
                 {
                     enuFlowSysCurrentState = MandatoryInspiration;

                     /*Calculate u32ValveOpeningValue*/
                     u32AdjustedValveOpeningValue = u32CalValveOpeningValue;
                     SetValveVoltage(u32CalValveOpeningValue);
                 }
                 else
                 {
                     enuFlowSysCurrentState = FlowMonitor;
                 }
            }

      break;
  case MandatoryInspiration:

      u32InsExptimer++;
      u32CycleTimer++;

      FlowSensorValue = s16ReadFlow();
      u32Pressure = u32ReadPressure();

      if((u32Pressure < 100) &&  (FlowSensorValue < doctorInputs.ratePerMinute) && (u32InsExptimer < inspirationTicks))
      {
          if(FlowSensorValue < u32CalValveOpeningValue)
          {
              u32AdjustedValveOpeningValue++;
              /*Re adjust proportional valve*/
              SetValveVoltage(u32AdjustedValveOpeningValue);
          }
          else if (FlowSensorValue > u32CalValveOpeningValue)
          {
               u32AdjustedValveOpeningValue--;
               /*Re adjust proportional valve*/
               SetValveVoltage(u32AdjustedValveOpeningValue);
          }
          else
          {
              SetValveVoltage(u32AdjustedValveOpeningValue);
          }

          /*Calculate volume*/
          if(CalculatedVolume >= doctorInputs.tidelVolume)
          {
               SetValveVoltage(0);
               ExpValve(VALVE_OPEN);
               enuFlowSysCurrentState = Expiration;

               u32InsExptimer = 0;
          }

      }
      else
      {
          SetValveVoltage(0);
          //SafetyValve(VALVE_OPEN);
          ExpValve(VALVE_OPEN);
          enuFlowSysCurrentState = SaveState;

          u32InsExptimer = 0;
      }

      break;
  case Expiration :

      u32InsExptimer++;
      u32CycleTimer++;

      FlowSensorValue = s16ReadFlow();
      u32Pressure = u32ReadPressure();

      /*CalculatedVolume*/

      if((u32Pressure > doctorInputs.pepPressure) || (CalculatedVolume  < doctorInputs.pepVolume)
              || (u32InsExptimer < inspirationTicks))
      {
          ExpValve(VALVE_CLOSE);
          enuFlowSysCurrentState = FlowMonitor;
          u32InsExptimer = 0;
      }

      break;
  case FlowMonitor :
      u32CycleTimer++;

      if(u32CycleTimer >=  (doctorInputs.ratePerMinute * 100) )
      {
          SetValveVoltage(u32AdjustedValveOpeningValue);
          enuFlowSysCurrentState = MandatoryInspiration;
          u32CycleTimer = 0;
      }

      break;
  case SaveState :

      break;
  case Spontaneous :

      break;
  case AssistedControl :

      break;
  default:
      break;

  }

}

#endif

