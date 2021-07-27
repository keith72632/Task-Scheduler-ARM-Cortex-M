/*
 * gpio_drivers.h
 *
 *  Created on: Jul 26, 2021
 *      Author: keith
 */
#include <stdint.h>

#ifndef INC_GPIO_DRIVERS_H_
#define INC_GPIO_DRIVERS_H_

void gpio_test_init();

void green_led_toggle(void);
void blue_led_toggle(void);
void clear_interrupt(uint8_t int_no);
void enable_interrupt(uint8_t int_no);

#endif /* INC_GPIO_DRIVERS_H_ */
