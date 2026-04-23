#include "RCC_header.h"
#include "bit_operator.h"
#include "UART.h"
#include "GPIO.h"
#include "Interrupt.h"
#include <string.h>

USART_t *USART_reg[6] = {
	(USART_t*)0x40011000,
	(USART_t*)0x40004400,
	(USART_t*)0x40004800,
	(USART_t*)0x40004C00,
	(USART_t*)0x40005000,
	(USART_t*)0x40011400
};
volatile queue_t UART_recv_buf[6];
__attribute__((section(".ccmram_data")))volatile uint8_t isUpdated_UART[6] = {
	false,
	false,
	false,
	false,
	false,
	false
};
__attribute__((section(".ccmram_data")))volatile bool UART_init_state[6] = {
	NOT_INITTED,
	NOT_INITTED,
	NOT_INITTED,
	NOT_INITTED,
	NOT_INITTED,
	NOT_INITTED
};
__attribute__((section(".ccmram_data")))volatile bool UART_state_tx[6] = {
	UART_STATE_READY,
	UART_STATE_READY,
	UART_STATE_READY,
	UART_STATE_READY,
	UART_STATE_READY,
	UART_STATE_READY
};
__attribute__((section(".ccmram_data")))volatile bool UART_state_rx[6] = {
	UART_STATE_READY,
	UART_STATE_READY,
	UART_STATE_READY,
	UART_STATE_READY,
	UART_STATE_READY,
	UART_STATE_READY
};

