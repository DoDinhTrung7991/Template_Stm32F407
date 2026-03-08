#include "GPIO.h"
#include "UART.h"

int main(void)
{
	int my_data = 0;

	UART_init(USART1, 9600); // Initialize UART with a 9600 baud rate
	GPIO_OUT_setup(GPIOAEN, 6, GP, AF7, PP, PU);
	GPIO_OUT_setup(GPIOAEN, 7, GP, AF7, PP, PU);

	GPIO_OUT_setVal(GPIOAEN, 6, 1);
	GPIO_OUT_setVal(GPIOAEN, 7, 1);

	while (1)
	{
		if (true == isUpdated_UART)
		{
			my_data = UART_Read();

			if (48 == my_data)
			{
				GPIO_OUT_setVal(GPIOAEN, 6, 0);
				GPIO_OUT_setVal(GPIOAEN, 7, 1);
			}
			else if (49 == my_data)
			{
				GPIO_OUT_setVal(GPIOAEN, 6, 1);
				GPIO_OUT_setVal(GPIOAEN, 7, 0);
			}
			else
			{
				GPIO_OUT_setVal(GPIOAEN, 6, 0);
				GPIO_OUT_setVal(GPIOAEN, 7, 0);
			}

			UART_transmit(USART1, &(const uint8_t*)my_data, 1);
		}
	}

    return 0;
}
