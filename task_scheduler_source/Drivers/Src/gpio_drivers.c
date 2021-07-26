/*
 * gpio_drivers.c
 *
 *  Created on: Jul 26, 2021
 *      Author: keith
 */

#include "gpio_drivers.h"
#include "stm32f407xx.h"

//PA0, EXTI0
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
}
