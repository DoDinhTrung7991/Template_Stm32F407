#include "SYSTICK_header.h"
#include "bit_operator.h"
#include "init_static.h"

void delay_us(uint32_t us)
{
    uint32_t startCountVal_u32 = READ_REG(SYSTICK_reg->VAL, 0xFFFFFFUL, 0);
    uint32_t ticks_per_1us_u32;
    uint32_t required_ticks_u32;
    uint32_t countVal_u32;
    uint32_t loadVal_u32 = READ_REG(SYSTICK_reg->LOAD, 0xFFFFFFUL, 0);

    if (READ_REG(SYSTICK_reg->CTRL, 1UL, 2U))
    {
        ticks_per_1us_u32 = AHB_freq / 1000000UL;
    }
    else
    {
        ticks_per_1us_u32 = (AHB_freq / 8UL) / 1000000UL;
    }

    required_ticks_u32 = us * ticks_per_1us_u32;

    while (1)
    {
        countVal_u32 = READ_REG(SYSTICK_reg->VAL, 0xFFFFFFUL, 0);

        if (
            ((startCountVal_u32 >= countVal_u32) && (required_ticks_u32 <= (startCountVal_u32 - countVal_u32)))
            || ((startCountVal_u32 < countVal_u32) && (required_ticks_u32 <= (startCountVal_u32 + (loadVal_u32 - countVal_u32))))
        )
        {
            break;
        }
    }
}
