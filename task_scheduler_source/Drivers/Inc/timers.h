/*
 * timers.h
 *
 *  Created on: Jul 23, 2021
 *      Author: keith
 */
#include <stdint.h>
#include "stm32f407xx.h"

#ifndef INC_TIMERS_H_
#define INC_TIMERS_H_

typedef struct{
    uint32_t CR1;
    uint32_t CR2;
    uint32_t DIER;
    uint32_t SR;
    uint32_t EGR;
    uint32_t CNT;
    uint32_t PSC;
    uint32_t ARR;
}TIM_RegDef_t;

#define TIM_6_BASE_ADDR 0x40001000
#define TIM_6           ((TIM_RegDef_t *)TIM_6_BASE_ADDR)

//TIM6 CR1 registers
#define CEN    0
#define UDIS   1
#define URS    2
#define OPM    3
#define ARPE   7

//TIM6 CR2 registers
#define MMS    4

//TIM6 DMA/Interrypt enable register(DIER)
#define UIE    0
#define UDE    8

//TIM6 Event Generation Register(EGR)
#define UG      0


//macros for clock
#define TIM_6_CLK_EN() (RCC->APB1ENR |= (1 << 4))

#endif /* INC_TIMERS_H_ */