bool UART_init(UARTx_t UARTx, uint32_t baudrate)
{
    DMA_direct_param_t DMA_direct_param_tx_st = (DMA_direct_param_t)
	{
		{
			.DMAx = 0,
			.stream = 0,
			.channel = 0
		},
		{
			.double_buffer_en = disable,
			.peri_data_size = half_word,
			.mem_data_size = half_word,
			.peri_mode = fixed,
			.mem_mode = not_fixed
		},
		{
			.dir = mem_to_peri,
			.flow_controller = DMA
		},
		{
			.stream_priority = low,
			.interrupt_en_u8 = (TCIE | DMEIE)
		}
	};

    DMA_direct_param_t DMA_direct_param_rx_st = (DMA_direct_param_t)
	{
		{
			.DMAx = 0,
			.stream = 0,
			.channel = 0
		},
		{
			.double_buffer_en = disable,
			.peri_data_size = half_word,
			.mem_data_size = half_word,
			.peri_mode = fixed,
			.mem_mode = circular
		},
		{
			.dir = peri_to_mem,
			.flow_controller = DMA
		},
		{
			.stream_priority = medium,
			.interrupt_en_u8 = (TCIE | DMEIE)
		}
	};

	buffer_t buffer_info_rx_st = (buffer_t)
	{
		.data_length = ARR_SIZE,
		.peri_addr = &USART_reg[UARTx]->DR,
		.mem_addr = (volatile uint8_t *)UART_recv_buf[UARTx].buf
	};

	UART_init_state[UARTx] = NOT_INITTED;

	if ((UART_STATE_BUSY == UART_state_tx[UARTx]) || (UART_STATE_BUSY == UART_state_rx[UARTx]))
	{
		return NOT_OK;
	}
	else
	{
		// Setup Clock and GPIO for USART ports
		switch (UARTx)
		{
			case USART1:
				GPIO_setup(GPIOAEN, 9, AF, AF7, PP, NoP);	// TX
				GPIO_setup(GPIOAEN, 10, AF, AF7, PP, NoP);	// RX

				// GPIO_setup(GPIOBEN, 6, AF, AF7, PP, NoP);	// TX
				// GPIO_setup(GPIOBEN, 7, AF, AF7, PP, NoP);	// RX

				// Enable clock for USART peripheral
				SET_BIT(RCC_reg->APB2ENR, 4U);
				// Enable Interrupt line
				NVIC_ISER_setVal(USART1_Interrupt);

				DMA_direct_param_tx_st.Stream_info_st.DMAx = DMA2;
				DMA_direct_param_tx_st.Stream_info_st.stream = Stream_7;
				DMA_direct_param_tx_st.Stream_info_st.channel = 4;

				DMA_direct_param_rx_st.Stream_info_st.DMAx = DMA2;
				DMA_direct_param_rx_st.Stream_info_st.stream = Stream_5;
				DMA_direct_param_rx_st.Stream_info_st.channel = 4;
				
				break;
			
			case USART2:
				GPIO_setup(GPIOAEN, 2, AF, AF7, PP, NoP);	// TX
				GPIO_setup(GPIOAEN, 3, AF, AF7, PP, NoP);	// RX

				// GPIO_setup(GPIODEN, 5, AF, AF7, PP, NoP);	// TX
				// GPIO_setup(GPIODEN, 6, AF, AF7, PP, NoP);	// RX

				// Enable clock for USART peripheral
				SET_BIT(RCC_reg->APB1ENR, 17U);
				// Enable Interrupt line
				NVIC_ISER_setVal(USART2_Interrupt);

				DMA_direct_param_tx_st.Stream_info_st.DMAx = DMA1;
				DMA_direct_param_tx_st.Stream_info_st.stream = Stream_6;
				DMA_direct_param_tx_st.Stream_info_st.channel = 4;

				DMA_direct_param_rx_st.Stream_info_st.DMAx = DMA1;
				DMA_direct_param_rx_st.Stream_info_st.stream = Stream_5;
				DMA_direct_param_rx_st.Stream_info_st.channel = 4;
				
				break;

			case USART3:
				GPIO_setup(GPIOBEN, 10, AF, AF7, PP, NoP);	// TX
				GPIO_setup(GPIOBEN, 11, AF, AF7, PP, NoP);	// RX

				// GPIO_setup(GPIOCEN, 10, AF, AF7, PP, NoP);	// TX
				// GPIO_setup(GPIOCEN, 11, AF, AF7, PP, NoP);	// RX

				// Enable clock for USART peripheral
				SET_BIT(RCC_reg->APB1ENR, 18U);
				// Enable Interrupt line
				NVIC_ISER_setVal(USART3_Interrupt);

				DMA_direct_param_tx_st.Stream_info_st.DMAx = DMA1;
				DMA_direct_param_tx_st.Stream_info_st.stream = Stream_3;
				DMA_direct_param_tx_st.Stream_info_st.channel = 4;

				DMA_direct_param_rx_st.Stream_info_st.DMAx = DMA1;
				DMA_direct_param_rx_st.Stream_info_st.stream = Stream_1;
				DMA_direct_param_rx_st.Stream_info_st.channel = 4;
				
				break;
			
			case UART4:
				GPIO_setup(GPIOAEN, 0, AF, AF8, PP, NoP);	// TX
				GPIO_setup(GPIOAEN, 1, AF, AF8, PP, NoP);	// RX

				// GPIO_setup(GPIOCEN, 10, AF, AF7, PP, NoP);	// TX
				// GPIO_setup(GPIOCEN, 11, AF, AF7, PP, NoP);	// RX

				// Enable clock for UART peripheral
				SET_BIT(RCC_reg->APB1ENR, 19U);
				// Enable Interrupt line
				NVIC_ISER_setVal(UART4_Interrupt);

				DMA_direct_param_tx_st.Stream_info_st.DMAx = DMA1;
				DMA_direct_param_tx_st.Stream_info_st.stream = Stream_4;
				DMA_direct_param_tx_st.Stream_info_st.channel = 4;

				DMA_direct_param_rx_st.Stream_info_st.DMAx = DMA1;
				DMA_direct_param_rx_st.Stream_info_st.stream = Stream_2;
				DMA_direct_param_rx_st.Stream_info_st.channel = 4;
				
				break;
			
			case UART5:
				GPIO_setup(GPIOCEN, 12, AF, AF8, PP, NoP);	// TX
				GPIO_setup(GPIODEN, 2, AF, AF8, PP, NoP);	// RX

				// Enable clock for UART peripheral
				SET_BIT(RCC_reg->APB1ENR, 20U);
				// Enable Interrupt line
				NVIC_ISER_setVal(UART5_Interrupt);

				DMA_direct_param_tx_st.Stream_info_st.DMAx = DMA1;
				DMA_direct_param_tx_st.Stream_info_st.stream = Stream_7;
				DMA_direct_param_tx_st.Stream_info_st.channel = 4;

				DMA_direct_param_rx_st.Stream_info_st.DMAx = DMA1;
				DMA_direct_param_rx_st.Stream_info_st.stream = Stream_0;
				DMA_direct_param_rx_st.Stream_info_st.channel = 4;
				
				break;
			
			case USART6:
				GPIO_setup(GPIOCEN, 6, AF, AF8, PP, NoP);	// TX
				GPIO_setup(GPIOCEN, 7, AF, AF8, PP, NoP);	// RX

				// Enable clock for USART peripheral
				SET_BIT(RCC_reg->APB2ENR, 5U);
				// Enable Interrupt line
				NVIC_ISER_setVal(USART6_Interrupt);

				DMA_direct_param_tx_st.Stream_info_st.DMAx = DMA2;
				DMA_direct_param_tx_st.Stream_info_st.stream = Stream_7;
				DMA_direct_param_tx_st.Stream_info_st.channel = 5;

				DMA_direct_param_rx_st.Stream_info_st.DMAx = DMA2;
				DMA_direct_param_rx_st.Stream_info_st.stream = Stream_1;
				DMA_direct_param_rx_st.Stream_info_st.channel = 5;
				
				break;
			
			default:
				return NOT_OK;

				break;
		}
	}
	
	// Disable USART
	CLEAR_BIT(USART_reg[UARTx]->CR1, 13U);
	// Setting Data layout
	CLEAR_BIT(USART_reg[UARTx]->CR1, 12U);
	// Setting Stop bits
	WRITE_REG(USART_reg[UARTx]->CR2, 3UL, 12U, 0UL);
	// Setting DMA transmitter
	SET_BIT(USART_reg[UARTx]->CR3, 7U);
	// Setting DMA receiver
	SET_BIT(USART_reg[UARTx]->CR3, 6U);
	// Choose oversampling
	CLEAR_BIT(USART_reg[UARTx]->CR1, 15U);
	// Calculate Baudrate
	uint32_t fck = 0;

	if ((USART1 == UARTx) || (USART6 == UARTx))
	{
		fck = APB2_freq;
	}
	else if ((USART2 == UARTx) || (USART3 == UARTx) || (UART4 == UARTx) || (UART5 == UARTx))
	{
		fck = APB1_freq;
	}
	else
	{
		return NOT_OK;
	}

	uint32_t div_mantissa = fck / (8 * (2 - READ_REG(USART_reg[UARTx]->CR1, 1UL, 15U)) * baudrate);
	uint32_t div_fraction_times_100 = ((fck * 100) / (8 * (2 - READ_REG(USART_reg[UARTx]->CR1, 1UL, 15U)) * baudrate)) % 100;
	uint32_t div_fraction = (div_fraction_times_100 * 16 + 50) / 100; // Multiply by 16 and round
	uint32_t brr_val = (div_mantissa << 4) | (div_fraction & 0xFU);
	// Setting Baudrate
	WRITE_REG(USART_reg[UARTx]->BRR, 0xFFFFUL, 0U, brr_val);
	// Enable/Disable Parity control
	CLEAR_BIT(USART_reg[UARTx]->CR1, 10U);
	// CTS enable
	CLEAR_BIT(USART_reg[UARTx]->CR3, 9U);
	// RTS enable
	CLEAR_BIT(USART_reg[UARTx]->CR3, 8U);
	// Setting clock from CK pin for Synchronize mode
	CLEAR_BIT(USART_reg[UARTx]->CR2, 11U);
	// Half-duplex selection
	CLEAR_BIT(USART_reg[UARTx]->CR3, 3U);
	// LIN mode enable
	CLEAR_BIT(USART_reg[UARTx]->CR2, 14U);
	// Smartcard mode enable
	CLEAR_BIT(USART_reg[UARTx]->CR3, 5U);
	// IrDA mode enable
	CLEAR_BIT(USART_reg[UARTx]->CR3, 1U);
	// Enable/Disable Error interrupt
	SET_BIT(USART_reg[UARTx]->CR3, 0U);
	// Parity error interrupt enable
	CLEAR_BIT(USART_reg[UARTx]->CR1, 8U);
	// IDLE interrupt enable
	SET_BIT(USART_reg[UARTx]->CR1, 4U);
	// TXE interrupt enable
	CLEAR_BIT(USART_reg[UARTx]->CR1, 7U);
	// TC interrupt enable
	CLEAR_BIT(USART_reg[UARTx]->CR1, 6U);
	// RXNE interrupt enable
	CLEAR_BIT(USART_reg[UARTx]->CR1, 5U);
	
	// Setting for DMA
	if ((NOT_OK == DMA_direct_init(DMA_direct_param_tx_st)) || (NOT_OK == DMA_direct_init(DMA_direct_param_rx_st)))
	{
		return NOT_OK;
	}

	DMA_transfer(DMA_direct_param_rx_st.Stream_info_st, buffer_info_rx_st);
	
	// Enable USART
	SET_BIT(USART_reg[UARTx]->CR1, 13U);
	// Enable Transmitter
	SET_BIT(USART_reg[UARTx]->CR1, 3U);
	// Enable/Disable Receiver
	SET_BIT(USART_reg[UARTx]->CR1, 2U);
	UART_init_state[UARTx] = INITTED;

	return OK;
}

