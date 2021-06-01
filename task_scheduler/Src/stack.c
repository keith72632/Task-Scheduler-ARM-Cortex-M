/*
 * stack.c
 *
 *  Created on: Jun 1, 2021
 *      Author: keith
 */

#include <stdint.h>
#include <stdio.h>
#include "main.h"

//all addresses of stack starts. These are unsigned ints, so must be cast to pointers
uint32_t psp_of_task[MAX_TASKS] = {T1_STACK_START, T2_STACK_START, T3_STACK_START, T4_STACK_START};

//all handlers
uint32_t task_handlers[MAX_TASKS];


__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stack_start)
{
    //first argument passed to this function is r0
    //__asm volatile("MSR MSP,R0");
    __asm volatile ("MSR MSP,R0": : "r"(scheduler_stack_start) : );
    //Branch indirect back to main, which is stored in LR
    __asm volatile ("BX LR");
}

void init_task_stack(void)
{
	uint32_t *pPSP;
	//loop through pPSP and assign register value
	for(int i = 0; i < MAX_TASKS; i++)
	{
        //initialize pPSP to addr of each task. should be 0x400 or 1024 KB apart
		pPSP = (uint32_t *)psp_of_task[i];
        printf("Task%d PSP intialized address: %p\n\n", i+1, pPSP);

        //XPSR
        pPSP--;
        *pPSP = 0x01000000;

        //PC. Address of task handler
        pPSP--;
        *pPSP = task_handlers[i];
        printf("Return address of task%d handler(PC): %lx\n\n", i+1, *pPSP); 

        //LR
        pPSP--;
        *pPSP = 0xfffffffd;

        //r0 through r12
        for(int j = 0; j < 13; j++)
        {
            pPSP--;
            *pPSP = i;
        }

        //store value of psp
        psp_of_task[i] = (uint32_t)pPSP;
	}
}
