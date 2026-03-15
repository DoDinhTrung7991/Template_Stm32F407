#ifndef INC_DMA_HEADER_H_
#define INC_DMA_HEADER_H_

#include <stdint.h>

typedef struct Stream_st
{
    volatile uint32_t CR;
	volatile uint32_t NDTR;
	volatile uint32_t PAR;
    volatile uint32_t M0AR;
    volatile uint32_t M1AR;
    volatile uint32_t FCR;
} Stream_t;

typedef struct DMA_str
{
	volatile uint32_t LISR;
	volatile uint32_t HISR;
	volatile uint32_t LIFCR;
	volatile uint32_t HIFCR;
	Stream_t S[8];
} DMA_t;

extern DMA_t *DMA1_reg;
extern DMA_t *DMA2_reg;

#endif
