#include "UART.h"

int main(void)
{
    uint16_t my_buf[3] = {48, 49, 50};

    UART_init(USART1, 115200);
    UART_transmit(USART1, my_buf, 3);
   
    while(1)
    {
        if (isUpdated_UART[USART1])
        {
            UART_Read(USART1, my_buf, 3);
            UART_transmit(USART1, my_buf, 3);
        }
    }
}
