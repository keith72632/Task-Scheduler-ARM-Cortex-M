/*
 * stack.h
 *
 *  Created on: Jun 1, 2021
 *      Author: keith
 */

#ifndef STACK_H_
#define STACK_H_

#define TASK_READY_STATE 0x00
#define TASK_BLOCKED_STATE 0xFF

//task control block
typedef struct {
    uint32_t psp_value;
    uint32_t block_count;
    uint8_t current_state;
    void (*task_handler)(void);
}TCB_t;

__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stack_start);
void init_task_stack();
void print_stack_info();
__attribute__((naked)) void switch_sp_to_psp(void);
void save_psp_value(uint32_t current_psp_value);
uint32_t get_psp_value(void);


#endif /* STACK_H_ */
