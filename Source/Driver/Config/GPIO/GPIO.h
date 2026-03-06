#ifndef _GPIO_H_
#define _GPIO_H_

#include "stdUtility.h"
#include "GPIO_header.h"
#include "RCC_header.h"

typedef enum
{
    GP,
    AF,
} GPIO_purpose_t;

typedef enum
{
    AF0,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15
} AFRx_t;

typedef enum
{
    PP,
    OD
} GPIO_outputType_t;

typedef enum
{
    PU,
    PD,
    NoP
} GPIO_pullDir_t;

typedef enum
{
    GPIO_STATUS_RESET,
    GPIO_STATUS_SET
} GPIO_Status_t;

typedef enum
{
	GPIOAEN,
	GPIOBEN,
	GPIOCEN,
	GPIODEN,
	GPIOEEN,
	GPIOFEN,
	GPIOGEN,
	GPIOHEN,
	GPIOIEN,
	GPIOJEN,
	GPIOKEN
} GPIO_ENABLE_t;

extern bool GPIOx_IN_getVal_check_b;

bool GPIO_IN_setup(GPIO_ENABLE_t GPIOx_en, uint8_t pos_u8, GPIO_pullDir_t GPIO_pullDir);
bool GPIO_IN_getVal(GPIO_ENABLE_t GPIOx_en, uint8_t pos_u8);
bool GPIO_OUT_setup(GPIO_ENABLE_t GPIOx_en, uint8_t pos_u8, GPIO_purpose_t GPIO_purpose_en, AFRx_t AFx_en, GPIO_outputType_t GPIO_outputType_en, GPIO_pullDir_t GPIO_pullDir_en);
bool GPIO_OUT_setVal(GPIO_ENABLE_t GPIOx_en, uint8_t pos_u8, bool setVal_b);

#endif
