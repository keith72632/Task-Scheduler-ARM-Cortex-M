#include <stdint.h>
#include "registers.h"
#include "main.h"

/* This variable tracks the current_task being executed on the CPU */
uint8_t current_task = 1; //task1 is running

/* This variable gets updated from systick handler for every systick interrupt */
uint32_t g_tick_count = 0;



/* Each task has its own TCB */
TCB_t user_tasks[MAX_TASKS];

//Registers
SCB_t* SCB = (SCB_t*)SCB_BASE;
