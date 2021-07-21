/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Keith Horton
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include<stdio.h>
#include <stdint.h>
#include"main.h"
#include "led.h"
#include "psp.h"
#include "faults.h"
#include "registers.h"
#include "tasks.h"
#include "uart_drivers.h"
#include "spi_drivers.h"
#include "stm32f407xx.h"

void usart_init(void);
void uart_write(uint8_t c);
void uart_write_string(char s[]);

/* This variable tracks the current_task being executed on the CPU */
extern uint8_t current_task; //task1 is running

/* This variable gets updated from systick handler for every systick interrupt */
extern uint32_t g_tick_count;



/* Each task has its own TCB */
extern TCB_t user_tasks[MAX_TASKS];

//Registers
extern SCB_t* SCB;


int main(void)
{

	enable_processor_faults();

	init_scheduler_stack(SCHED_STACK_START);

	init_tasks_stack();

	led_init_all();

	USART_Init(USART2);

	SPI_Init(SPI1);

	init_systick_timer(TICK_HZ);

	switch_sp_to_psp();

	task1_handler();

	for(;;);
}



