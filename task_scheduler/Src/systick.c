#include <stdint.h>
#include "main.h"
#include "stack.h"
#include "systick.h"

extern uint8_t current_task;
extern uint32_t g_tick_count;
extern TCB_t user_tasks[MAX_TASKS];

uint32_t *pICSR = (uint32_t *)0xe000ed04;

__attribute__((naked))void PendSV_Handler(void)
{
    /*Save context of current task */
    //1. Get current running task's psp value 
    __asm volatile("MRS R0,PSP");

    //2. Using that psp value store Stack Frame Two (r4 to r11)
    //**can't use pop or push in handler, these affect MSP. Use store instruction.
    //**Store Multiple Decrement Before. !=final addr is written to Rn!
    __asm volatile("STMDB R0!,{R4-R11}");
    
    //Need to save LR
    __asm volatile("PUSH {LR}");

    //3. Save the current value of psp
    __asm volatile("BL save_psp_value");


    /* Retrieve Context of next task */
    
    //1. Decide Next Task
    __asm volatile("BL update_next_task");
    //2. Get it's last psp value
    __asm volatile("BL get_psp_value");
    //3. Using that psp value retrieve Stack Frame 2
    // psp value is returned as r0 from function above
    // now load from memory to register. LDMIA, or LDM is default
    __asm volatile("LDMIA R0!,{R4-R11}");
    //4. Update psp and exit. Points to next updated task
    __asm("MSR PSP,R0");

    //Restore LR
    __asm volatile("POP {LR}");

    //since function is naked, need to manually exit
    __asm volatile("BX LR");

}

void update_global_tick_count(void)
{
    g_tick_count++;
}

void unblock_tasks(void)
{
    //user_tasks index 1 is task one. Index 0 is just idle task
    for(int i = 1; i < MAX_TASKS; i++)
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

void SysTick_Handler(void)
{
    update_global_tick_count();
    //Checks we there are any blocked tasks that qualify for running state.
    unblock_tasks();
    //pend the pendsv exception in ICSR PENDSVSET

    *pICSR |= (1 << 28); //PENDSVSET register
}

void init_systick_timer(uint32_t tick_hz)
{
    //Systick reload value register
    uint32_t *pSRVR = (uint32_t *)0xE000E014;
    uint32_t *pSCVR = (uint32_t *)0xE000E010;
    uint32_t count_value = (SYSTICK_TIM_CLK/tick_hz) -1;

    //clear value of SVR
    *pSRVR &= ~(0xffffffff);

    //load value into SVR
    *pSRVR |= count_value;

    //do some setting in SYST_CVR 
    *pSCVR |= (1 << 1) | (1 << 2); //enables systick exception request and indicates clock source, respectivley.

    //enables systick
    *pSCVR |= (1 << 0); //enable systick
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

void schedule(void)
{
    *pICSR |= (1 << 28); //Set the pend bit 
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

/*****************************************************************************************************************/

