#include "I2C.h"
#include "bit_operator.h"
#include "I2C_header.h"
#include "RCC_header.h"
#include "GPIO.h"

bool I2C_init(I2Cx_t I2Cx_en)
{
    switch (I2Cx_en)
    {
        case I2C1:
            RCC_reg->APB1ENR |= (1UL << 21U);
            GPIO_OUT_setup(GPIOBEN, 5U, AF, AF4, OD, PU);
            GPIO_OUT_setup(GPIOBEN, 6U, AF, AF4, OD, PU);
            GPIO_OUT_setup(GPIOBEN, 7U, AF, AF4, OD, PU);
            WRITE_REG(I2C1_reg->CR2, 0x3FUL, 0U, 4UL);
            break;
        
        default:
            break;
    }
}
