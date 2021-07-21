/*
 * uart_drivers.c
 *
 *  Created on: Jul 21, 2021
 *      Author: keith
 */
#include "stm32f407xx.h"
#include "uart_drivers.h"

void USART2_ClockInit()
{
	GPIOA_PCLK_EN();
	USART2_PCCK_EN();
}

void USART2_PinInit()
{
	GPIOA->MODER |= (2 << 4) | (2 << 6);
	GPIOA->AFR[0] |= (7 << 8) | (7 << 12);
}

void USART_Init(USART_RegDef_t *pUSARTx)
{
	USART2_ClockInit();

	USART2_PinInit();

	pUSARTx->BRR = BAUD_RATE_9600;

	pUSARTx->CR1 |= (1 << 2) | (1 << 3) | (1 << 13);
}

void usart_write(uint8_t c)
{
    while(!(USART2->SR & 0x0080)){};
    USART2->DR = c;
}

void uputs(uint8_t *s)
{
	if(*s)
	{
		usart_write(*s);
		uputs(s+=1);
	}

    while(!(USART2->SR & 0x0040)){};
}
