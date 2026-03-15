#include "GPIO.h"
#include "UART.h"

uint16_t tx_data[3] = {48, 49, 50};

int main(void)
{
	int rx_data = 0;

	UART_init(USART1, 115200); // Initialize UART with a baudrate
	GPIO_OUT_setup(GPIOAEN, 6, GP, AF7, PP, PU);
	GPIO_OUT_setup(GPIOAEN, 7, GP, AF7, PP, PU);

	while (1)
	{	
		UART_transmit(USART1, tx_data, 3);
		
		if (true == isUpdated_UART[USART1])
		{
			rx_data = UART_Read(USART1);

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
				GPIO_OUT_setVal(GPIOAEN, 6, 1);
				GPIO_OUT_setVal(GPIOAEN, 7, 1);
			}
		}
	}

    return 0;
}
