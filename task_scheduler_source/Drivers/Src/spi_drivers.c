/*
 * spi_drivers.c
 *
 *  Created on: Jul 21, 2021
 *      Author: keith
 */


#include <stdint.h>
#include <string.h>
#include "stm32f407xx.h"
#include "spi_drivers.h"
#include "uart_drivers.h"

/*
***********************************************************************************
*                           Private Functions                                     *
**********************************************************************************/

static void SPI1_EnableAllClocks()
{
	GPIOA_PCLK_EN();
	GPIOB_PCLK_EN();
	SPI1_PCLK_EN();
}

static void SPI2_EnableAllClocks()
{
	GPIOB_PCLK_EN();
	SPI2_PCLK_EN();
}

static void SPI1_PinInit()
{
	//nss pin output
	GPIOB->MODER |= (OUTPUT << PIN_MODE_6);

	//sclk, miso and mosi set to alternative
	GPIOA->OSPEEDR |= (3 << PIN_MODE_5) | (3 << PIN_MODE_6) | (3 << PIN_MODE_7);
	GPIOA->MODER |= (ALT << PIN_MODE_5) | (ALT << PIN_MODE_6) | (ALT << PIN_MODE_7);
	GPIOA->AFR[0] |= (5 << 20) | (5 << 24) | (5 << 28);

}

static void SPI_Config(SPI_RegDef_t *SPIx)
{
	SPIx->CR1 |= (1 << SPI_CR1_CPHA) | (1 << SPI_CR1_MSTR) | (1 << SPI_CR1_SSI) | (1 << SPI_CR1_SSM) | (5 << SPI_CR1_BR);
	SPIx->CRCPR = 0x07;
}

static void SPI_Enable(SPI_RegDef_t *SPIx)
{
	SPIx->CR1 |= (ENABLE << SPI_CR1_SPE);
}

/**********************************************************************************************
 *                                Public Functions                                            *
 * *******************************************************************************************/

void SPI_Init(SPI_RegDef_t *SPIx)
{
	SPI1_EnableAllClocks();
	SPI1_PinInit();

	SPI_Config(SPIx);

	SPI_Enable(SPIx);

	NSS_PIN_HIGH();
}

void SPI1_Write(uint8_t *data)
{
	uint32_t len = strlen((char *)data);

	 while(len > 0)
	 {
	 	while(SPI1->SR & (DISABLE << SPI_SR_TXE)){};

	 	if(SPI1->CR1 & (1 << SPI_CR1_DFF))
	 	{
	 		SPI1->DR = *((uint16_t*)data);
	 		len--;
	 		len--;
	 		(uint16_t*)data++;
	 		while(SPI1->SR & (1 << SPI_SR_BSY)){};
	 	}
	 	else
	 	{
	 		SPI1->DR = *data;
	 		len--;
	 		data++;
	 		while(SPI1->SR & (1 << SPI_SR_BSY)){};

	 	}
	 }
}

void SPI1_Read(uint8_t *buffer, uint32_t len)
{

	 while(len > 0)
	 {
	 	while(SPI1->SR & (EMPTY << SPI_SR_RXNE)){};

	 	if(SPI1->CR1 & (1 << SPI_CR1_DFF))
	 	{
	 		*((uint16_t*)buffer) = SPI1->DR;
	 		len--;
	 		len--;
	 		(uint16_t*)buffer++;
//	 		while(SPI1->SR & (1 << SPI_SR_BSY)){};
	 	}
	 	else
	 	{
	 		*buffer = SPI1->DR;
	 		len--;
	 		buffer++;
//	 		while(SPI1->SR & (1 << SPI_SR_BSY)){};

	 	}
	 }


//	uputs(buffer);
}

void SPI1_Transmit(uint8_t *data)
{

	NSS_PIN_LOW();

	SPI1_Write(data);

	NSS_PIN_HIGH();

}

void SPI1_Receive(uint8_t *data, uint32_t len)
{

	NSS_PIN_LOW();

	SPI1_Read(data, len);

	NSS_PIN_HIGH();

}
