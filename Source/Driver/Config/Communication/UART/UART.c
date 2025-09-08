#include "RCC_header.h"
#include "bit_operator.h"
#include "UART.h"
#include "GPIO.h"
#include "Interrupt.h"

USART_t *USART1_reg = (USART_t*)0x40011000;
bool UART_init_state = NOT_INITTED;
bool UART_state = UART_STATE_READY;
bool isUpdated_UART = false;

bool UART_init(UARTx_t UARTx)
{
	switch (UARTx)
	{
		case USART1:
			if (UART_STATE_READY == UART_state)
			{
				UART_state = UART_STATE_BUSY;
				WRITE_REG(RCC_reg->APB2ENR, 1UL, 4U, 1UL);
				WRITE_REG(USART1_reg->CR1, 1UL, 13U, 0UL);
				WRITE_REG(USART1_reg->CR2, 3UL, 12U, 0UL);
				WRITE_REG(USART1_reg->CR1, 1UL, 12U, 0UL);
				WRITE_REG(USART1_reg->CR1, 1UL, 10U, 0UL);
				WRITE_REG(USART1_reg->CR1, 1UL, 3U, 1UL);
				WRITE_REG(USART1_reg->CR1, 1UL, 2U, 1UL);
				WRITE_REG(USART1_reg->CR1, 1UL, 15U, 0UL);
				WRITE_REG(USART1_reg->CR3, 1UL, 8U, 0UL);
				WRITE_REG(USART1_reg->CR3, 1UL, 9U, 0UL);
				USART1_reg->BRR = (uint16_t)((4UL << 4U) | 5);
				WRITE_REG(USART1_reg->CR2, 1UL, 14U, 0UL);
				WRITE_REG(USART1_reg->CR2, 1UL, 11U, 0UL);
				WRITE_REG(USART1_reg->CR3, 1UL, 5U, 0UL);
				WRITE_REG(USART1_reg->CR3, 1UL, 3U, 0UL);
				WRITE_REG(USART1_reg->CR3, 1UL, 1U, 0UL);
				GPIO_OUT_setup(GPIOAEN, 9, AF, AF7, PP, NoP);
				GPIO_OUT_setup(GPIOAEN, 10, AF, AF7, PP, NoP);
				WRITE_REG(USART1_reg->CR1, 1UL, 5U, 1UL);
				if (1UL == READ_REG(USART1_reg->CR1, 1UL, 5U))
				{
					NVIC_ISER_setVal(USART1_Interrupt);
				}
				
				WRITE_REG(USART1_reg->CR1, 1UL, 8U, 1UL);
				WRITE_REG(USART1_reg->CR1, 1UL, 7U, 0UL);
				WRITE_REG(USART1_reg->CR3, 1UL, 0U, 0UL);
				WRITE_REG(USART1_reg->CR1, 1UL, 13U, 1UL);
				UART_init_state = INITTED;
				UART_state = UART_STATE_READY;

				return OK;
			}
			else
			{
				return NOT_OK;
			}
			break;

		default:
			return NOT_OK;
			break;
	}
}

bool UART_transmit(UARTx_t UARTx, const uint8_t* buf, uint8_t data_length)
{
	const uint8_t* pdata_8bit;
	const uint16_t* pdata_16bit;
	
	switch (UARTx)
	{
		case USART1:
			if ((UART_STATE_BUSY == UART_state) || (NOT_INITTED == UART_init_state) || (NULL == buf) || (0 == data_length))
			{
				return NOT_OK;
			}
			else
			{
				UART_state = UART_STATE_BUSY;
		
				if (READ_REG(USART1_reg->CR1, 1UL, 12U) && (!READ_REG(USART1_reg->CR1, 1UL, 10U)))
				{
					pdata_16bit = (const uint16_t*)buf;
					pdata_8bit = NULL;
				}
				else
				{
					pdata_8bit = buf;
					pdata_16bit = NULL;
				}
	
				while (data_length > 0)
				{
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
					while (!READ_REG(USART1_reg->SR, 1UL, 7U));
					data_length --;
				}
	
				while (!READ_REG(USART1_reg->SR, 1UL, 6U));
				UART_state = UART_STATE_READY;
	
				return OK;
			}
			break;
		
		default:
			return NOT_OK;
			break;
	}
}

bool UART_receive(UARTx_t UARTx, volatile uint8_t* buf)
{	
	switch (UARTx)
	{
		case USART1:
			if ((UART_STATE_BUSY == UART_state) || (NOT_INITTED == UART_init_state))
			{
				return NOT_OK;
			}
			else
			{
				UART_state = UART_STATE_BUSY;
				while ((USART1_reg->SR >> 5U) & 1UL)
				{
					if (READ_REG(USART1_reg->CR1, 1UL, 12U) && (!READ_REG(USART1_reg->CR1, 1UL, 10U)))
					{
						buf[0] = (USART1_reg->DR & 0xFFUL);
						buf[1] = ((USART1_reg->DR >> 8U) & 1UL);
					}
					else
					{
						buf[0] = (USART1_reg->DR & 0xFFUL);
					}
					
					isUpdated_UART = false;
				}
				UART_state = UART_STATE_READY;
				return OK;
			}
			break;
		
		default:
			return NOT_OK;
			break;
	}
}
