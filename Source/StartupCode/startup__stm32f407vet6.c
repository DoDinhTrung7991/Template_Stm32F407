#include "stdUtility.h"
#include "bit_operator.h"
#include "main.h"
#include "init.h"
#include "EXTI_header.h"
#include "DMA_header.h"
#include "UART.h"
#include "Timer.h"

typedef void (*isr_fnct_t)(void);

extern uint32_t _ccmram_sidata;
extern uint32_t _ccmram_sdata;
extern uint32_t _ccmram_edata;
extern uint32_t _ccmram_sbss;
extern uint32_t _ccmram_ebss;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _estack;

__attribute__((section(".ccmram_data")))volatile uint32_t SysTick_cnt_u32 = 0;

void Default_Handler(void);

void Reset_Handler(void);
__attribute__((weak, alias("Default_Handler")))void NMI_Handler(void);
__attribute__((weak, alias("Default_Handler")))void HardFault_Handler(void);
__attribute__((weak, alias("Default_Handler")))void MemManage_Handler(void);
__attribute__((weak, alias("Default_Handler")))void BusFault_Handler(void);
__attribute__((weak, alias("Default_Handler")))void UsageFault_Handler(void);
__attribute__((weak, alias("Default_Handler")))void SVCall_Handler(void);
__attribute__((weak, alias("Default_Handler")))void Debug_Handler(void);
__attribute__((weak, alias("Default_Handler")))void PendSV_Handler(void);
void SysTick_Handler(void);
__attribute__((weak, alias("Default_Handler")))void WWDG_Handler(void);
__attribute__((weak, alias("Default_Handler")))void PVD_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TAMP_STAMP_Handler(void);
__attribute__((weak, alias("Default_Handler")))void RTC_WKUP_Handler(void);
__attribute__((weak, alias("Default_Handler")))void FLASH_Handler(void);
__attribute__((weak, alias("Default_Handler")))void RCC_Handler(void);
__attribute__((weak, alias("Default_Handler")))void EXTI0_Handler(void);
__attribute__((weak, alias("Default_Handler")))void EXTI1_Handler(void);
__attribute__((weak, alias("Default_Handler")))void EXTI2_Handler(void);
void EXTI3_Handler(void);
void EXTI4_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA1_Stream0_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA1_Stream1_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA1_Stream2_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA1_Stream3_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA1_Stream4_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA1_Stream5_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA1_Stream6_Handler(void);
__attribute__((weak, alias("Default_Handler")))void ADC_Handler(void);
__attribute__((weak, alias("Default_Handler")))void CAN1_TX_Handler(void);
__attribute__((weak, alias("Default_Handler")))void CAN1_RX0_Handler(void);
__attribute__((weak, alias("Default_Handler")))void CAN1_RX1_Handler(void);
__attribute__((weak, alias("Default_Handler")))void CAN1_SCE_Handler(void);
__attribute__((weak, alias("Default_Handler")))void EXTI9_5_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM1_BRK_TIM9_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM1_UP_TIM10_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM1_TRG_COM_TIM11_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM1_CC_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM2_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM3_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM4_Handler(void);
__attribute__((weak, alias("Default_Handler")))void I2C1_EV_Handler(void);
__attribute__((weak, alias("Default_Handler")))void I2C1_ER_Handler(void);
__attribute__((weak, alias("Default_Handler")))void I2C2_EV_Handler(void);
__attribute__((weak, alias("Default_Handler")))void I2C2_ER_Handler(void);
__attribute__((weak, alias("Default_Handler")))void SPI1_Handler(void);
__attribute__((weak, alias("Default_Handler")))void SPI2_Handler(void);
void USART1_Handler(void);
__attribute__((weak, alias("Default_Handler")))void USART2_Handler(void);
__attribute__((weak, alias("Default_Handler")))void USART3_Handler(void);
__attribute__((weak, alias("Default_Handler")))void EXTI15_10_Handler(void);
__attribute__((weak, alias("Default_Handler")))void RTC_Alarm_Handler(void);
__attribute__((weak, alias("Default_Handler")))void OTG_FS_WKUP_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM8_BRK_TIM12_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM8_UP_TIM13_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM8_TRG_COM_TIM14_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM8_CC_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA1_Stream7_Handler(void);
__attribute__((weak, alias("Default_Handler")))void FSMC_Handler(void);
__attribute__((weak, alias("Default_Handler")))void SDIO_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM5_Handler(void);
__attribute__((weak, alias("Default_Handler")))void SPI3_Handler(void);
__attribute__((weak, alias("Default_Handler")))void UART4_Handler(void);
__attribute__((weak, alias("Default_Handler")))void UART5_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM6_DAC_Handler(void);
__attribute__((weak, alias("Default_Handler")))void TIM7_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA2_Stream0_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA2_Stream1_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA2_Stream2_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA2_Stream3_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA2_Stream4_Handler(void);
__attribute__((weak, alias("Default_Handler")))void ETH_Handler(void);
__attribute__((weak, alias("Default_Handler")))void ETH_WKUP_Handler(void);
__attribute__((weak, alias("Default_Handler")))void CAN2_TX_Handler(void);
__attribute__((weak, alias("Default_Handler")))void CAN2_RX0_Handler(void);
__attribute__((weak, alias("Default_Handler")))void CAN2_RX1_Handler(void);
__attribute__((weak, alias("Default_Handler")))void CAN2_SCE_Handler(void);
__attribute__((weak, alias("Default_Handler")))void OTG_FS_Handler(void);
void DMA2_Stream5_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DMA2_Stream6_Handler(void);
void DMA2_Stream7_Handler(void);
__attribute__((weak, alias("Default_Handler")))void USART6_Handler(void);
__attribute__((weak, alias("Default_Handler")))void I2C3_EV_Handler(void);
__attribute__((weak, alias("Default_Handler")))void I2C3_ER_Handler(void);
__attribute__((weak, alias("Default_Handler")))void OTG_HS_EP1_OUT_Handler(void);
__attribute__((weak, alias("Default_Handler")))void OTG_HS_EP1_IN_Handler(void);
__attribute__((weak, alias("Default_Handler")))void OTG_HS_WKUP_Handler(void);
__attribute__((weak, alias("Default_Handler")))void OTG_HS_Handler(void);
__attribute__((weak, alias("Default_Handler")))void DCMI_Handler(void);
__attribute__((weak, alias("Default_Handler")))void CRYP_Handler(void);
__attribute__((weak, alias("Default_Handler")))void HASH_RNG_Handler(void);
__attribute__((weak, alias("Default_Handler")))void FPU_Handler(void);

