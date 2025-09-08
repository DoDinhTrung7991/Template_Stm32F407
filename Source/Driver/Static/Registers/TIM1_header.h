#ifndef INC_TIM1_HEADER_H_
#define INC_TIM1_HEADER_H_

#include <stdint.h>

typedef struct TIM1_str
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
	volatile uint32_t RCR;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t BDTR;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
} TIM1_t;

extern TIM1_t *TIM1_reg;
// TIM1_t *TIM1_reg = (TIM1_t*)0x40010000;

extern TIM1_t *TIM8_reg;
// TIM1_t *TIM8_reg = (TIM1_t*)0x40010400;

#endif
