#include "Timer.h"
#include "init_static.h"
#include "init_user.h"
#include "RCC_header.h"

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

	switch (TIMx_en)
	{
		case TIM2:
			TIMxFrequency[TIM2] = frequency;
			WRITE_REG(RCC_reg->APB1ENR, 1UL, 0U, 1UL);
			WRITE_REG(TIM2_reg->CR1, 3UL, 5U, 0UL);
			WRITE_REG(TIM2_reg->CR1, 1UL, 4U, 0UL);
			WRITE_REG(TIM2_reg->CR1, 3UL, 8U, 0UL);
			WRITE_REG(TIM2_reg->CR1, 1UL, 7U, 0UL);
			TIM2_reg->ARR = (uint16_t)ARR_CONST;
			TIM2_reg->PSC = (uint16_t)(APB1_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM2]) - 1);
			is_timerInit[TIM2] = true;
			break;
		case TIM3:
			TIMxFrequency[TIM3] = frequency;
			WRITE_REG(RCC_reg->APB1ENR, 1UL, 1U, 1UL);
			WRITE_REG(TIM3_reg->CR1, 3UL, 5U, 0UL);
			WRITE_REG(TIM3_reg->CR1, 1UL, 4U, 0UL);
			WRITE_REG(TIM3_reg->CR1, 3UL, 8U, 0UL);
			WRITE_REG(TIM3_reg->CR1, 1UL, 7U, 0UL);
			TIM3_reg->ARR = (uint16_t)ARR_CONST;
			TIM3_reg->PSC = (uint16_t)(APB1_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM3]) - 1);
			is_timerInit[TIM3] = true;
			break;
		case TIM4:
			TIMxFrequency[TIM4] = frequency;
			WRITE_REG(RCC_reg->APB1ENR, 1UL, 2U, 1UL);
			WRITE_REG(TIM4_reg->CR1, 3UL, 5U, 0UL);
			WRITE_REG(TIM4_reg->CR1, 1UL, 4U, 0UL);
			WRITE_REG(TIM4_reg->CR1, 3UL, 8U, 0UL);
			WRITE_REG(TIM4_reg->CR1, 1UL, 7U, 0UL);
			TIM4_reg->ARR = (uint16_t)ARR_CONST;
			TIM4_reg->PSC = (uint16_t)(APB1_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM4]) - 1);
			is_timerInit[TIM4] = true;
			break;
		case TIM8:
			TIMxFrequency[TIM8] = frequency;
			WRITE_REG(RCC_reg->APB2ENR, 1UL, 1U, 1UL);
			WRITE_REG(TIM8_reg->CR1, 3UL, 5U, 0UL);
			WRITE_REG(TIM8_reg->CR1, 1UL, 4U, 0UL);
			WRITE_REG(TIM8_reg->CR1, 3UL, 8U, 0UL);
			WRITE_REG(TIM8_reg->CR1, 1UL, 7U, 0UL);
			TIM8_reg->ARR = (uint16_t)ARR_CONST;
			TIM8_reg->PSC = (uint16_t)(APB2_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM8]) - 1);
			is_timerInit[TIM8] = true;
			break;
		case TIM9:
			TIMxFrequency[TIM9] = frequency;
			WRITE_REG(RCC_reg->APB2ENR, 1UL, 16U, 1UL);
			WRITE_REG(TIM9_reg->CR1, 3UL, 8U, 0UL);
			WRITE_REG(TIM9_reg->CR1, 1UL, 7U, 0UL);
			TIM9_reg->ARR = (uint16_t)ARR_CONST;
			TIM9_reg->PSC = (uint16_t)(APB2_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM9]) - 1);
			is_timerInit[TIM9] = true;
			break;
		case TIM10:
			TIMxFrequency[TIM10] = frequency;
			WRITE_REG(RCC_reg->APB2ENR, 1UL, 17U, 1UL);
			WRITE_REG(TIM10_reg->CR1, 3UL, 8U, 0UL);
			WRITE_REG(TIM10_reg->CR1, 1UL, 7U, 0UL);
			TIM10_reg->ARR = (uint16_t)ARR_CONST;
			TIM10_reg->PSC = (uint16_t)(APB2_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM10]) - 1);
			is_timerInit[TIM10] = true;
			break;
		case TIM11:
			TIMxFrequency[TIM11] = frequency;
			WRITE_REG(RCC_reg->APB2ENR, 1UL, 18U, 1UL);
			WRITE_REG(TIM11_reg->CR1, 3UL, 8U, 0UL);
			WRITE_REG(TIM11_reg->CR1, 1UL, 7U, 0UL);
			TIM11_reg->ARR = (uint16_t)ARR_CONST;
			TIM11_reg->PSC = (uint16_t)(APB2_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM11]) - 1);
			is_timerInit[TIM11] = true;
			break;
		case TIM12:
			TIMxFrequency[TIM12] = frequency;
			WRITE_REG(RCC_reg->APB1ENR, 1UL, 6U, 1UL);
			WRITE_REG(TIM12_reg->CR1, 3UL, 8U, 0UL);
			WRITE_REG(TIM12_reg->CR1, 1UL, 7U, 0UL);
			TIM12_reg->ARR = (uint16_t)ARR_CONST;
			TIM12_reg->PSC = (uint16_t)(APB1_freq / ((ARR_CONST + 1U) * TIMxFrequency[TIM12]) - 1);
			is_timerInit[TIM12] = true;
			break;
		default:
			ReturnVal = NOT_OK;
			break;
	}

	return ReturnVal;
}
