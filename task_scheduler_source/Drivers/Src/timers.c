/*
 * timers.c
 *
 *  Created on: Jul 23, 2021
 *      Author: keith
 */
#include "stm32f407xx.h"
#include "timers.h"

__vo uint32_t *pPrescaler   = (uint32_t *)0x40001028;
__vo uint32_t *pCounter     = (uint32_t *)0x40001024;
__vo uint32_t *pInterruptEn = (uint32_t *)0x4000100C;
__vo uint32_t *pISER        = (uint32_t *)0xE000E104;
__vo uint32_t *pIPRBase = (uint32_t *)0xE000E400;


void Configure_TIM6_NVIC()
{
	uint32_t pos = TIM_6_INTERRUPT % 32;
	*pISER |= (1 << pos);

	//configure pritority
	uint32_t ipr_slot = TIM_6_INTERRUPT / 4;
	uint8_t ipr_pos = (TIM_6_INTERRUPT % 4) * 8;

	__vo uint32_t *pIPR = pIPRBase + ipr_slot;

	*pIPR &= ~(0xff << ipr_pos);
	*pIPR |= (0xf0 << ipr_pos);
}


void TIM_6_Init()
{
    TIM_6_CLK_EN();
    *pPrescaler = 0X42; //79
    *pCounter = 0xFFFF;

    TIM_6->CR1 |= (1 << 0);

    Configure_TIM6_NVIC();
    *pInterruptEn |= (1 << 0);
}
