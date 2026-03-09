#include "RCC_header.h"
#include "bit_operator.h"
#include "UART.h"
#include "GPIO.h"
#include "Interrupt.h"

USART_t *USART1_reg = (USART_t*)0x40011000;
bool UART_init_state = NOT_INITTED;
bool UART_state = UART_STATE_READY;
bool isUpdated_UART = false;

bool UART_init(UARTx_t UARTx, uint32_t baudrate)
{
	switch (UARTx)
	{
		case USART1:
			if (UART_STATE_READY == UART_state)
			{
				UART_init_state = NOT_INITTED;
				// Enable clock for USART1 peripheral
				WRITE_REG(RCC_reg->APB2ENR, 1UL, 4U, 1UL);
				// Disable USART
				WRITE_REG(USART1_reg->CR1, 1UL, 13U, 0UL);
				// Setting Data layout
				WRITE_REG(USART1_reg->CR1, 1UL, 12U, 0UL);
				// Setting Stop bits
				WRITE_REG(USART1_reg->CR2, 3UL, 12U, 0UL);
				// Setting DMA transmitter
				WRITE_REG(USART1_reg->CR3, 1UL, 7U, 0UL);
				// Setting DMA receiver
				WRITE_REG(USART1_reg->CR3, 1UL, 6U, 0UL);
				// Choose oversampling
				WRITE_REG(USART1_reg->CR1, 1UL, 15U, 0UL);
				// Setting Baud rate
				uint32_t fck = APB2_freq;
				uint32_t div_mantissa = fck / (8 * (2 - READ_REG(USART1_reg->CR1, 1UL, 15U)) * baudrate);
				uint32_t div_fraction_times_100 = ((fck * 100) / (8 * (2 - READ_REG(USART1_reg->CR1, 1UL, 15U)) * baudrate)) % 100;
				uint32_t div_fraction = (div_fraction_times_100 * 16 + 50) / 100; // Multiply by 16 and round
				uint32_t brr_val = (div_mantissa << 4) | (div_fraction & 0xFU);
				WRITE_REG(USART1_reg->BRR, 0xFFFFUL, 0U, brr_val);
				// Enable/Disable Parity control
				WRITE_REG(USART1_reg->CR1, 1UL, 10U, 0UL);
				// CTS enable
				WRITE_REG(USART1_reg->CR3, 1UL, 9U, 0UL);
				// RTS enable
				WRITE_REG(USART1_reg->CR3, 1UL, 8U, 0UL);
				// Setting clock from CK pin for Synchronize mode
				WRITE_REG(USART1_reg->CR2, 1UL, 11U, 0UL);
				// Half-duplex selection
				WRITE_REG(USART1_reg->CR3, 1UL, 3U, 0UL);
				// LIN mode enable
				WRITE_REG(USART1_reg->CR2, 1UL, 14U, 0UL);
				// Smartcard mode enable
				WRITE_REG(USART1_reg->CR3, 1UL, 5U, 0UL);
				// IrDA mode enable
				WRITE_REG(USART1_reg->CR3, 1UL, 1U, 0UL);
				// Parity error interrupt enable
				WRITE_REG(USART1_reg->CR1, 1UL, 8U, 0UL); // Disabled as it's not handled
				// Enable/Disable Error interrupt
				WRITE_REG(USART1_reg->CR3, 1UL, 0U, 0UL);
				// Enable Transmitter
				WRITE_REG(USART1_reg->CR1, 1UL, 3U, 1UL);
				// TXE interrupt enable
				WRITE_REG(USART1_reg->CR1, 1UL, 7U, 0UL);
				// Enable/Disable Receiver
				WRITE_REG(USART1_reg->CR1, 1UL, 2U, 1UL);
				// RXNE interrupt enable
				WRITE_REG(USART1_reg->CR1, 1UL, 5U, 1UL);

				if (1UL == READ_REG(USART1_reg->CR1, 1UL, 5U))
				{
					NVIC_ISER_setVal(USART1_Interrupt);
				}

				// Setup GPIO for USART ports
				GPIO_OUT_setup(GPIOAEN, 9, AF, AF7, PP, NoP);	// TX
				GPIO_OUT_setup(GPIOAEN, 10, AF, AF7, PP, NoP);	// RX
				// Clear receive buffer
				UART_recv_buf[0] = 0;
				UART_recv_buf[1] = 0;
				// Clear isUpdated flag
				isUpdated_UART = false;
				// Enable USART
				WRITE_REG(USART1_reg->CR1, 1UL, 13U, 1UL);
				UART_init_state = INITTED;
			}
			else
			{
				UART_init_state = NOT_INITTED;
				return NOT_OK;
			}

			break;

		default:
			return NOT_OK;

			break;
	}

	return OK;
}

