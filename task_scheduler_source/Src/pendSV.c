/*
 * pendSV.c
 *
 *  Created on: Jun 7, 2021
 *      Author: keith
 */

#include <stdint.h>
#include "main.h"

extern uint8_t current_task;
extern TCB_t user_tasks[MAX_TASKS];

void save_psp_value(uint32_t current_psp_value)
{
	user_tasks[current_task].psp_value = current_psp_value;
}


void update_next_task(void)
{
	int state = TASK_BLOCKED_STATE;

	for(int i= 0 ; i < (MAX_TASKS) ; i++)
	{
		current_task++;
	    current_task %= MAX_TASKS;
		state = user_tasks[current_task].current_state;
		if( (state == TASK_READY_STATE) && (current_task != 0) )
			break;
	}

	if(state != TASK_READY_STATE)
		current_task = 0;
}


__attribute__((naked)) void PendSV_Handler(void)
{

	/*Save the context of current task */

	//1. Get current running task's PSP value
	__asm volatile("MRS R0,PSP");
	//2. Using that PSP value store SF2( R4 to R11)
	__asm volatile("STMDB R0!,{R4-R11}");

	__asm volatile("PUSH {LR}");

	//3. Save the current value of PSP
    __asm volatile("BL save_psp_value");



	/*Retrieve the context of next task */

	//1. Decide next task to run
    __asm volatile("BL update_next_task");

	//2. get its past PSP value
	__asm volatile ("BL get_psp_value");

	//3. Using that PSP value retrieve SF2(R4 to R11)
	__asm volatile ("LDMIA R0!,{R4-R11}");

	//4. update PSP and exit
	__asm volatile("MSR PSP,R0");

	__asm volatile("POP {LR}");

	__asm volatile("BX LR");

}

