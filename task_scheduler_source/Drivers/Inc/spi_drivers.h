/*
 * spi_drivers.h
 *
 *  Created on: Jul 21, 2021
 *      Author: keith
 */

#include <stdint.h>
#include "stm32f407xx.h"

#ifndef INC_SPI_DRIVERS_H_
#define INC_SPI_DRIVERS_H_

#define NSS_PIN_HIGH() (GPIOB->ODR |= (1 << 6))
#define NSS_PIN_LOW()  (GPIOB->ODR &= ~(1 << 6))

void SPI_Init(SPI_RegDef_t *SPIx);
void SPI1_Transmit(uint8_t *data);

#endif /* INC_SPI_DRIVERS_H_ */
