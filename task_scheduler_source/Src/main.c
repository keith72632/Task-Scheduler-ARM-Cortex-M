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
#include "kernel.h"
#include"main.h"
#include "led.h"
#include "psp.h"
#include "faults.h"
#include "registers.h"
#include "tasks.h"
#include "uart_drivers.h"
#include "spi_drivers.h"
#include "timers.h"
#include "stm32f407xx.h"
#include "gpio_drivers.h"

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

uint32_t timer = 0;



int main(void)
{
	led_init_all();

	USART_Init(USART2);

	SPI_Init(SPI1);

//	TIM_6_Init();

	gpio_test_init();

	OS_KernelInit();

	for(;;);
}

void TIM6_DAC_IRQHandler()
{
	uint8_t tim[] = "timer\n";

	timer++;
	if(timer > 200000)
	{
		uputs(tim);
		timer = 0;
	}
//	while(1);
}

void SPI1_IRQHandler(void)
{
	uint8_t success[] = "success\n";
	uputs(success);
	while(1);
}


void EXTI0_IRQHandler()
{
//	uint8_t success[] = "gpio\n";
//	uputs(success);
}

