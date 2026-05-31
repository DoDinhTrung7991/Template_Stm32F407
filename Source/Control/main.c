#include "GPIO.h"
#include "Timer.h"

int main(void)
{
    GPIO_setup(GPIOAEN, 6U, GP_OUT, AF0, PP, NoP);
    Timer_init(TIM2, 1U, true);

    while (1)
    {
        // do nothing
    }

    return 0;
}
