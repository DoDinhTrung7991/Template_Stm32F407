#include "IWDG_header.h"
#include "IWDG.h"
#include "bit_operator.h"
#include "Interrupt.h"

#define WATCHDOG_START 0xCCCCUL
#define WATCHDOG_RESET 0xAAAAUL
#define WATCHDOG_WR_ENABLE 0x5555UL

IWDG_t *IWDG_reg = (IWDG_t *)0x40003000;

bool IWDG_init(IWDG_timeout_t timeout)
{
    uint32_t timegap_u32;

    // Start IWDG
    WRITE_REG(IWDG_reg->KR, 0xFFFFUL, 0U, WATCHDOG_START);
    // Enable write IWDG_PR and IWDG_RLR
    WRITE_REG(IWDG_reg->KR, 0xFFFFUL, 0U, WATCHDOG_WR_ENABLE);
    // Setting Prescaler
    WRITE_REG(IWDG_reg->PR, 0x7UL, 0U, timeout);

    timegap_u32 = SysTick_cnt_u32;

    // Waiting for Prescaler update completed.
    while (READ_REG(IWDG_reg->SR, 1UL, 0U))
    {
        if (
			((SysTick_cnt_u32 < timegap_u32) && (5UL <= (SysTick_cnt_u32 + (0xFFFFFFFFUL - timegap_u32) - 1)))
			|| ((SysTick_cnt_u32 >= timegap_u32) && (5UL <= (SysTick_cnt_u32 - timegap_u32)))
		)
		{
			return NOT_OK;
		}
    }

    // Reset IWDG Counter
    WRITE_REG(IWDG_reg->KR, 0xFFFFUL, 0U, WATCHDOG_RESET);

    return OK;
}

void IWDG_reset(void)
{
    // Reset IWDG Counter
    WRITE_REG(IWDG_reg->KR, 0xFFFFUL, 0U, WATCHDOG_RESET);
}
