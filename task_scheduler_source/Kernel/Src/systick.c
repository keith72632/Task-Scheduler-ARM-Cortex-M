/*
 * systick.c
 *
 *  Created on: Jun 7, 2021
 *      Author: keith
 */


#include <stdint.h>
#include "main.h"
#include "registers.h"

extern uint8_t current_task;
extern uint32_t g_tick_count;
extern TCB_t user_tasks[MAX_TASKS];
extern SCB_t *SCB;

void update_global_tick_count(void);
void unblock_tasks(void);
void schedule(void);

void init_systick_timer(uint32_t tick_hz)
{
	uint32_t *pSRVR = (uint32_t*)0xE000E014;
	uint32_t *pSCSR = (uint32_t*)0xE000E010;

    /* calculation of reload value */
    uint32_t count_value = (SYSTICK_TIM_CLK/tick_hz)-1;

    //Clear the value of SVR
    *pSRVR &= ~(0x00FFFFFFFF);

    //load the value in to SVR
    *pSRVR |= count_value;

    //do some settings
    *pSCSR |= ( 1 << 1); //Enables SysTick exception request:
    *pSCSR |= ( 1 << 2);  //Indicates the clock source, processor clock source

    //enable the systick
    *pSCSR |= ( 1 << 0); //enables the counter

}


void  SysTick_Handler(void)
{

	//uint32_t *pICSR = (uint32_t*)0xE000ED04;

    update_global_tick_count();
	//checks if there are any blocked tasks that qualify for running state
    unblock_tasks();

    //pend the pendsv exception
    SYS->ICSR |= ( 1 << 28);
}


void update_global_tick_count(void)
{
	g_tick_count++;
}

void unblock_tasks(void)
{
	for(int i = 1 ; i < MAX_TASKS ; i++)
	{
		if(user_tasks[i].current_state != TASK_READY_STATE)
		{
			if(user_tasks[i].block_count == g_tick_count)
			{
				user_tasks[i].current_state = TASK_READY_STATE;
			}
		}

	}

}

void schedule(void)
{
	//pend the pendsv exception in the Interrupt Control and State Register
	uint32_t *pICSR = (uint32_t*)0xE000ED04;
	*pICSR |= ( 1 << 28);

}




void task_delay(uint32_t tick_count)
{
	//disable interrupt
	INTERRUPT_DISABLE();

	if(current_task)
	{
	   user_tasks[current_task].block_count = g_tick_count + tick_count;
	   user_tasks[current_task].current_state = TASK_BLOCKED_STATE;
	   schedule();
	}

	//enable interrupt
	INTERRUPT_ENABLE();
}


