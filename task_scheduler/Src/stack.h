/*
 * stack.h
 *
 *  Created on: Jun 1, 2021
 *      Author: keith
 */

#ifndef STACK_H_
#define STACK_H_

__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stack_start);
void init_task_stack();
void print_stack_info();
__attribute__((naked)) void switch_sp_to_psp(void);
void save_psp_value(uint32_t current_psp_value);
uint32_t get_psp_value(void);


#endif /* STACK_H_ */
