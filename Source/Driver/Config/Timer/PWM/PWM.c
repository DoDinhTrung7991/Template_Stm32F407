#include "GPIO.h"
#include "Timer.h"

/*Variable - Start*/

bool is_PWMinit[MAX_TIMER_NUMBER][MAX_CHANNEL_NUMBER] = { 0 };

/*Variable - End*/

bool PWM_init(TIMx_t TIMx_en, TIM_Channel_t Channel)
{
	bool ReturnVal = OK;

	switch (TIMx_en)
	{
		case TIM1:
			if (true == is_timerInit[TIM1])
			{
				SET_BIT(TIM1_reg->EGR, 0U);
				WRITE_REG(TIM1_reg->CR2, 7UL, 4U, 0UL);
				CLEAR_BIT(TIM1_reg->SMCR, 7U);
				switch (Channel)
				{
					case CHANN_1:
						CLEAR_BIT(TIM1_reg->CCER, 0U);
						WRITE_REG(TIM1_reg->CCMR1, 7UL, 4U, 6UL);
						WRITE_REG(TIM1_reg->CCMR1, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM1_reg->CCER, 1U);
						TIM1_reg->CCR1 = (unsigned short)0;
						SET_BIT(TIM1_reg->CCMR1, 3U);
						SET_BIT(TIM1_reg->CCMR1, 2U);
						GPIO_setup(GPIOAEN, 8U, AF, AF1, PP, NoP);
						SET_BIT(TIM1_reg->CCER, 0U);
						WRITE_REG(TIM1_reg->SMCR, 7UL, 0U, 0UL);
						SET_BIT(TIM1_reg->BDTR, 15U);
						is_PWMinit[TIM1][CHANN_1] = true;
						break;
					case CHANN_2:
						CLEAR_BIT(TIM1_reg->CCER, 4U);
						WRITE_REG(TIM1_reg->CCMR1, 7UL, 12U, 6UL);
						WRITE_REG(TIM1_reg->CCMR1, 3UL, 8U, 0UL);
						CLEAR_BIT(TIM1_reg->CCER, 5U);
						TIM1_reg->CCR2 = (unsigned short)0;
						SET_BIT(TIM1_reg->CCMR1, 11U);
						SET_BIT(TIM1_reg->CCMR1, 10U);
						GPIO_setup(GPIOAEN, 9U, AF, AF1, PP, NoP);
						SET_BIT(TIM1_reg->CCER, 4U);
						WRITE_REG(TIM1_reg->SMCR, 7UL, 0U, 0UL);
						SET_BIT(TIM1_reg->BDTR, 15U);
						is_PWMinit[TIM1][CHANN_2] = true;
						break;
					case CHANN_3:
						CLEAR_BIT(TIM1_reg->CCER, 8U);
						WRITE_REG(TIM1_reg->CCMR2, 7UL, 4U, 6UL);
						WRITE_REG(TIM1_reg->CCMR2, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM1_reg->CCER, 9U);
						TIM1_reg->CCR3 = (unsigned short)0;
						SET_BIT(TIM1_reg->CCMR2, 3U);
						SET_BIT(TIM1_reg->CCMR2, 2U);
						GPIO_setup(GPIOAEN, 10U, AF, AF1, PP, NoP);
						SET_BIT(TIM1_reg->CCER, 8U);
						WRITE_REG(TIM1_reg->SMCR, 7UL, 0U, 0UL);
						SET_BIT(TIM1_reg->BDTR, 15U);
						is_PWMinit[TIM1][CHANN_3] = true;
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
				SET_BIT(TIM1_reg->CR1, 0U);
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM2:
			if (true == is_timerInit[TIM2])
			{
				SET_BIT(TIM2_reg->EGR, 0U);
				WRITE_REG(TIM2_reg->CR2, 7UL, 4U, 0UL);
				CLEAR_BIT(TIM2_reg->SMCR, 7U);
				switch (Channel)
				{
					case CHANN_1:
						CLEAR_BIT(TIM2_reg->CCER, 0U);
						WRITE_REG(TIM2_reg->CCMR1, 7UL, 4U, 6UL);
						WRITE_REG(TIM2_reg->CCMR1, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM2_reg->CCER, 1U);
						TIM2_reg->CCR1 = (unsigned short)0;
						SET_BIT(TIM2_reg->CCMR1, 3U);
						SET_BIT(TIM2_reg->CCMR1, 2U);
						GPIO_setup(GPIOAEN, 0U, AF, AF1, PP, NoP);
						SET_BIT(TIM2_reg->CCER, 0U);
						WRITE_REG(TIM2_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM2][CHANN_1] = true;
						break;
					case CHANN_2:
						CLEAR_BIT(TIM2_reg->CCER, 4U);
						WRITE_REG(TIM2_reg->CCMR1, 7UL, 12U, 6UL);
						WRITE_REG(TIM2_reg->CCMR1, 3UL, 8U, 0UL);
						CLEAR_BIT(TIM2_reg->CCER, 5U);
						TIM2_reg->CCR2 = (unsigned short)0;
						SET_BIT(TIM2_reg->CCMR1, 11U);
						SET_BIT(TIM2_reg->CCMR1, 10U);
						GPIO_setup(GPIOAEN, 1U, AF, AF1, PP, NoP);
						SET_BIT(TIM2_reg->CCER, 4U);
						WRITE_REG(TIM2_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM2][CHANN_2] = true;
						break;
					case CHANN_3:
						CLEAR_BIT(TIM2_reg->CCER, 8U);
						WRITE_REG(TIM2_reg->CCMR2, 7UL, 4U, 6UL);
						WRITE_REG(TIM2_reg->CCMR2, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM2_reg->CCER, 9U);
						TIM2_reg->CCR3 = (unsigned short)0;
						SET_BIT(TIM2_reg->CCMR2, 3U);
						SET_BIT(TIM2_reg->CCMR2, 2U);
						GPIO_setup(GPIOAEN, 2U, AF, AF1, PP, NoP);
						SET_BIT(TIM2_reg->CCER, 8U);
						WRITE_REG(TIM2_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM2][CHANN_3] = true;
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
				SET_BIT(TIM2_reg->CR1, 0U);
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM3:
			if (true == is_timerInit[TIM3])
			{
				SET_BIT(TIM3_reg->EGR, 0U);
				WRITE_REG(TIM3_reg->CR2, 7UL, 4U, 0UL);
				CLEAR_BIT(TIM3_reg->SMCR, 7U);
				switch (Channel)
				{
					case CHANN_1:
						CLEAR_BIT(TIM3_reg->CCER, 0U);
						WRITE_REG(TIM3_reg->CCMR1, 7UL, 4U, 6UL);
						WRITE_REG(TIM3_reg->CCMR1, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM3_reg->CCER, 1U);
						TIM3_reg->CCR1 = (unsigned short)0;
						SET_BIT(TIM3_reg->CCMR1, 3U);
						SET_BIT(TIM3_reg->CCMR1, 2U);
						GPIO_setup(GPIOAEN, 6U, AF, AF2, PP, NoP);
						SET_BIT(TIM3_reg->CCER, 0U);
						WRITE_REG(TIM3_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM3][CHANN_1] = true;
						break;
					case CHANN_2:
						CLEAR_BIT(TIM3_reg->CCER, 4U);
						WRITE_REG(TIM3_reg->CCMR1, 7UL, 12U, 6UL);
						WRITE_REG(TIM3_reg->CCMR1, 3UL, 8U, 0UL);
						CLEAR_BIT(TIM3_reg->CCER, 5U);
						TIM3_reg->CCR2 = (unsigned short)0;
						SET_BIT(TIM3_reg->CCMR1, 11U);
						SET_BIT(TIM3_reg->CCMR1, 10U);
						GPIO_setup(GPIOAEN, 7U, AF, AF2, PP, NoP);
						SET_BIT(TIM3_reg->CCER, 4U);
						WRITE_REG(TIM3_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM3][CHANN_2] = true;
						break;
					case CHANN_3:
						CLEAR_BIT(TIM3_reg->CCER, 8U);
						WRITE_REG(TIM3_reg->CCMR2, 7UL, 4U, 6UL);
						WRITE_REG(TIM3_reg->CCMR2, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM3_reg->CCER, 9U);
						TIM3_reg->CCR3 = (unsigned short)0;
						SET_BIT(TIM3_reg->CCMR2, 3U);
						SET_BIT(TIM3_reg->CCMR2, 2U);
						GPIO_setup(GPIOBEN, 0U, AF, AF2, PP, NoP);
						SET_BIT(TIM3_reg->CCER, 8U);
						WRITE_REG(TIM3_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM3][CHANN_3] = true;
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
				SET_BIT(TIM3_reg->CR1, 0U);
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM4:
			if (true == is_timerInit[TIM4])
			{
				SET_BIT(TIM4_reg->EGR, 0U);
				WRITE_REG(TIM4_reg->CR2, 7UL, 4U, 0UL);
				CLEAR_BIT(TIM4_reg->SMCR, 7U);
				switch (Channel)
				{
					case CHANN_1:
						CLEAR_BIT(TIM4_reg->CCER, 0U);
						WRITE_REG(TIM4_reg->CCMR1, 7UL, 4U, 6UL);
						WRITE_REG(TIM4_reg->CCMR1, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM4_reg->CCER, 1U);
						TIM4_reg->CCR1 = (unsigned short)0;
						SET_BIT(TIM4_reg->CCMR1, 3U);
						SET_BIT(TIM4_reg->CCMR1, 2U);
						GPIO_setup(GPIODEN, 12U, AF, AF2, PP, NoP);
						SET_BIT(TIM4_reg->CCER, 0U);
						WRITE_REG(TIM4_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM4][CHANN_1] = true;
						break;
					case CHANN_2:
						CLEAR_BIT(TIM4_reg->CCER, 4U);
						WRITE_REG(TIM4_reg->CCMR1, 7UL, 12U, 6UL);
						WRITE_REG(TIM4_reg->CCMR1, 3UL, 8U, 0UL);
						CLEAR_BIT(TIM4_reg->CCER, 5U);
						TIM4_reg->CCR2 = (unsigned short)0;
						SET_BIT(TIM4_reg->CCMR1, 11U);
						SET_BIT(TIM4_reg->CCMR1, 10U);
						GPIO_setup(GPIODEN, 13U, AF, AF2, PP, NoP);
						SET_BIT(TIM4_reg->CCER, 4U);
						WRITE_REG(TIM4_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM4][CHANN_2] = true;
						break;
					case CHANN_3:
						CLEAR_BIT(TIM4_reg->CCER, 8U);
						WRITE_REG(TIM4_reg->CCMR2, 7UL, 4U, 6UL);
						WRITE_REG(TIM4_reg->CCMR2, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM4_reg->CCER, 9U);
						TIM4_reg->CCR3 = (unsigned short)0;
						SET_BIT(TIM4_reg->CCMR2, 3U);
						SET_BIT(TIM4_reg->CCMR2, 2U);
						GPIO_setup(GPIODEN, 14U, AF, AF2, PP, NoP);
						SET_BIT(TIM4_reg->CCER, 8U);
						WRITE_REG(TIM4_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM4][CHANN_3] = true;
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
				SET_BIT(TIM4_reg->CR1, 0U);
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM8:
			if (true == is_timerInit[TIM8])
			{
				SET_BIT(TIM8_reg->EGR, 0U);
				WRITE_REG(TIM8_reg->CR2, 7UL, 4U, 0UL);
				CLEAR_BIT(TIM8_reg->SMCR, 7U);
				switch (Channel)
				{
					case CHANN_1:
						CLEAR_BIT(TIM8_reg->CCER, 0U);
						WRITE_REG(TIM8_reg->CCMR1, 7UL, 4U, 6UL);
						WRITE_REG(TIM8_reg->CCMR1, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM8_reg->CCER, 1U);
						TIM8_reg->CCR1 = (unsigned short)0;
						SET_BIT(TIM8_reg->CCMR1, 3U);
						SET_BIT(TIM8_reg->CCMR1, 2U);
						GPIO_setup(GPIOCEN, 6U, AF, AF3, PP, NoP);
						SET_BIT(TIM8_reg->CCER, 0U);
						WRITE_REG(TIM8_reg->SMCR, 7UL, 0U, 0UL);
						SET_BIT(TIM8_reg->BDTR, 15U);
						is_PWMinit[TIM8][CHANN_1] = true;
						break;
					case CHANN_2:
						CLEAR_BIT(TIM8_reg->CCER, 4U);
						WRITE_REG(TIM8_reg->CCMR1, 7UL, 12U, 6UL);
						WRITE_REG(TIM8_reg->CCMR1, 3UL, 8U, 0UL);
						CLEAR_BIT(TIM8_reg->CCER, 5U);
						TIM8_reg->CCR2 = (unsigned short)0;
						SET_BIT(TIM8_reg->CCMR1, 11U);
						SET_BIT(TIM8_reg->CCMR1, 10U);
						GPIO_setup(GPIOCEN, 7U, AF, AF3, PP, NoP);
						SET_BIT(TIM8_reg->CCER, 4U);
						WRITE_REG(TIM8_reg->SMCR, 7UL, 0U, 0UL);
						SET_BIT(TIM8_reg->BDTR, 15U);
						is_PWMinit[TIM8][CHANN_2] = true;
						break;
					case CHANN_3:
						CLEAR_BIT(TIM8_reg->CCER, 8U);
						WRITE_REG(TIM8_reg->CCMR2, 7UL, 4U, 6UL);
						WRITE_REG(TIM8_reg->CCMR2, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM8_reg->CCER, 9U);
						TIM8_reg->CCR3 = (unsigned short)0;
						SET_BIT(TIM8_reg->CCMR2, 3U);
						SET_BIT(TIM8_reg->CCMR2, 2U);
						GPIO_setup(GPIOCEN, 8U, AF, AF3, PP, NoP);
						SET_BIT(TIM8_reg->CCER, 8U);
						WRITE_REG(TIM8_reg->SMCR, 7UL, 0U, 0UL);
						SET_BIT(TIM8_reg->BDTR, 15U);
						is_PWMinit[TIM8][CHANN_3] = true;
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
				SET_BIT(TIM8_reg->CR1, 0U);
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM9:
			if (true == is_timerInit[TIM9])
			{
				SET_BIT(TIM9_reg->EGR, 0U);
				CLEAR_BIT(TIM9_reg->SMCR, 7U);
				switch (Channel)
				{
					case CHANN_1:
						CLEAR_BIT(TIM9_reg->CCER, 0U);
						WRITE_REG(TIM9_reg->CCMR1, 7UL, 4U, 6UL);
						WRITE_REG(TIM9_reg->CCMR1, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM9_reg->CCER, 1U);
						TIM9_reg->CCR1 = (unsigned short)0;
						SET_BIT(TIM9_reg->CCMR1, 3U);
						SET_BIT(TIM9_reg->CCMR1, 2U);
						GPIO_setup(GPIOEEN, 5U, AF, AF3, PP, NoP);
						SET_BIT(TIM9_reg->CCER, 0U);
						WRITE_REG(TIM9_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM9][CHANN_1] = true;
						break;
					case CHANN_2:
						CLEAR_BIT(TIM9_reg->CCER, 4U);
						WRITE_REG(TIM9_reg->CCMR1, 7UL, 12U, 6UL);
						WRITE_REG(TIM9_reg->CCMR1, 3UL, 8U, 0UL);
						CLEAR_BIT(TIM9_reg->CCER, 5U);
						TIM9_reg->CCR2 = (unsigned short)0;
						SET_BIT(TIM9_reg->CCMR1, 11U);
						SET_BIT(TIM9_reg->CCMR1, 10U);
						GPIO_setup(GPIOEEN, 6U, AF, AF3, PP, NoP);
						SET_BIT(TIM9_reg->CCER, 4U);
						WRITE_REG(TIM9_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM9][CHANN_2] = true;
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
				SET_BIT(TIM9_reg->CR1, 0U);
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM10:
			if (true == is_timerInit[TIM10])
			{
				SET_BIT(TIM10_reg->EGR, 0U);
				CLEAR_BIT(TIM10_reg->SMCR, 7U);
				switch (Channel)
				{
					case CHANN_1:
						CLEAR_BIT(TIM10_reg->CCER, 0U);
						WRITE_REG(TIM10_reg->CCMR1, 7UL, 4U, 6UL);
						WRITE_REG(TIM10_reg->CCMR1, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM10_reg->CCER, 1U);
						TIM10_reg->CCR1 = (unsigned short)0;
						SET_BIT(TIM10_reg->CCMR1, 3U);
						SET_BIT(TIM10_reg->CCMR1, 2U);
						GPIO_setup(GPIOBEN, 8U, AF, AF3, PP, NoP);
						SET_BIT(TIM10_reg->CCER, 0U);
						WRITE_REG(TIM10_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM10][CHANN_1] = true;
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
				SET_BIT(TIM10_reg->CR1, 0U);
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM11:
			if (true == is_timerInit[TIM11])
			{
				SET_BIT(TIM11_reg->EGR, 0U);
				CLEAR_BIT(TIM11_reg->SMCR, 7U);
				switch (Channel)
				{
					case CHANN_1:
						CLEAR_BIT(TIM11_reg->CCER, 0U);
						WRITE_REG(TIM11_reg->CCMR1, 7UL, 4U, 6UL);
						WRITE_REG(TIM11_reg->CCMR1, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM11_reg->CCER, 1U);
						TIM11_reg->CCR1 = (unsigned short)0;
						SET_BIT(TIM11_reg->CCMR1, 2U);
						SET_BIT(TIM11_reg->CCMR1, 3U);
						GPIO_setup(GPIOBEN, 9U, AF, AF3, PP, NoP);
						SET_BIT(TIM11_reg->CCER, 0U);
						WRITE_REG(TIM11_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM11][CHANN_1] = true;
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
				SET_BIT(TIM11_reg->CR1, 0U);
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM12:
			if (true == is_timerInit[TIM12])
			{
				SET_BIT(TIM12_reg->EGR, 0U);
				CLEAR_BIT(TIM12_reg->SMCR, 7U);
				switch (Channel)
				{
					case CHANN_1:
						CLEAR_BIT(TIM12_reg->CCER, 0U);
						WRITE_REG(TIM12_reg->CCMR1, 7UL, 4U, 6UL);
						WRITE_REG(TIM12_reg->CCMR1, 3UL, 0U, 0UL);
						CLEAR_BIT(TIM12_reg->CCER, 1U);
						TIM12_reg->CCR1 = (unsigned short)0;
						SET_BIT(TIM12_reg->CCMR1, 3U);
						SET_BIT(TIM12_reg->CCMR1, 2U);
						GPIO_setup(GPIOBEN, 14U, AF, AF9, PP, NoP);
						SET_BIT(TIM12_reg->CCER, 0U);
						WRITE_REG(TIM12_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM12][CHANN_1] = true;
						break;
					case CHANN_2:
						CLEAR_BIT(TIM12_reg->CCER, 4U);
						WRITE_REG(TIM12_reg->CCMR1, 7UL, 12U, 6UL);
						WRITE_REG(TIM12_reg->CCMR1, 3UL, 8U, 0UL);
						CLEAR_BIT(TIM12_reg->CCER, 5U);
						TIM12_reg->CCR2 = (unsigned short)0;
						SET_BIT(TIM12_reg->CCMR1, 11U);
						SET_BIT(TIM12_reg->CCMR1, 10U);
						GPIO_setup(GPIOBEN, 15U, AF, AF9, PP, NoP);
						SET_BIT(TIM12_reg->CCER, 4U);
						WRITE_REG(TIM12_reg->SMCR, 7UL, 0U, 0UL);
						is_PWMinit[TIM12][CHANN_2] = true;
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
				SET_BIT(TIM12_reg->CR1, 0U);
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		default:
			ReturnVal = NOT_OK;
			break;
	}

	return ReturnVal;
}

bool PWM_Generation(TIMx_t TIMx_en, TIM_Channel_t Channel, uint8_t activePercent_u8_int, uint8_t activePercent_floating_point)
{
	bool ReturnVal = OK;

	uint8_t floating_point_u8 = 0;

	if (activePercent_floating_point < 10U)
	{
		if (activePercent_floating_point <= 2U)
		{
			// do nothing
		}
		else if ((activePercent_floating_point > 2U) && (activePercent_floating_point <= 7U))
		{
			floating_point_u8 = 5;
		}
		else
		{
			activePercent_u8_int ++;
		}
	}
	else if ((activePercent_floating_point >= 10U) && (activePercent_floating_point < 100U))
	{
		floating_point_u8 = activePercent_floating_point / 10U;
		if (floating_point_u8 <= 2U)
		{
			floating_point_u8 = 0;
		}
		else if (floating_point_u8 > 2U && floating_point_u8 <= 7U)
		{
			floating_point_u8 = 5;
		}
		else
		{
			activePercent_u8_int ++;
		}
	}
	else
	{
		// do nothing
	}

	switch (TIMx_en)
	{
		case TIM1:
			if (true == is_timerInit[TIM1])
			{
				switch (Channel)
				{
					case CHANN_1:
						if (true == is_PWMinit[TIM1][CHANN_1])
						{
							TIM1_reg->CCR1 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					case CHANN_2:
						if (true == is_PWMinit[TIM1][CHANN_2])
						{
							TIM1_reg->CCR2 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					case CHANN_3:
						if (true == is_PWMinit[TIM1][CHANN_3])
						{
							TIM1_reg->CCR3 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM2:
			if (true == is_timerInit[TIM2])
			{
				switch (Channel)
				{
					case CHANN_1:
						if (true == is_PWMinit[TIM2][CHANN_1])
						{
							TIM2_reg->CCR1 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					case CHANN_2:
						if (true == is_PWMinit[TIM2][CHANN_2])
						{
							TIM2_reg->CCR2 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					case CHANN_3:
						if (true == is_PWMinit[TIM2][CHANN_3])
						{
							TIM2_reg->CCR3 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM3:
			if (true == is_timerInit[TIM3])
			{
				switch (Channel)
				{
					case CHANN_1:
						if (true == is_PWMinit[TIM3][CHANN_1])
						{
							TIM3_reg->CCR1 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					case CHANN_2:
						if (true == is_PWMinit[TIM3][CHANN_2])
						{
							TIM3_reg->CCR2 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					case CHANN_3:
						if (true == is_PWMinit[TIM3][CHANN_3])
						{
							TIM3_reg->CCR3 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM4:
			if (true == is_timerInit[TIM4])
			{
				switch (Channel)
				{
					case CHANN_1:
						if (true == is_PWMinit[TIM4][CHANN_1])
						{
							TIM4_reg->CCR1 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					case CHANN_2:
						if (true == is_PWMinit[TIM4][CHANN_2])
						{
							TIM4_reg->CCR2 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					case CHANN_3:
						if (true == is_PWMinit[TIM4][CHANN_3])
						{
							TIM4_reg->CCR3 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM8:
			if (true == is_timerInit[TIM8])
			{
				switch (Channel)
				{
					case CHANN_1:
						if (true == is_PWMinit[TIM8][CHANN_1])
						{
							TIM8_reg->CCR1 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					case CHANN_2:
						if (true == is_PWMinit[TIM8][CHANN_2])
						{
							TIM8_reg->CCR2 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					case CHANN_3:
						if (true == is_PWMinit[TIM8][CHANN_3])
						{
							TIM8_reg->CCR3 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM9:
			if (true == is_timerInit[TIM9])
			{
				switch (Channel)
				{
					case CHANN_1:
						if (true == is_PWMinit[TIM9][CHANN_1])
						{
							TIM9_reg->CCR1 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					case CHANN_2:
						if (true == is_PWMinit[TIM9][CHANN_2])
						{
							TIM9_reg->CCR2 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM10:
			if (true == is_timerInit[TIM10])
			{
				switch (Channel)
				{
					case CHANN_1:
						if (true == is_PWMinit[TIM10][CHANN_1])
						{
							TIM10_reg->CCR1 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM11:
			if (true == is_timerInit[TIM11])
			{
				switch (Channel)
				{
					case CHANN_1:
						if (true == is_PWMinit[TIM11][CHANN_1])
						{
							TIM11_reg->CCR1 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		case TIM12:
			if (true == is_timerInit[TIM12])
			{
				switch (Channel)
				{
					case CHANN_1:
						if (true == is_PWMinit[TIM12][CHANN_1])
						{
							TIM12_reg->CCR1 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					case CHANN_2:
						if (true == is_PWMinit[TIM12][CHANN_2])
						{
							TIM12_reg->CCR2 = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
						}
						else
						{
							ReturnVal = NOT_OK;
						}
						break;
					default:
						ReturnVal = NOT_OK;
						break;
				}
			}
			else
			{
				ReturnVal = NOT_OK;
			}
			break;
		default:
			ReturnVal = NOT_OK;
			break;
	}		

	return ReturnVal;
}
