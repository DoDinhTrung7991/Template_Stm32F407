#include "init.h"
#include "GPIO.h"

int main(void)
{
    uint32_t temp_u32;
    uint8_t toggle = 1;

    GPIO_setup(GPIOAEN, 6U, GP_OUT, AF0, PP, PU);
    temp_u32 = SysTick_cnt_u32;
   
    while(1)
    {
        if (SysTick_cnt_u32 - temp_u32 >= 1000 && (toggle == 1))
        {
            GPIO_OUT_setVal(GPIOAEN, 6U, 0U);
            temp_u32 = SysTick_cnt_u32;
            toggle = 0;
        }
        else if (SysTick_cnt_u32 - temp_u32 >= 1000 && (toggle == 0))
        {
            GPIO_OUT_setVal(GPIOAEN, 6U, 1U);
            temp_u32 = SysTick_cnt_u32;
            toggle = 1;
        }
        else
        {
        
        }
    }
}
