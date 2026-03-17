#include "UART.h"
#include "GPIO.h"

const uint16_t tx_data[4] = {48, 49, 50, 51};

int main(void)
{

    GPIO_setup(GPIOEEN, 4, IN, AF0, PP, PU);
    UART_init(USART1, 115200);
   
    while(1)
    {
        if(!GPIO_IN_getVal(GPIOEEN, 4))
        {
            UART_transmit(USART1, tx_data, 4);
        }
    }
}