bool UART_transmit(UARTx_t UARTx, const uint16_t *buf, uint8_t data_length)
{
	if ((NOT_INITTED == UART_init_state[UARTx]) || (UART_STATE_BUSY == UART_state_tx[UARTx]) || (NULL == buf) || (0 == data_length) || (USART1 > UARTx) || (USART6 < UARTx))
	{
		return NOT_OK;
	}
	else
	{
		stream_channel_t Stream_info_st;

		switch (UARTx)
		{
			case USART1:
				Stream_info_st.DMAx = DMA2;
				Stream_info_st.stream = Stream_7;

				break;

			case USART2:
				Stream_info_st.DMAx = DMA1;
				Stream_info_st.stream = Stream_6;

				break;

			case USART3:
				Stream_info_st.DMAx = DMA1;
				Stream_info_st.stream = Stream_3;

				break;

			case UART4:
				Stream_info_st.DMAx = DMA1;
				Stream_info_st.stream = Stream_4;

				break;

			case UART5:
				Stream_info_st.DMAx = DMA1;
				Stream_info_st.stream = Stream_7;

				break;

			case USART6:
				Stream_info_st.DMAx = DMA2;
				Stream_info_st.stream = Stream_7;

				break;

			default:
				return NOT_OK;

				break;
		}
		
		UART_state_tx[UARTx] = UART_STATE_BUSY;
		DMA_transfer
		(
			Stream_info_st, 
			(buffer_t){
				.data_length = data_length,
				.peri_addr = &USART_reg[UARTx]->DR,
				.mem_addr = (volatile uint8_t *)buf
			}
		);
	}

	return OK;
}