__attribute__((section(".isr_vector"), used)) isr_fnct_t isr_vector_arr[] = // vector table placed at .isr_vector section
{
    (isr_fnct_t)&_estack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    SVCall_Handler,
    Debug_Handler,
    PendSV_Handler,
    SysTick_Handler,
    WWDG_Handler,
    PVD_Handler,
    TAMP_STAMP_Handler,
    RTC_WKUP_Handler,
    FLASH_Handler,
    RCC_Handler,
    EXTI0_Handler,
    EXTI1_Handler,
    EXTI2_Handler,
    EXTI3_Handler,
    EXTI4_Handler,
    DMA1_Stream0_Handler,
    DMA1_Stream1_Handler,
    DMA1_Stream2_Handler,
    DMA1_Stream3_Handler,
    DMA1_Stream4_Handler,
    DMA1_Stream5_Handler,
    DMA1_Stream6_Handler,
    ADC_Handler,
    CAN1_TX_Handler,
    CAN1_RX0_Handler,
    CAN1_RX1_Handler,
    CAN1_SCE_Handler,
    EXTI9_5_Handler,
    TIM1_BRK_TIM9_Handler,
    TIM1_UP_TIM10_Handler,
    TIM1_TRG_COM_TIM11_Handler,
    TIM1_CC_Handler,
    TIM2_Handler,
    TIM3_Handler,
    TIM4_Handler,
    I2C1_EV_Handler,
    I2C1_ER_Handler,
    I2C2_EV_Handler,
    I2C2_ER_Handler,
    SPI1_Handler,
    SPI2_Handler,
    USART1_Handler,
    USART2_Handler,
    USART3_Handler,
    EXTI15_10_Handler,
    RTC_Alarm_Handler,
    OTG_FS_WKUP_Handler,
    TIM8_BRK_TIM12_Handler,
    TIM8_UP_TIM13_Handler,
    TIM8_TRG_COM_TIM14_Handler,
    TIM8_CC_Handler,
    DMA1_Stream7_Handler,
    FSMC_Handler,
    SDIO_Handler,
    TIM5_Handler,
    SPI3_Handler,
    UART4_Handler,
    UART5_Handler,
    TIM6_DAC_Handler,
    TIM7_Handler,
    DMA2_Stream0_Handler,
    DMA2_Stream1_Handler,
    DMA2_Stream2_Handler,
    DMA2_Stream3_Handler,
    DMA2_Stream4_Handler,
    ETH_Handler,
    ETH_WKUP_Handler,
    CAN2_TX_Handler,
    CAN2_RX0_Handler,
    CAN2_RX1_Handler,
    CAN2_SCE_Handler,
    OTG_FS_Handler,
    DMA2_Stream5_Handler,
    DMA2_Stream6_Handler,
    DMA2_Stream7_Handler,
    USART6_Handler,
    I2C3_EV_Handler,
    I2C3_ER_Handler,
    OTG_HS_EP1_OUT_Handler,
    OTG_HS_EP1_IN_Handler,
    OTG_HS_WKUP_Handler,
    OTG_HS_Handler,
    DCMI_Handler,
    CRYP_Handler,
    HASH_RNG_Handler,
    FPU_Handler,
};

