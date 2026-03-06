#ifndef _H_INTERRUPT_
#define _H_INTERRUPT_

#include "stdUtility.h"
#include "GPIO.h"

typedef enum
{
    WWDG,
    PVD,
    TAMP_STAMP,
    RTC_WKUP,
    FLASH,
    RCC,
    EXTI0,
    EXTI1,
    EXTI2,
    EXTI3,
    EXTI4,
    DMA1_Stream0,
    DMA1_Stream1,
    DMA1_Stream2,
    DMA1_Stream3,
    DMA1_Stream4,
    DMA1_Stream5,
    DMA1_Stream6,
    ADC,
    CAN1_TX,
    CAN1_RX0,
    CAN1_RX1,
    CAN1_SCE,
    EXTI9_5,
    TIM1_BRK_TIM9,
    TIM1_UP_TIM10,
    TIM1_TRG_COM_TIM11,
    TIM1_CC,
    TIM2,
    TIM3,
    TIM4,
    I2C1_EV,
    I2C1_ER,
    I2C2_EV,
    I2C2_ER,
    SPI1,
    SPI2,
    USART1_Interrupt
} peripheral_Selection_t;

typedef enum
{
    Falling_Edge,
    Rising_Edge,
    Both_Edge
} EvRaising_Dir_t;

void NVIC_ISER_setVal(peripheral_Selection_t peripheral_Selection_en);
void NVIC_ICER_setVal(peripheral_Selection_t peripheral_Selection_en);
bool Ex_Interrupt(GPIO_ENABLE_t GPIOx_en, uint8_t pos_u8, GPIO_pullDir_t GPIO_pullDir_en, EvRaising_Dir_t EvRaising_Dir_en);

#endif
