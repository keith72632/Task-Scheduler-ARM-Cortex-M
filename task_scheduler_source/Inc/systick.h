/*
 * systick.h
 *
 *  Created on: Jun 7, 2021
 *      Author: keith
 */
#include <stdint.h>

#ifndef SYSTICK_H_
#define SYSTICK_H_

void init_systick_timer(uint32_t tick_hz);
void task_delay(uint32_t tick_count);

#endif /* SYSTICK_H_ */
