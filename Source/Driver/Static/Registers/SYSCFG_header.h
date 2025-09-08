#ifndef INC_SYSCFG_HEADER_H_
#define INC_SYSCFG_HEADER_H_

#include <stdint.h>

typedef struct SYSCFG_str
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t CMPCR;
} SYSCFG_t;

SYSCFG_t *SYSCFG_reg = (SYSCFG_t*)0x40013800;

#endif

