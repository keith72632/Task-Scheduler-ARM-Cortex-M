/*
 * spi_drivers.c
 *
 *  Created on: Jul 21, 2021
 *      Author: keith
 */


#include <stdint.h>
#include "stm32f407xx.h"
#include "spi_drivers.h"

static void SPI1_ClockEnable()
{
	GPIOA_PCLK_EN();
	SPI1_PCLK_EN();
}

static void SPI1_PinInit()
{
	GPIOA->MODER |= (ALT << PIN_MODE_5) | (ALT << PIN_MODE_6) | (ALT << PIN_MODE_7);
	GPIOA->AFR[0] |= (5 << 20) | (5 << 24) | (5 << 28);
}

void SPI_Init(SPI_RegDef_t *SPIx)
{
	SPI1_ClockEnable();
	SPI1_PinInit();
}
