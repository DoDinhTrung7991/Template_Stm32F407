#include "stdUtility.h"

#define HSI_VALUE 16000000U
#define HSE_VALUE 8000000U
#define LSE_VALUE 32768
#define LSI_VALUE 32768

typedef  enum
{
	PRIGROUP_0,
	PRIGROUP_1,
	PRIGROUP_2,
	PRIGROUP_3,
	PRIGROUP_4,
	PRIGROUP_5,
	PRIGROUP_6,
	PRIGROUP_7
} priGroup_t;

typedef unsigned int systickFreq_t;

typedef struct
{
	priGroup_t priGroupField;
	systickFreq_t systickFreq;
} priConf_t;

typedef enum
{
	HSE,
	HSI,
	LSE,
	LSI
} oscillatorType_t;

typedef struct
{
	bool PLL_enable;
	uint8_t PLLM;
	uint16_t PLLN;
	uint8_t PLLP;
	uint8_t PLLQ;
} PLL_t;

typedef struct
{
	oscillatorType_t Oscillator;
	unsigned char HSITRIM;
	PLL_t PLL;
} oscillatorConf_t;

typedef enum
{
	zero,
	one,
	two,
	three,
	four,
	five,
	six,
	seven
} flatency_t;

typedef enum
{
	AHB_not_divided,
	AHB_divided_by_2,
	AHB_divided_by_4,
	AHB_divided_by_8,
	AHB_divided_by_16,
	AHB_divided_by_64,
	AHB_divided_by_128,
	AHB_divided_by_256,
	AHB_divided_by_512
} HPRE_t;

typedef enum
{
	APBx_not_divided,
	APBx_divided_by_2,
	APBx_divided_by_4,
	APBx_divided_by_8,
	APBx_divided_by_16,
} PPREx_t;

typedef struct
{
	HPRE_t AHB_prescaler;
	PPREx_t PPRE1;
	PPREx_t PPRE2;
} clockConf_t;

bool initConfig(priConf_t priConf_st, oscillatorConf_t oscillatorConf_st, clockConf_t clockConf_st);
