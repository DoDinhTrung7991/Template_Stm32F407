#include "GPIO.h"
#include "UART.h"
#include <stdint.h>

int main(void)
{
	int rx_data = 48;

	UART_init(USART1, 9600); // Initialize UART with a 9600 baud rate
	GPIO_OUT_setup(GPIOAEN, 6, GP, AF7, PP, PU);
	GPIO_OUT_setup(GPIOAEN, 7, GP, AF7, PP, PU);

	GPIO_OUT_setVal(GPIOAEN, 6, 1);
	GPIO_OUT_setVal(GPIOAEN, 7, 1);

	while (1)
	{
		if (true == isUpdated_UART)
		{
			rx_data = UART_Read();

			if (48 == rx_data)
			{
				GPIO_OUT_setVal(GPIOAEN, 6, 0);
				GPIO_OUT_setVal(GPIOAEN, 7, 1);
			}
			else if (49 == rx_data)
			{
				GPIO_OUT_setVal(GPIOAEN, 6, 1);
				GPIO_OUT_setVal(GPIOAEN, 7, 0);
			}
			else
			{
				GPIO_OUT_setVal(GPIOAEN, 6, 0);
				GPIO_OUT_setVal(GPIOAEN, 7, 0);
			}

			uint8_t data_to_transmit = (uint8_t)rx_data;
			UART_transmit(USART1, &data_to_transmit, 1);
		}
	}

    return 0;
}
