/*
 * Flow_Sensor.h
 *
 *  Created on: Aug 22, 2020
 *      Author: Ahmed_Saad
 */

#ifndef HAL_FLOW_SENSOR_FLOW_SENSOR_H_
#define HAL_FLOW_SENSOR_FLOW_SENSOR_H_

#define FLOW_SENSOR_INSPIRATION     0
#define FLOW_SENSOR_EXPIRATION      1


int16_t s16ReadFlow(uint8_t SensorID);
uint32_t u32ReadSensorID(uint8_t SensorID);
void vidSensorReset(uint8_t SensorID);

#endif /* HAL_FLOW_SENSOR_FLOW_SENSOR_H_ */
