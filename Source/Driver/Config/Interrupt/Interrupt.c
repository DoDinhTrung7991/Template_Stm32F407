#include "Interrupt.h"
#include "SYSCFG_header.h"
#include "NVIC_header.h"
#include "EXTI_header.h"
#include "bit_operator.h"

EXTI_t *EXTI_reg = (EXTI_t*)0x40013C00;

void NVIC_ISER_setVal(peripheral_Selection_t peripheral_Selection_en)
{
    uint8_t bytePos = peripheral_Selection_en / 32U;
    uint8_t bitPos = peripheral_Selection_en - (bytePos * 32U);
    WRITE_REG(NVIC_reg->ISER[bytePos], 1UL, bitPos, 1UL);
}

bool Ex_Interrupt(GPIO_ENABLE_t GPIOx_en, uint8_t pos_u8, GPIO_pullDir_t GPIO_pullDir_en, EvRaising_Dir_t EvRaising_Dir_en)
{
    bool returnVal = OK;

    switch (GPIOx_en)
    {
        case GPIOEEN:
            switch (GPIO_pullDir_en)
            {
                case PU:
                    GPIO_IN_setup(GPIOEEN, pos_u8, PU);
                    break;

                case PD:
                    GPIO_IN_setup(GPIOEEN, pos_u8, PD);
                    break;

                case NoP:
                    GPIO_IN_setup(GPIOEEN, pos_u8, NoP);
                    break;

                default:
                    break;
            }

            switch (EvRaising_Dir_en)
            {
                case Falling_Edge:
                    WRITE_REG(EXTI_reg->RTSR, 1UL, pos_u8, 0UL);
                    WRITE_REG(EXTI_reg->FTSR, 1UL, pos_u8, 1UL);
                    break;
                
                case Rising_Edge:
                    WRITE_REG(EXTI_reg->RTSR, 1UL, pos_u8, 1UL);
                    WRITE_REG(EXTI_reg->FTSR, 1UL, pos_u8, 0UL);
                    break;

                case Both_Edge:
                    WRITE_REG(EXTI_reg->RTSR, 1UL, pos_u8, 1UL);
                    WRITE_REG(EXTI_reg->FTSR, 1UL, pos_u8, 1UL);
                    break;

                default:
                    returnVal = NOT_OK;
                    break;
            }

            switch (pos_u8)
            {
                case 3:
                    NVIC_ISER_setVal(EXTI3);
                    WRITE_REG(SYSCFG_reg->EXTICR1, 0xFUL, 12U, GPIOEEN);
                    WRITE_REG(EXTI_reg->EMR, 1UL, pos_u8, 0UL);
                    WRITE_REG(EXTI_reg->IMR, 1UL, pos_u8, 1UL);
                    break;

                case 4:
                    NVIC_ISER_setVal(EXTI4);
                    WRITE_REG(SYSCFG_reg->EXTICR2, 0xFUL, 0U, GPIOEEN);
                    WRITE_REG(EXTI_reg->EMR, 1UL, pos_u8, 0UL);
                    WRITE_REG(EXTI_reg->IMR, 1UL, pos_u8, 1UL);
                    break;

                default:
                    returnVal = NOT_OK;
                    break;
            }

            break;

        default:
            returnVal = NOT_OK;
            break;
    }

    return returnVal;
}
