#ifndef INC_TIM2_HEADER_H_
#define INC_TIM2_HEADER_H_

#include <stdint.h>

typedef struct TIM2_str
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t Reverse_1;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t Reverse_2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	volatile uint32_t OR;
} TIM2_t;

extern TIM2_t *TIM2_reg;
// TIM2_t *TIM2_reg = (TIM2_t*)0x40000000;

extern TIM2_t *TIM3_reg;
// TIM2_t *TIM3_reg = (TIM2_t*)0x40000400;

extern TIM2_t *TIM4_reg;
// TIM2_t *TIM4_reg = (TIM2_t*)0x40000800;

extern TIM2_t *TIM5_reg;
// TIM2_t *TIM5_reg = (TIM2_t*)0x40000C00;

#endif

