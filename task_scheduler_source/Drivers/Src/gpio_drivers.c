/*
 * gpio_drivers.c
 *
 *  Created on: Jul 26, 2021
 *      Author: keith
 */

#include "gpio_drivers.h"
#include "uart_drivers.h"
#include "stm32f407xx.h"

//PA0, EXTI0

void gpio_priority(uint8_t interrupt_no, uint8_t priority)
{
	uint8_t pos = interrupt_no % 4;
//	usart_write(pos);
	uint8_t section = interrupt_no / 4;

	uint32_t *addr = (uint32_t*)0xe000e404;

	*addr |= (priority << 6);
}
void gpio_test_init()
{
	GPIOA_PCLK_EN();
	SYSCFG_PCLK_EN();

	GPIOA->MODER &= ~(1 << 0);

	EXTI->IMR |= (1 << 0);

	//boffem
	EXTI->RTSR |= (1 << 0);
	EXTI->FTSR |= (1 << 0);

	SYSCFG->EXTICR[0] &= ~(1 << 0);

	*NVIC_ISER0 |= (1 << IRQ_NO_EXTI0);

	gpio_priority((uint8_t)IRQ_NO_EXTI0, NVIC_IRQ_PRI15);
}
