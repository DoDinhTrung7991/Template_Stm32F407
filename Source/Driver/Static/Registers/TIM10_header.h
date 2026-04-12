#ifndef INC_TIM10_HEADER_H_
#define INC_TIM10_HEADER_H_

#include <stdint.h>

typedef struct TIM10_str
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
	volatile uint32_t Reverse_4[6];
	volatile uint32_t OR;
} TIM10_t;

extern TIM10_t *TIM10_reg;
// TIM10_t *TIM10_reg = (TIM10_t*)0x40014400;

extern TIM10_t *TIM11_reg;
// TIM10_t *TIM11_reg = (TIM10_t*)0x40014800;

#endif
