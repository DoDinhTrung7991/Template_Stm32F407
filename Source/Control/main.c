#include "GPIO.h"

int main(void)
{

    GPIO_setup(GPIOEEN, 4, IN, AF0, PP, PU);
    GPIO_setup(GPIOAEN, 6, GP_OUT, AF0, PP, PU);
   
    while(1)
    {
        if(!GPIO_IN_getVal(GPIOEEN, 4))
        {
            GPIO_OUT_setVal(GPIOAEN, 6, 0);
        }
        else
        {
            GPIO_OUT_setVal(GPIOAEN, 6, 1);
        }
    }
}
