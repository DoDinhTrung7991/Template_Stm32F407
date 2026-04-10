#ifndef INC_WWDG_HEADER_H_
#define INC_WWDG_HEADER_H_

#include <stdint.h>

typedef struct WWDG_str
{
    volatile uint32_t CR;
    volatile uint32_t CFR;
    volatile uint32_t SR;
} WWDG_t;

#endif
