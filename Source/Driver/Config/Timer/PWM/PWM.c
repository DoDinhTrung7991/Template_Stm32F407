#include "GPIO.h"
#include "Timer.h"

/*Variable - Start*/

static bool is_PWMinit[MAX_TIMER_NUMBER][MAX_CHANNEL_NUMBER] = { 0 };
const unsigned int OCxM_bit[2] = {4U, 12U};
const unsigned int OCxPE_bit[2] = {3U, 11U};
const unsigned int OCxFE_bit[2] = {2U, 10U};

/*Variable - End*/

bool PWM_init(TIMx_t TIMx_en, TIM_Channel_t Channel, uint8_t frequency_u8)
{
	is_PWMinit[TIMx_en][Channel] = false;

	if (OK != (Timer_init(TIMx_en, frequency_u8, false))
		||	(MAX_TIMER_NUMBER < TIMx_en)
		|| 	(TIM6 == TIMx_en)
		|| 	(TIM7 == TIMx_en)
		|| 	(
				((TIM9 == TIMx_en) || (TIM12 == TIMx_en))
				&& (CHANN_2 < Channel)
			)
		|| 	(
				(
					(TIM10 == TIMx_en)
					|| (TIM11 == TIMx_en)
					|| (TIM13 == TIMx_en)
					|| (TIM14 == TIMx_en)
				)
				&& (CHANN_1 < Channel)
			)
	)
	{
		return NOT_OK;
	}

	switch (TIMx_en)
	{
		case TIM1:
		case TIM8:
			// Main output enable
			SET_BIT(TIM_reg[TIMx_en]->BDTR, 15U);
			break;
		default:
			break;
	}

	// Disable Counter
	CLEAR_BIT(TIM_reg[TIMx_en]->CR1, 0U);
	// CCx channel is configured as output
	WRITE_REG(TIM_reg[TIMx_en]->CCMR[Channel / 2U], 3UL, ((Channel % 2) * 8), 0UL);
	// Choose Output compare mode
	WRITE_REG(TIM_reg[TIMx_en]->CCMR[Channel / 2U], 7UL, OCxM_bit[Channel % 2], 6UL);
	// Output compare preload enable
	SET_BIT(TIM_reg[TIMx_en]->CCMR[Channel / 2U], OCxPE_bit[Channel % 2]);
	// Output compare fast enable
	SET_BIT(TIM_reg[TIMx_en]->CCMR[Channel / 2U], OCxFE_bit[Channel % 2]);
	// Output compare enable
	SET_BIT(TIM_reg[TIMx_en]->CCER, (Channel * 4U));

	// Setup GPIO
	switch (TIMx_en)
	{
		case TIM1:
			if (Channel == CHANN_1) GPIO_setup(GPIOAEN, 8U, AF, AF1, PP, NoP);
			if (Channel == CHANN_2) GPIO_setup(GPIOAEN, 9U, AF, AF1, PP, NoP);
			if (Channel == CHANN_3) GPIO_setup(GPIOAEN, 10U, AF, AF1, PP, NoP);
			if (Channel == CHANN_4) GPIO_setup(GPIOAEN, 11U, AF, AF1, PP, NoP);
			break;

		case TIM2:
			if (Channel == CHANN_1) GPIO_setup(GPIOAEN, 0U, AF, AF1, PP, NoP);
			if (Channel == CHANN_2) GPIO_setup(GPIOAEN, 1U, AF, AF1, PP, NoP);
			if (Channel == CHANN_3) GPIO_setup(GPIOAEN, 2U, AF, AF1, PP, NoP);
			if (Channel == CHANN_4) GPIO_setup(GPIOAEN, 3U, AF, AF1, PP, NoP);
			break;

		case TIM3:
			if (Channel == CHANN_1) GPIO_setup(GPIOAEN, 6U, AF, AF2, PP, NoP);
			if (Channel == CHANN_2) GPIO_setup(GPIOAEN, 7U, AF, AF2, PP, NoP);
			if (Channel == CHANN_3) GPIO_setup(GPIOBEN, 0U, AF, AF2, PP, NoP);
			if (Channel == CHANN_4) GPIO_setup(GPIOBEN, 1U, AF, AF2, PP, NoP);
			break;

		case TIM4:
			if (Channel == CHANN_1) GPIO_setup(GPIOBEN, 6U, AF, AF2, PP, NoP);
			if (Channel == CHANN_2) GPIO_setup(GPIOBEN, 7U, AF, AF2, PP, NoP);
			if (Channel == CHANN_3) GPIO_setup(GPIOBEN, 8U, AF, AF2, PP, NoP);
			if (Channel == CHANN_4) GPIO_setup(GPIOBEN, 9U, AF, AF2, PP, NoP);
			break;

		case TIM5:
			if (Channel == CHANN_1) GPIO_setup(GPIOAEN, 0U, AF, AF2, PP, NoP);
			if (Channel == CHANN_2) GPIO_setup(GPIOAEN, 1U, AF, AF2, PP, NoP);
			if (Channel == CHANN_3) GPIO_setup(GPIOAEN, 2U, AF, AF2, PP, NoP);
			if (Channel == CHANN_4) GPIO_setup(GPIOAEN, 3U, AF, AF2, PP, NoP);
			break;

		case TIM8:
			if (Channel == CHANN_1) GPIO_setup(GPIOCEN, 6U, AF, AF3, PP, NoP);
			if (Channel == CHANN_2) GPIO_setup(GPIOCEN, 7U, AF, AF3, PP, NoP);
			if (Channel == CHANN_3) GPIO_setup(GPIOCEN, 8U, AF, AF3, PP, NoP);
			if (Channel == CHANN_4) GPIO_setup(GPIOCEN, 9U, AF, AF3, PP, NoP);
			break;

		case TIM9:
			if (Channel == CHANN_1) GPIO_setup(GPIOEEN, 5U, AF, AF3, PP, NoP);
			if (Channel == CHANN_2) GPIO_setup(GPIOEEN, 6U, AF, AF3, PP, NoP);
			break;
			
		case TIM10:
			if (Channel == CHANN_1) GPIO_setup(GPIOBEN, 8U, AF, AF3, PP, NoP);
			break;

		case TIM11:
			if (Channel == CHANN_1) GPIO_setup(GPIOBEN, 9U, AF, AF3, PP, NoP);
			break;

		case TIM12:
			if (Channel == CHANN_1) GPIO_setup(GPIOBEN, 14U, AF, AF9, PP, NoP);
			if (Channel == CHANN_2) GPIO_setup(GPIOBEN, 15U, AF, AF9, PP, NoP);
			break;

		case TIM13:
			if (Channel == CHANN_1) GPIO_setup(GPIOAEN, 6U, AF, AF9, PP, NoP);
			break;
		
		case TIM14:
			if (Channel == CHANN_1) GPIO_setup(GPIOAEN, 7U, AF, AF9, PP, NoP);
			break;
		
		default:
			return NOT_OK;
			break;
	}

	is_PWMinit[TIMx_en][Channel] = true;

	return OK;
}

bool PWM_Generation(TIMx_t TIMx_en, TIM_Channel_t Channel, uint8_t activePercent_u8_int, uint8_t activePercent_floating_point)
{
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
			// do nothing
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

	if ((true == is_timerInit[TIMx_en]) && (true == is_PWMinit[TIMx_en][Channel]))
	{
		TIM_reg[TIMx_en]->CCR[Channel] = (unsigned short)((((ARR_CONST + 1) * activePercent_u8_int) / 100U) + (floating_point_u8 * 2U / 10U));
	}
	else
	{
		return NOT_OK;
	}

	// Reset Counter
	TIM_reg[TIMx_en]->CNT = 0U;
	// Enable Counter
	SET_BIT(TIM_reg[TIMx_en]->CR1, 0U);

	return OK;
}
