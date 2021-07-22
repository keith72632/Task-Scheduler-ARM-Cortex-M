/*
 * faults.h
 *
 *  Created on: Jun 7, 2021
 *      Author: keith
 */

#ifndef FAULTS_H_
#define FAULTS_H_

void enable_processor_faults(void);
void gen_usage_fault(void);
void gen_mem_manage(void);

#endif /* FAULTS_H_ */
