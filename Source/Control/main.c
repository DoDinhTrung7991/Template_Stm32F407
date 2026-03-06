#include "GPIO.h"
#include "UART.h"

int main(void)
{
	uint8_t data_u8 = 48;

	UART_init(USART1, 9600); // Initialize UART with a 9600 baud rate
	GPIO_OUT_setup(GPIOAEN, 6, GP, AF7, PP, PU);
	GPIO_OUT_setup(GPIOAEN, 7, GP, AF7, PP, PU);

	GPIO_OUT_setVal(GPIOAEN, 6, 1);
	GPIO_OUT_setVal(GPIOAEN, 7, 1);

	while (1)
	{
		if (true == isUpdated_UART)
		{
			data_u8 = UART_Read();

			if (48 == data_u8)
			{
				GPIO_OUT_setVal(GPIOAEN, 6, 0);
				GPIO_OUT_setVal(GPIOAEN, 7, 1);
			}
			else if (49 == data_u8)
			{
				GPIO_OUT_setVal(GPIOAEN, 6, 1);
				GPIO_OUT_setVal(GPIOAEN, 7, 0);
			}
			else
			{
				GPIO_OUT_setVal(GPIOAEN, 6, 1);
				GPIO_OUT_setVal(GPIOAEN, 7, 1);
			}

			UART_transmit(USART1, &data_u8, 1);
		}
	}

    return 0;
}
