/*
 * psp.c
 *
 *  Created on: Jun 7, 2021
 *      Author: keith
 */
#include <stdint.h>
#include "main.h"

extern TCB_t user_tasks[MAX_TASKS];
extern uint8_t current_task;

uint32_t get_psp_value(void)
{

	return user_tasks[current_task].psp_value;
}



__attribute__((naked)) void switch_sp_to_psp(void)
{
    //1. initialize the PSP with TASK1 stack start address

	//get the value of psp of current_task
	__asm volatile ("PUSH {LR}"); //preserve LR which connects back to main()
	__asm volatile ("BL get_psp_value"); //branch with link. This is why the lr is saved
	__asm volatile ("MSR PSP,R0"); //initialize psp. value in getpsp returned as r0.
	__asm volatile ("POP {LR}");  //pops back LR value

	//2. change SP to PSP using CONTROL register
	__asm volatile ("MOV R0,#0X02");
	__asm volatile ("MSR CONTROL,R0");
	__asm volatile ("BX LR");
}

