#ifndef INC_DMA_HEADER_H_
#define INC_DMA_HEADER_H_

#include <stdint.h>

typedef struct Stream_st
{
    volatile uint32_t CR;
	volatile uint32_t NDTR;
	volatile uint32_t PAR;
    volatile uint32_t MAR[2];
    volatile uint32_t FCR;
} Stream_reg_t;

typedef struct DMA_str
{
	volatile uint32_t ISR[2];
	volatile uint32_t IFCR[2];
	Stream_reg_t S[8];
} DMA_t;

#endif
