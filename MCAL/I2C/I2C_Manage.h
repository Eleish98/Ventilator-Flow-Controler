/*
 * I2C_Manage.h
 *
 *  Created on: May 10, 2020
 *      Author: Ahmed_Saad
 */

#ifndef I2C_I2C_MANAGE_H_
#define I2C_I2C_MANAGE_H_

#define I2C_0       0
#define I2C_1       1
#define I2C_2       2
#define I2C_3       3

void InitI2C(void);
uint32_t I2CReceiveOneByte(uint8_t I2C_ID, uint32_t slave_addr, uint8_t reg);
uint32_t I2CReceiveBytes(uint8_t I2C_ID, uint32_t slave_addr,uint8_t u8Command, uint8_t u8BytesNumber,uint8_t * RxBuffer);
uint32_t I2CSendString(uint8_t I2C_ID, uint8_t slave_addr, uint8_t array[]);
uint32_t I2CReadBytes(uint8_t I2C_ID, uint32_t slave_addr,uint8_t * u8Command, uint8_t u8BytesNumber,uint8_t * RxBuffer);

/*
void InitI2C1(void);
uint32_t I2C1ReadBytes(uint32_t slave_addr,uint8_t  u8Command, uint8_t u8BytesNumber,uint8_t * RxBuffer);
*/

#endif /* I2C_I2C_MANAGE_H_ */
