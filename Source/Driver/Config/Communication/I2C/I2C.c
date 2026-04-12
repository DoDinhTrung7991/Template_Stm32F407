#include "I2C.h"
#include "init_static.h"
#include "bit_operator.h"
#include "I2C_header.h"
#include "RCC_header.h"
#include "Interrupt.h"
#include "GPIO.h"

I2C_t *I2C_reg[3] = 
{
    (I2C_t *)0x40005400,
    (I2C_t *)0x40005800,
    (I2C_t *)0x40005C00
};

bool I2C_init(I2Cx_t I2Cx_en)
{
    uint32_t I2C_freq_u32 = APB1_freq/(2 * 1000000);

    switch (I2Cx_en)
    {
        case I2C1:
            // Enable I2C clock
            SET_BIT(RCC_reg->APB1ENR, 21U);
            // Setup GPIO for I2C
            GPIO_setup(GPIOBEN, 8, AF, AF4, OD, PU);	// SCL
			GPIO_setup(GPIOBEN, 9, AF, AF4, OD, PU);	// SDA
            /*
            GPIO_setup(GPIOBEN, 6, AF, AF4, OD, PU);	// SCL
			GPIO_setup(GPIOBEN, 7, AF, AF4, OD, PU);	// SDA
            */
            // Enable ISR for I2C
            NVIC_ISER_setVal(I2C1_EV);
            NVIC_ISER_setVal(I2C1_ER);
            break;

        case I2C2:
            // Enable I2C clock
            SET_BIT(RCC_reg->APB1ENR, 22U);
            // Setup GPIO for I2C
            GPIO_setup(GPIOBEN, 10, AF, AF4, OD, PU);	// SCL
			GPIO_setup(GPIOBEN, 11, AF, AF4, OD, PU);	// SDA
            // Enable ISR for I2C
            NVIC_ISER_setVal(I2C2_EV);
            NVIC_ISER_setVal(I2C2_ER);
            break;

        case I2C3:
            // Enable I2C clock
            SET_BIT(RCC_reg->APB1ENR, 23U);
            // Setup GPIO for I2C
            GPIO_setup(GPIOAEN, 8, AF, AF4, OD, PU);	// SCL
			GPIO_setup(GPIOCEN, 9, AF, AF4, OD, PU);	// SDA
            // Enable ISR for I2C
            NVIC_ISER_setVal(I2C3_EV);
            NVIC_ISER_setVal(I2C3_ER);
            break;

        default:
            return NOT_OK;
    }

    // Peripheral disable
    CLEAR_BIT(I2C_reg[I2Cx_en]->CR1, 0U);
    // DMA requests enable
    SET_BIT(I2C_reg[I2Cx_en]->CR2, 11U);
    // Enable Event interrupt enable
    SET_BIT(I2C_reg[I2Cx_en]->CR2, 9U);
    // Enable Error interrupt enable
    SET_BIT(I2C_reg[I2Cx_en]->CR2, 8U);
    // Set Peripheral clock frequency
    WRITE_REG(I2C_reg[I2Cx_en]->CR2, 0x3FUL, 0U, I2C_freq_u32);
    // I2C master mode selection: Sm
    CLEAR_BIT(I2C_reg[I2Cx_en]->CCR, 15U);
    // Clock control register in Fm/Sm mode (Master mode)
    WRITE_REG(I2C_reg[I2Cx_en]->CCR, 0xFFFUL, 0U, ((I2C_freq_u32 * 1000000) / (2 * 100000)));
    // Maximum rise time in Fm/Sm mode (Master mode): 1000ns
    WRITE_REG(I2C_reg[I2Cx_en]->TRISE, 0x3FUL, 0U, (I2C_freq_u32 + 1));
    // Acknowledge enable
    SET_BIT(I2C_reg[I2Cx_en]->CR1, 10U);
    // Peripheral enable
    SET_BIT(I2C_reg[I2Cx_en]->CR1, 0U);

    return OK;
}
