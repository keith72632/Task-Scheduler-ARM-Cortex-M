/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
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


/* task handler function prototypes */
void task1_handler(void); //This is task1
void task2_handler(void); //this is task2
void task3_handler(void); //this is task3
void task4_handler(void); // this is task4 of the application


void init_systick_timer(uint32_t tick_hz);
__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack);
void init_tasks_stack(void);
void enable_processor_faults(void);
__attribute__((naked)) void switch_sp_to_psp(void);
uint32_t get_psp_value(void);

void task_delay(uint32_t tick_count);


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

	init_systick_timer(TICK_HZ);

	switch_sp_to_psp();

	task1_handler();

	for(;;);
}

void gen_usage_fault(void)
{
	uint32_t *pSRAM = (uint32_t *)0x20010000;
	*pSRAM = 0xffffffff;
	void(*address)(void);
	address = (void *)0x20010001;
	address();
}

void gen_mem_manage(void)
{
	uint32_t *pPtr = (uint32_t *)0x40000000;
	void(*address)(void);
	address = (void *)pPtr;
	address();
}



void idle_task(void)
{
	while(1);
}


void task1_handler(void)
{
	while(1)
	{
		led_on(LED_GREEN);
		task_delay(1000);
		led_off(LED_GREEN);
		task_delay(1000);
	}

}

void task2_handler(void)
{
	while(1)
	{
		led_on(LED_ORANGE);
		task_delay(500);
		led_off(LED_ORANGE);
		task_delay(500);
	}

}

void task3_handler(void)
{
	while(1)
	{
		led_on(LED_BLUE);
		task_delay(250);
		led_off(LED_BLUE);
		task_delay(250);
	}

}

void task4_handler(void)

{
	while(1)
	{
		led_on(LED_RED);
		task_delay(125);
		led_off(LED_RED);
		task_delay(125);
	}


}

