#include "GPIO.h"
#include "Timer.h"

int main(void)
{
    GPIO_setup(GPIOEEN, 4U, IN, AF0, PP, PU);
    GPIO_setup(GPIOAEN, 6U, GP_OUT, AF0, PP, PU);
    PWM_init(TIM13, CHANN_1, 50);
    PWM_Generation(TIM13, CHANN_1, 50, 0);

    while (1)
    {
        if (GPIO_IN_getVal(GPIOEEN, 4U))
        {
            GPIO_OUT_setVal(GPIOAEN, 6U, 1U);
        }
        else
        {
            GPIO_OUT_setVal(GPIOAEN, 6U, 0U);
        }
    }

    return 0;
}