bool UART_transmit(UARTx_t UARTx, const uint8_t* buf, uint8_t data_length)
{
	uint8_t* pdata_8bit = NULL;
	uint16_t* pdata_16bit = NULL;
	
	switch (UARTx)
	{
		case USART1:
			if ((NOT_INITTED == UART_init_state) || (NULL == buf) || (0 == data_length))
			{
				return NOT_OK;
			}
			else
			{
				UART_state = UART_STATE_BUSY;

				if (READ_REG(USART1_reg->CR1, 1UL, 12U) && (!READ_REG(USART1_reg->CR1, 1UL, 10U)))
				{
					pdata_16bit = (uint16_t *)buf;
					pdata_8bit = NULL;
				}
				else
				{
					pdata_8bit = (uint8_t *)buf;
					pdata_16bit = NULL;
				}
	
				while (data_length > 0)
				{
					// Waits until TXE=1
					while (!READ_REG(USART1_reg->SR, 1UL, 7U));

					if (NULL == pdata_8bit)
					{
						USART1_reg->DR = (uint16_t)(*pdata_16bit & 0x1FFU);
						pdata_16bit ++;
					}
					else
					{
						USART1_reg->DR = (uint8_t)(*pdata_8bit & 0xFFU);
						pdata_8bit ++;
					}
					
					data_length --;
				}

				// Waits until TC=1
				while (!READ_REG(USART1_reg->SR, 1UL, 6U));
				UART_state = UART_STATE_READY;
			}
			
			break;
		
		default:
			return NOT_OK;

			break;
	}

	return OK;
}

bool UART_receive(UARTx_t UARTx, volatile uint8_t* buf)
{
	switch (UARTx)
	{
		case USART1:
			if (NOT_INITTED == UART_init_state)
			{
				return NOT_OK;
			}
			else
			{
				if (READ_REG(USART1_reg->CR1, 1UL, 12U) && (!READ_REG(USART1_reg->CR1, 1UL, 10U)))
				{
					// Correctly read 9-bit data in a single operation
					uint16_t temp_data = (USART1_reg->DR & 0x1FFU);
					buf[0] = (uint8_t)(temp_data & 0xFFUL);
					buf[1] = (uint8_t)((temp_data >> 8U) & 0x01UL);
				}
				else
				{
					buf[0] = (USART1_reg->DR & 0xFFUL);
				}

				isUpdated_UART = true;
			}

			break;
		
		default:
			return NOT_OK;
			
			break;
	}

	return OK;
}

int UART_Read(void) // Returns received data, or -1 if no new data is available.
{
	int data = -1;

	/*
	 * Create a critical section to prevent a race condition. This ensures that checking
	 * the isUpdated_UART flag and reading from UART_recv_buf is an atomic operation.
	 */
	NVIC_ICER_setVal(USART1_Interrupt);
	if (isUpdated_UART == true)
	{
		data = (int)(UART_recv_buf[0] | (UART_recv_buf[1] << 8));
		isUpdated_UART = false;
	}
	NVIC_ISER_setVal(USART1_Interrupt);

	return data;
}
