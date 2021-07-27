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

//void config_priority(uint8_t irq_no, uint8_t pri_value)
//{
//	// find iprx. 4 interrupts per IPRx
//	uint8_t iprx = irq_no / 4;
//	uint32_t *ipr = pIPRBase + iprx;
//	// Set PRIx to priv level. 8 bits per PRIx
//	uint8_t pos = (irq_no % 4) * 8;
//	//configure priority
//	*ipr &= ~(0xff << pos);
//	*ipr|= (pri_value << pos);
//}

void gpio_priority(uint8_t interrupt_no, uint8_t priority)
{
	uint8_t irqx = interrupt_no / 4;
//	usart_write(pos);

	uint32_t *base = (uint32_t *)0xE000E400;
	uint32_t *addr = (uint32_t *)0xe000e402;

	uint8_t pos = (interrupt_no % 4) * 8;

	*addr |= (15 << 6);
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

void green_led_toggle()
{
	GPIOD_PCLK_EN();
	GPIOD->MODER |= (1 << 24);

	if(GPIOD->ODR & (1 << 12))
	{
		GPIOD->ODR &= ~(1 << 12);
	}
	else
	{
		GPIOD->ODR |= (1 << 12);
	}
}

void blue_led_toggle()
{
	GPIOD_PCLK_EN();
	GPIOD->MODER |= (1 << 30);

	if(GPIOD->ODR & (1 << 15))
	{
		GPIOD->ODR &= ~(1 << 15);
	}
	else
	{
		GPIOD->ODR |= (1 << 15);
	}
}

void clear_interrupt(uint8_t int_no)
{
	*NVIC_ICER0 |= (1 << int_no);
}

void enable_interrupt(uint8_t int_no)
{
	*NVIC_ISER0 |= (1 << int_no);
}
