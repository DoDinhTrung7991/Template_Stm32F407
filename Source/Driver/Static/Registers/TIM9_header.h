#ifndef INC_TIM9_HEADER_H_
#define INC_TIM9_HEADER_H_

#include <stdint.h>

typedef struct TIM9_str
{
	volatile uint32_t CR1;
	volatile uint32_t Reverse_1;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t Reverse_2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t Reverse_3;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
} TIM9_t;

extern TIM9_t *TIM9_reg;
// TIM9_t *TIM9_reg = (TIM9_t*)0x40014000;

extern TIM9_t *TIM12_reg;
// TIM9_t *TIM12_reg = (TIM9_t*)0x40001800;

#endif
