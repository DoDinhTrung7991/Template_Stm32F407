#ifndef INC_SYSTICK_HEADER_H_
#define INC_SYSTICK_HEADER_H_

#include <stdint.h>

typedef struct SYSTICK_str
{
	volatile uint32_t CSR;
	volatile uint32_t RVR;
	volatile uint32_t CVR;
	volatile uint32_t CALIB;
} SYSTICK_t;

SYSTICK_t *SYSTICK_reg = (SYSTICK_t *)0xE000E010;

#endif

