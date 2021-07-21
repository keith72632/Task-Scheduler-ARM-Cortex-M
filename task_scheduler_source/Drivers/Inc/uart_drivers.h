/*
 * uart_drivers.h
 *
 *  Created on: Jul 21, 2021
 *      Author: keith
 */

#include <stdint.h>
#include "stm32f407xx.h"

#ifndef INC_UART_DRIVERS_H_
#define INC_UART_DRIVERS_H_

#define BAUD_RATE_9600 0x0683U

void USART_Init(USART_RegDef_t *pUSARTx);
void uputs(uint8_t *s);

#endif /* INC_UART_DRIVERS_H_ */