static inline void LMAtoVMA(uint32_t *pDst, uint32_t *pSrc, uint32_t *pDst_end);
static inline void clear_bss(uint32_t *pStart, uint32_t *pEnd);

void Reset_Handler(void)
{
    // Copy LMA data to VMA
    LMAtoVMA(&_sdata, &_sidata, &_edata);
    LMAtoVMA(&_ccmram_sdata, &_ccmram_sidata, &_ccmram_edata);

    // Clear bss memory
    clear_bss(&_sbss, &_ebss);
    clear_bss(&_ccmram_sbss, &_ccmram_ebss);

    if (OK == SystemInit()) // Check if System init being successful
    {
        (void)main();
    }
    else
    {
        // do nothing
    }

    while (1)
    {
        // do nothing
    }
}

void EXTI3_Handler(void)
{
	// It is not recommended to call initialization functions inside an ISR.
    // Timer_init() and PWM_init() should be called once in main().
    // This handler can be used to change the duty cycle, for example.
    PWM_Generation(TIM1, CHANN_3, 50, 0); // Example: Set duty cycle to 50%

	if (READ_REG(EXTI_reg->PR, 1UL, 3U))
	{
		// Clear the pending bit by writing 1 to it
        SET_BIT(EXTI_reg->PR, 3U);
	}
}

void EXTI4_Handler(void)
{
	// It is not recommended to call initialization functions inside an ISR.
    // Timer_init() and PWM_init() should be called once in main().
    // This handler can be used to change the duty cycle, for example.
	PWM_Generation(TIM1, CHANN_2, 50, 0); // Example: Set duty cycle to 50%

	if (READ_REG(EXTI_reg->PR, 1UL, 4U))
	{
		// Clear the pending bit by writing 1 to it
        SET_BIT(EXTI_reg->PR, 4U);
	}
}

void USART1_Handler(void)
{
    // Check if the RXNE (Receive Not Empty) flag is set in the Status Register
	if (READ_REG(USART_reg[USART1]->SR, 1UL, 5U))
	{
        UART_state_rx[USART1] = UART_STATE_BUSY;
	}

    // Check Overrun error, Noise ,Framing error, Parity error and IDLE flag
    if (READ_REG(USART_reg[USART1]->SR, 1UL, 3U) || READ_REG(USART_reg[USART1]->SR, 1UL, 2U) || READ_REG(USART_reg[USART1]->SR, 1UL, 1U) || READ_REG(USART_reg[USART1]->SR, 1UL, 0U) || READ_REG(USART_reg[USART1]->SR, 1UL, 4U))
    {
        // Clear error flags
        uint32_t temp = USART_reg[USART1]->SR;
        temp = USART_reg[USART1]->DR;
        (void)temp;
    }
}

void DMA2_Stream5_Handler(void)
{
    if (READ_REG(DMA2_reg->HISR, 1UL, 11U))
    {
        SET_BIT(DMA2_reg->HIFCR, 11U);
        isUpdated_UART[USART1] = true;
        UART_state_rx[USART1] = UART_STATE_READY;
    }
}

void DMA2_Stream7_Handler(void)
{
    if (READ_REG(DMA2_reg->HISR, 1UL, 27U))
    {
        SET_BIT(DMA2_reg->HIFCR, 27U);
        UART_state_tx[USART1] = UART_STATE_READY;
    }
}

void SysTick_Handler(void)
{
    SysTick_cnt_u32 ++;
}

void Default_Handler(void)
{
    while (1)
    {
        // user define
    }
}

static inline void LMAtoVMA(uint32_t *pDst, uint32_t *pSrc, uint32_t *pDst_end)
{
    while (pDst < pDst_end)
    {
        *(pDst++) = *(pSrc++);
    }
}

static inline void clear_bss(uint32_t *pStart, uint32_t *pEnd)
{
    while (pStart < pEnd)
    {
        *(pStart++) = 0;
    }
}
