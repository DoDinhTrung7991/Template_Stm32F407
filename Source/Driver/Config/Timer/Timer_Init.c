#include "Timer.h"
#include "init_static.h"
#include "RCC_header.h"
#include "Interrupt.h"

TIM_t *TIM_reg[14] = 
{
	(TIM_t*)0x40010000,
	(TIM_t*)0x40000000,
	(TIM_t*)0x40000400,
	(TIM_t*)0x40000800,
	(TIM_t*)0x40000C00,
	(TIM_t*)0x40001000,
	(TIM_t*)0x40001400,
	(TIM_t*)0x40010400,
	(TIM_t*)0x40014000,
	(TIM_t*)0x40014400,
	(TIM_t*)0x40014800,
	(TIM_t*)0x40001800,
	(TIM_t*)0x40001C00,
	(TIM_t*)0x40002000
};

uint8_t TIMxFrequency[MAX_TIMER_NUMBER] = { 0 };
bool is_timerInit[MAX_TIMER_NUMBER] = { 0 };

bool Timer_init(TIMx_t TIMx_en, uint8_t frequency_u8, bool is_Interrupt_b)
{
	is_timerInit[TIMx_en] = false;
	TIMxFrequency[TIMx_en] = frequency_u8;

	// Enable Timer peripheral and interrupt line
	switch (TIMx_en)
	{
		case TIM1:
			SET_BIT(RCC_reg->APB2ENR, 0U);
			NVIC_ISER_setVal(TIM1_UP_TIM10);
			break;

		case TIM2:
			SET_BIT(RCC_reg->APB1ENR, 0U);
			NVIC_ISER_setVal(TIM2_Interrupt);
			break;

		case TIM3:
			SET_BIT(RCC_reg->APB1ENR, 1U);
			NVIC_ISER_setVal(TIM3_Interrupt);
			break;

		case TIM4:
			SET_BIT(RCC_reg->APB1ENR, 2U);
			NVIC_ISER_setVal(TIM4_Interrupt);
			break;

		case TIM5:
			SET_BIT(RCC_reg->APB1ENR, 3U);
			NVIC_ISER_setVal(TIM5_Interrupt);
			break;

		case TIM6:
			SET_BIT(RCC_reg->APB1ENR, 4U);
			NVIC_ISER_setVal(TIM6_DAC);
			break;

		case TIM7:
			SET_BIT(RCC_reg->APB1ENR, 5U);
			NVIC_ISER_setVal(TIM7_Interrupt);
			break;

		case TIM8:
			SET_BIT(RCC_reg->APB2ENR, 1U);
			NVIC_ISER_setVal(TIM8_UP_TIM13);
			break;

		case TIM9:
			SET_BIT(RCC_reg->APB2ENR, 16U);
			NVIC_ISER_setVal(TIM1_BRK_TIM9);
			break;
			
		case TIM10:
			SET_BIT(RCC_reg->APB2ENR, 17U);
			NVIC_ISER_setVal(TIM1_UP_TIM10);
			break;

		case TIM11:
			SET_BIT(RCC_reg->APB2ENR, 18U);
			NVIC_ISER_setVal(TIM1_TRG_COM_TIM11);
			break;

		case TIM12:
			SET_BIT(RCC_reg->APB1ENR, 6U);
			NVIC_ISER_setVal(TIM8_BRK_TIM12);
			break;

		case TIM13:
			SET_BIT(RCC_reg->APB1ENR, 7U);
			NVIC_ISER_setVal(TIM8_UP_TIM13);
			break;
		
		case TIM14:
			SET_BIT(RCC_reg->APB1ENR, 8U);
			NVIC_ISER_setVal(TIM8_TRG_COM_TIM14);
			break;
		
		default:
			return NOT_OK;
			break;
	}

	// Disable Counter
	CLEAR_BIT(TIM_reg[TIMx_en]->CR1, 0U);
	// Auto-reload preload enable
	SET_BIT(TIM_reg[TIMx_en]->CR1, 7U);
	// Update request source
	SET_BIT(TIM_reg[TIMx_en]->CR1, 2U);
	// Update generation
	SET_BIT(TIM_reg[TIMx_en]->EGR, 0U);

	switch (TIMx_en)
	{
		case TIM1:
		case TIM8:
		case TIM9:
		case TIM10:
		case TIM11:
			TIM_reg[TIMx_en]->ARR = (uint16_t)ARR_CONST;
			TIM_reg[TIMx_en]->PSC = (uint16_t)(APB2_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIMx_en]) - 1);
			break;

		case TIM2:
		case TIM3:
		case TIM4:
		case TIM5:
		case TIM6:
		case TIM7:
		case TIM12:
		case TIM13:
		case TIM14:
			TIM_reg[TIMx_en]->ARR = (uint16_t)ARR_CONST;
			TIM_reg[TIMx_en]->PSC = (uint16_t)(APB1_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIMx_en]) - 1);
			break;
			
		default:
			return NOT_OK;
			break;
	}

	// Clear interrupt flag
	CLEAR_BIT(TIM_reg[TIMx_en]->SR, 0U);

	if (is_Interrupt_b)
	{
		// Update interrupt enable
		SET_BIT(TIM_reg[TIMx_en]->DIER, 0U);
	}
	
	// Enable Counter
	SET_BIT(TIM_reg[TIMx_en]->CR1, 0U);
	is_timerInit[TIMx_en] = true;

	return OK;
}
