/*
 * UART_Manager.h
 *
 *  Created on: May 30, 2020
 *      Author: Ahmed_Saad
 */

#ifndef MCAL_UART_UART_MANAGER_H_
#define MCAL_UART_UART_MANAGER_H_


void UART_vidInit(void);

void UART_vidSend(unsigned char ucData);
uint32_t UART_vidReceive(uint8_t u8Wait);
#endif /* MCAL_UART_UART_MANAGER_H_ */
