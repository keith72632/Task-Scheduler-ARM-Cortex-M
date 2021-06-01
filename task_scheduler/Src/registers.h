#include <stdint.h>

#ifndef REGISTERS_H
#define REGISTERS_H

typedef struct Registers {
   uint32_t reg0, reg1, reg2, reg3, reg12, link, progC, XPSR; 
} registers_t;

#endif
