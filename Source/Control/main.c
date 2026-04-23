#include "I2C.h"
#include "Interrupt.h"

int main(void)
{
    uint32_t timegap_u32;

    I2C_init(I2C1);

    while (1)
    {
        timegap_u32 = SysTick_cnt_u32;

	    while (
	    	((SysTick_cnt_u32 < timegap_u32) && (5UL > (SysTick_cnt_u32 + (0xFFFFFFFFUL - timegap_u32) - 1)))
	    	|| ((SysTick_cnt_u32 >= timegap_u32) && (5UL > (SysTick_cnt_u32 - timegap_u32)))
	    );

        I2C_master_recv(I2C1, 104, 14);
    }

    return 0;
}
