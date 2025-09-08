#ifndef _TIMER_H_
#define _TIMER_H_

#include "stdUtility.h"
#include "bit_operator.h"
#include "TIM1_header.h"
#include "TIM2_header.h"
#include "TIM9_header.h"
#include "TIM10_header.h"

/*Macro - Start*/

#define MAX_TIMER_NUMBER 14U
#define MAX_CHANNEL_NUMBER 4U
#define ARR_CONST 199U

/*Macro - End*/

/*Data type - Start*/

typedef enum
{
	TIM1,
	TIM2,
	TIM3,
	TIM4,
	TIM5,
	TIM6,
	TIM7,
	TIM8,
	TIM9,
	TIM10,
	TIM11,
	TIM12,
	TIM13,
	TIM14
} TIMx_t;

typedef enum
{
	CHANN_1,
	CHANN_2,
	CHANN_3,
	CHANN_4
} TIM_Channel_t;

/*Data type - End*/

/*Variable - Start*/

extern bool is_timerInit[MAX_TIMER_NUMBER];
extern uint8_t TIMxFrequency[MAX_TIMER_NUMBER];

/*Variable - End*/

/*Function - Start*/

bool Timer_init(TIMx_t TIMx_en, uint8_t frequency);
bool PWM_init(TIMx_t TIMx_en, TIM_Channel_t Channel);
bool PWM_Generation(TIMx_t TIMx_en, TIM_Channel_t Channel, uint8_t activePercent_u8_int, uint8_t activePercent_floating_point);

/*Function - End*/

#endif