void UART_Read(UARTx_t UARTx, uint16_t *buf, uint8_t data_length)
{
	if (true == UART_recv_buf[UARTx].isEmpty)
	{
		return;
	}
	else
	{
		uint8_t i = 0;
		DMA_t *DMA_reg_rx = NULL;
		uint8_t DMA_Stream_rx = 0;

		switch (UARTx)
		{
			case USART1:
				DMA_reg_rx = DMA_reg[DMA2];
				DMA_Stream_rx = 5;
				// Disable DMA Stream
				CLEAR_BIT(DMA_reg_rx->S[DMA_Stream_rx].CR, 0U);
				while (READ_REG(DMA_reg_rx->S[DMA_Stream_rx].CR, 1UL, 0U));
				// Disable Interrupt
				NVIC_ICER_setVal(USART1_Interrupt);

				break;

			default:
				return;

				break;
		}

		if (data_length > ARR_SIZE)
		{
			data_length = ARR_SIZE;
		}

		if (UART_recv_buf[UARTx].rear >= data_length)
		{
			UART_recv_buf[UARTx].front = UART_recv_buf[UARTx].rear - data_length;
		}
		else
		{
			if (UART_recv_buf[UARTx].overrun)
			{
				UART_recv_buf[UARTx].front = ARR_SIZE - data_length + UART_recv_buf[UARTx].rear;
			}
			else
			{
				UART_recv_buf[UARTx].front = 0;
			}
		}

		while (false == UART_recv_buf[UARTx].isEmpty)
		{
			buf[i++] = UART_recv_buf[UARTx].buf[UART_recv_buf[UARTx].front];
			UART_recv_buf[UARTx].front = (UART_recv_buf[UARTx].front + 1) % ARR_SIZE;

			if (UART_recv_buf[UARTx].front == UART_recv_buf[UARTx].rear)
			{
				UART_recv_buf[UARTx].isEmpty = true;
			}
		}

		UART_recv_buf[UARTx].isFull = false;
		UART_recv_buf[UARTx].overrun = false;
		UART_recv_buf[UARTx].front = 0;
		UART_recv_buf[UARTx].rear = 0;
		isUpdated_UART[UARTx] = false;
	    memset((void*)UART_recv_buf[UARTx].buf, 0, ARR_SIZE * sizeof(*UART_recv_buf[UARTx].buf));

		//Enable Stream
		SET_BIT(DMA_reg_rx->S[DMA_Stream_rx].CR, 0U);
		// Enable Interrupt
		NVIC_ISER_setVal(USART1_Interrupt);
	}
}
