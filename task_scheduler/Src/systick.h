#include <stdint.h>

#ifndef SYSTICK_H
#define SYSTICK_H

__attribute__((naked)) void SysTick_Handler(void);
void init_systick_timer(uint32_t tick_hz);
void update_next_task(void);

#endif
