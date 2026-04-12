#include "Timer.h"
#include "init_static.h"
#include "RCC_header.h"

TIM1_t *TIM1_reg = (TIM1_t*)0x40010000;
TIM2_t *TIM2_reg = (TIM2_t*)0x40000000;
TIM2_t *TIM3_reg = (TIM2_t*)0x40000400;
TIM2_t *TIM4_reg = (TIM2_t*)0x40000800;
TIM1_t *TIM8_reg = (TIM1_t*)0x40010400;
TIM9_t *TIM9_reg = (TIM9_t*)0x40014000;
TIM10_t *TIM10_reg = (TIM10_t*)0x40014400;
TIM10_t *TIM11_reg = (TIM10_t*)0x40014800;
TIM9_t *TIM12_reg = (TIM9_t*)0x40001800;

uint8_t TIMxFrequency[MAX_TIMER_NUMBER] = { 0 };
bool is_timerInit[MAX_TIMER_NUMBER] = { 0 };

bool Timer_init(TIMx_t TIMx_en, uint8_t frequency)
{
	bool ReturnVal = OK;

	TIMxFrequency[TIMx_en] = frequency;

	switch (TIMx_en)
	{
		case TIM1:
			SET_BIT(RCC_reg->APB2ENR, 0U);
			WRITE_REG(TIM1_reg->CR1, 3UL, 5U, 0UL);
			CLEAR_BIT(TIM1_reg->CR1, 4U);
			WRITE_REG(TIM1_reg->CR1, 3UL, 8U, 0UL);
			CLEAR_BIT(TIM1_reg->CR1, 7U);
			TIM1_reg->ARR = (uint16_t)ARR_CONST;
			TIM1_reg->PSC = (uint16_t)(APB2_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM1]) - 1);
			break;
		case TIM2:
			SET_BIT(RCC_reg->APB1ENR, 0U);
			WRITE_REG(TIM2_reg->CR1, 3UL, 5U, 0UL);
			CLEAR_BIT(TIM2_reg->CR1, 4U);
			WRITE_REG(TIM2_reg->CR1, 3UL, 8U, 0UL);
			CLEAR_BIT(TIM2_reg->CR1, 7U);
			TIM2_reg->ARR = (uint16_t)ARR_CONST;
			TIM2_reg->PSC = (uint16_t)(APB1_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM2]) - 1);
			break;
		case TIM3:
			SET_BIT(RCC_reg->APB1ENR, 1U);
			WRITE_REG(TIM3_reg->CR1, 3UL, 5U, 0UL);
			CLEAR_BIT(TIM3_reg->CR1, 4U);
			WRITE_REG(TIM3_reg->CR1, 3UL, 8U, 0UL);
			CLEAR_BIT(TIM3_reg->CR1, 7U);
			TIM3_reg->ARR = (uint16_t)ARR_CONST;
			TIM3_reg->PSC = (uint16_t)(APB1_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM3]) - 1);
			break;
		case TIM4:
			SET_BIT(RCC_reg->APB1ENR, 2U);
			WRITE_REG(TIM4_reg->CR1, 3UL, 5U, 0UL);
			CLEAR_BIT(TIM4_reg->CR1, 4U);
			WRITE_REG(TIM4_reg->CR1, 3UL, 8U, 0UL);
			CLEAR_BIT(TIM4_reg->CR1, 7U);
			TIM4_reg->ARR = (uint16_t)ARR_CONST;
			TIM4_reg->PSC = (uint16_t)(APB1_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM4]) - 1);
			break;
		case TIM8:
			SET_BIT(RCC_reg->APB2ENR, 1U);
			WRITE_REG(TIM8_reg->CR1, 3UL, 5U, 0UL);
			CLEAR_BIT(TIM8_reg->CR1, 4U);
			WRITE_REG(TIM8_reg->CR1, 3UL, 8U, 0UL);
			CLEAR_BIT(TIM8_reg->CR1, 7U);
			TIM8_reg->ARR = (uint16_t)ARR_CONST;
			TIM8_reg->PSC = (uint16_t)(APB2_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM8]) - 1);
			break;
		case TIM9:
			SET_BIT(RCC_reg->APB2ENR, 16U);
			WRITE_REG(TIM9_reg->CR1, 3UL, 8U, 0UL);
			CLEAR_BIT(TIM9_reg->CR1, 7U);
			TIM9_reg->ARR = (uint16_t)ARR_CONST;
			TIM9_reg->PSC = (uint16_t)(APB2_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM9]) - 1);
			break;
		case TIM10:
			SET_BIT(RCC_reg->APB2ENR, 17U);
			WRITE_REG(TIM10_reg->CR1, 3UL, 8U, 0UL);
			CLEAR_BIT(TIM10_reg->CR1, 7U);
			TIM10_reg->ARR = (uint16_t)ARR_CONST;
			TIM10_reg->PSC = (uint16_t)(APB2_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM10]) - 1);
			break;
		case TIM11:
			SET_BIT(RCC_reg->APB2ENR, 18U);
			WRITE_REG(TIM11_reg->CR1, 3UL, 8U, 0UL);
			CLEAR_BIT(TIM11_reg->CR1, 7U);
			TIM11_reg->ARR = (uint16_t)ARR_CONST;
			TIM11_reg->PSC = (uint16_t)(APB2_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM11]) - 1);
			break;
		case TIM12:
			SET_BIT(RCC_reg->APB1ENR, 6U);
			WRITE_REG(TIM12_reg->CR1, 3UL, 8U, 0UL);
			CLEAR_BIT(TIM12_reg->CR1, 7U);
			TIM12_reg->ARR = (uint16_t)ARR_CONST;
			TIM12_reg->PSC = (uint16_t)(APB1_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM12]) - 1);
			break;
		default:
			ReturnVal = NOT_OK;
			break;
	}

	is_timerInit[TIMx_en] = true;

	return ReturnVal;
}
