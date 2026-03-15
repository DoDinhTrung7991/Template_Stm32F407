#include "RCC_header.h"
#include "bit_operator.h"
#include "UART.h"
#include "GPIO.h"
#include "Interrupt.h"

DMA_t *DMA1_reg = (DMA_t*)0x40026000;
DMA_t *DMA2_reg = (DMA_t*)0x40026400;

USART_t *USART_reg[6] = {
	(USART_t*)0x40011000,
	(USART_t*)0x40004400,
	(USART_t*)0x40004800,
	(USART_t*)0x40004C00,
	(USART_t*)0x40005000,
	(USART_t*)0x40011400
};
__attribute__((section(".ccmram_data")))volatile uint16_t UART_recv_buf[6][1] = {
	{0},
	{0},
	{0},
	{0},
	{0},
	{0}
};
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
	UART_init_state[UARTx] = NOT_INITTED;

	if ((UART_STATE_BUSY == UART_state_tx[UARTx]) || (UART_STATE_BUSY == UART_state_rx[UARTx]))
	{
		return NOT_OK;
	}
	else
	{
		// Setup GPIO for USART ports
		switch (UARTx)
		{
			case USART1:
				GPIO_OUT_setup(GPIOAEN, 9, AF, AF7, PP, NoP);	// TX
				GPIO_OUT_setup(GPIOAEN, 10, AF, AF7, PP, NoP);	// RX

				// GPIO_OUT_setup(GPIOBEN, 6, AF, AF7, PP, NoP);	// TX
				// GPIO_OUT_setup(GPIOBEN, 7, AF, AF7, PP, NoP);	// RX

				// Enable clock for USART peripheral
				SET_BIT(RCC_reg->APB2ENR, 4U);

				break;
			
			case USART2:
				GPIO_OUT_setup(GPIOAEN, 2, AF, AF7, PP, NoP);	// TX
				GPIO_OUT_setup(GPIOAEN, 3, AF, AF7, PP, NoP);	// RX

				// GPIO_OUT_setup(GPIODEN, 5, AF, AF7, PP, NoP);	// TX
				// GPIO_OUT_setup(GPIODEN, 6, AF, AF7, PP, NoP);	// RX

				// Enable clock for USART peripheral
				SET_BIT(RCC_reg->APB1ENR, 17U);

				break;

			case USART3:
				GPIO_OUT_setup(GPIOBEN, 10, AF, AF7, PP, NoP);	// TX
				GPIO_OUT_setup(GPIOBEN, 11, AF, AF7, PP, NoP);	// RX

				// GPIO_OUT_setup(GPIOCEN, 10, AF, AF7, PP, NoP);	// TX
				// GPIO_OUT_setup(GPIOCEN, 11, AF, AF7, PP, NoP);	// RX

				// Enable clock for USART peripheral
				SET_BIT(RCC_reg->APB1ENR, 18U);

				break;
			
			case UART4:
				GPIO_OUT_setup(GPIOAEN, 0, AF, AF8, PP, NoP);	// TX
				GPIO_OUT_setup(GPIOAEN, 1, AF, AF8, PP, NoP);	// RX

				// GPIO_OUT_setup(GPIOCEN, 10, AF, AF7, PP, NoP);	// TX
				// GPIO_OUT_setup(GPIOCEN, 11, AF, AF7, PP, NoP);	// RX

				// Enable clock for UART peripheral
				SET_BIT(RCC_reg->APB1ENR, 19U);

				break;
			
			case UART5:
				GPIO_OUT_setup(GPIOCEN, 12, AF, AF8, PP, NoP);	// TX
				GPIO_OUT_setup(GPIODEN, 2, AF, AF8, PP, NoP);	// RX

				// Enable clock for UART peripheral
				SET_BIT(RCC_reg->APB1ENR, 20U);

				break;
			
			case USART6:
				GPIO_OUT_setup(GPIOCEN, 6, AF, AF8, PP, NoP);	// TX
				GPIO_OUT_setup(GPIOCEN, 7, AF, AF8, PP, NoP);	// RX

				// Enable clock for USART peripheral
				SET_BIT(RCC_reg->APB2ENR, 5U);

				break;
			
			default:
				return NOT_OK;

				break;
		}
	}
	
	// Disable USART
	WRITE_REG(USART_reg[UARTx]->CR1, 1UL, 13U, 0UL);
	// Setting Data layout
	WRITE_REG(USART_reg[UARTx]->CR1, 1UL, 12U, 0UL);
	// Setting Stop bits
	WRITE_REG(USART_reg[UARTx]->CR2, 3UL, 12U, 0UL);
	// Setting DMA transmitter
	WRITE_REG(USART_reg[UARTx]->CR3, 1UL, 7U, 1UL);
	// Setting DMA receiver
	WRITE_REG(USART_reg[UARTx]->CR3, 1UL, 6U, 1UL);
	// Choose oversampling
	WRITE_REG(USART_reg[UARTx]->CR1, 1UL, 15U, 0UL);
	// Calculate Baudrate
	uint32_t fck = 0;

	if ((USART1 == UARTx) || (USART6 == UARTx)) {
		fck = APB2_freq;
	}
	else if ((USART2 == UARTx) || (USART3 == UARTx) || (UART4 == UARTx) || (UART5 == UARTx)) {
		fck = APB1_freq;
	}
	else {
		return NOT_OK;
	}

	uint32_t div_mantissa = fck / (8 * (2 - READ_REG(USART_reg[UARTx]->CR1, 1UL, 15U)) * baudrate);
	uint32_t div_fraction_times_100 = ((fck * 100) / (8 * (2 - READ_REG(USART_reg[UARTx]->CR1, 1UL, 15U)) * baudrate)) % 100;
	uint32_t div_fraction = (div_fraction_times_100 * 16 + 50) / 100; // Multiply by 16 and round
	uint32_t brr_val = (div_mantissa << 4) | (div_fraction & 0xFU);
	// Setting Baudrate
	WRITE_REG(USART_reg[UARTx]->BRR, 0xFFFFUL, 0U, brr_val);
	// Enable/Disable Parity control
	WRITE_REG(USART_reg[UARTx]->CR1, 1UL, 10U, 0UL);
	// CTS enable
	WRITE_REG(USART_reg[UARTx]->CR3, 1UL, 9U, 0UL);
	// RTS enable
	WRITE_REG(USART_reg[UARTx]->CR3, 1UL, 8U, 0UL);
	// Setting clock from CK pin for Synchronize mode
	WRITE_REG(USART_reg[UARTx]->CR2, 1UL, 11U, 0UL);
	// Half-duplex selection
	WRITE_REG(USART_reg[UARTx]->CR3, 1UL, 3U, 0UL);
	// LIN mode enable
	WRITE_REG(USART_reg[UARTx]->CR2, 1UL, 14U, 0UL);
	// Smartcard mode enable
	WRITE_REG(USART_reg[UARTx]->CR3, 1UL, 5U, 0UL);
	// IrDA mode enable
	WRITE_REG(USART_reg[UARTx]->CR3, 1UL, 1U, 0UL);

	// Start Interrupt settings
	// Parity error interrupt enable
	WRITE_REG(USART_reg[UARTx]->CR1, 1UL, 8U, 0UL); // Disabled as it's not handled
	// Enable/Disable Error interrupt
	WRITE_REG(USART_reg[UARTx]->CR3, 1UL, 0U, 1UL);
	// TXE interrupt enable
	WRITE_REG(USART_reg[UARTx]->CR1, 1UL, 7U, 0UL);
	// TC interrupt enable
	WRITE_REG(USART_reg[UARTx]->CR1, 1UL, 6U, 0UL);
	// RXNE interrupt enable
	WRITE_REG(USART_reg[UARTx]->CR1, 1UL, 5U, 0UL);
	
	switch (UARTx)
	{
		case USART1:
			NVIC_ISER_setVal(USART1_Interrupt);
			break;
		
		case USART2:
			NVIC_ISER_setVal(USART2_Interrupt);
			break;

		case USART3:
			NVIC_ISER_setVal(USART3_Interrupt);
			break;
		
		case UART4:
			NVIC_ISER_setVal(UART4_Interrupt);
			break;
		
		case UART5:
			NVIC_ISER_setVal(UART5_Interrupt);
			break;
		
		case USART6:
			NVIC_ISER_setVal(USART6_Interrupt);
			break;
		
		default:
			break;
	}

	// End Interrupt settings

	// Start DMA settings
	switch (UARTx) {
		case USART1:
			// Enable Clock for DMA2
			SET_BIT(RCC_reg->AHB1ENR, 22U);
			// Start setting DMA for Tx
			// Reset DMA
			DMA2_reg->S[7].CR = 0UL;
			while (READ_REG(DMA2_reg->S[7].CR, 1UL, 0U));
			// DMA stream x peripheral address register
			DMA2_reg->S[7].PAR = (uint32_t)&USART_reg[UARTx]->DR;
			// Channel selection
			WRITE_REG(DMA2_reg->S[7].CR, 7UL, 25U, 4UL);
			// Memory data size
			WRITE_REG(DMA2_reg->S[7].CR, 3UL, 13U, 1UL);
			// Peripheral data size
			WRITE_REG(DMA2_reg->S[7].CR, 3UL, 11U, 1UL);
			// Memory increment mode
			WRITE_REG(DMA2_reg->S[7].CR, 1UL, 10U, 1UL);
			// Peripheral increment mode
			WRITE_REG(DMA2_reg->S[7].CR, 1UL, 9U, 0UL);
			// Circular mode
			WRITE_REG(DMA2_reg->S[7].CR, 1UL, 8U, 0UL);
			// Data transfer direction
			WRITE_REG(DMA2_reg->S[7].CR, 3UL, 6U, 1UL);
			// Peripheral flow controller
			WRITE_REG(DMA2_reg->S[7].CR, 1UL, 5U, 0UL);
			// Transfer complete interrupt enable
			WRITE_REG(DMA2_reg->S[7].CR, 1UL, 4U, 1UL);
			// Transfer error interrupt enable
			WRITE_REG(DMA2_reg->S[7].CR, 1UL, 2U, 0UL);
			// Direct mode error interrupt enable
			WRITE_REG(DMA2_reg->S[7].CR, 1UL, 1U, 0UL);
			// Enable DMA Interrupt
			NVIC_ISER_setVal(DMA2_Stream7);
			// End setting DMA for Tx
			// Start setting DMA for Rx
			// Reset DMA
			DMA2_reg->S[5].CR = 0UL;
			while (READ_REG(DMA2_reg->S[5].CR, 1UL, 0U));
			// DMA stream x number of data register
			WRITE_REG(DMA2_reg->S[5].NDTR, 0xFFFFUL, 0U, 1UL);
			// DMA stream x peripheral address register
			DMA2_reg->S[5].PAR = (uint32_t)&USART_reg[UARTx]->DR;
			// DMA stream x memory 0 address register
			DMA2_reg->S[5].M0AR = (uint32_t)UART_recv_buf[UARTx];
			// Channel selection
			WRITE_REG(DMA2_reg->S[5].CR, 7UL, 25U, 4UL);
			// Memory data size
			WRITE_REG(DMA2_reg->S[5].CR, 3UL, 13U, 1UL);
			// Peripheral data size
			WRITE_REG(DMA2_reg->S[5].CR, 3UL, 11U, 1UL);
			// Memory increment mode
			WRITE_REG(DMA2_reg->S[5].CR, 1UL, 10U, 0UL);
			// Peripheral increment mode
			WRITE_REG(DMA2_reg->S[5].CR, 1UL, 9U, 0UL);
			// Circular mode
			WRITE_REG(DMA2_reg->S[5].CR, 1UL, 8U, 0UL);
			// Data transfer direction
			WRITE_REG(DMA2_reg->S[5].CR, 3UL, 6U, 0UL);
			// Peripheral flow controller
			WRITE_REG(DMA2_reg->S[5].CR, 1UL, 5U, 0UL);
			// Transfer complete interrupt enable
			WRITE_REG(DMA2_reg->S[5].CR, 1UL, 4U, 1UL);
			// Transfer error interrupt enable
			WRITE_REG(DMA2_reg->S[5].CR, 1UL, 2U, 0UL);
			// Direct mode error interrupt enable
			WRITE_REG(DMA2_reg->S[5].CR, 1UL, 1U, 0UL);
			// Enable DMA Interrupt
			NVIC_ISER_setVal(DMA2_Stream5);
			//Enable Stream
			WRITE_REG(DMA2_reg->S[5].CR, 1UL, 0U, 1UL);
			// End setting DMA for Rx

			break;

		default:
			return NOT_OK;

			break;
	}
	
	// End DMA settings

	// Enable USART
	WRITE_REG(USART_reg[UARTx]->CR1, 1UL, 13U, 1UL);
	// Enable Transmitter
	WRITE_REG(USART_reg[UARTx]->CR1, 1UL, 3U, 1UL);
	// Enable/Disable Receiver
	WRITE_REG(USART_reg[UARTx]->CR1, 1UL, 2U, 1UL);
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
		// Disable DMA Stream
		switch (UARTx) {
			case USART1:
				CLEAR_BIT(DMA2_reg->S[7].CR, 0U);
				while (READ_REG(DMA2_reg->S[7].CR, 1UL, 0U));

				break;

			default:
				return NOT_OK;

				break;
		}
		
		UART_state_tx[UARTx] = UART_STATE_BUSY;
		DMA2_reg->S[7].NDTR = data_length;
		DMA2_reg->S[7].M0AR = (uint32_t)buf;

		// Disable DMA Stream
		switch (UARTx) {
			case USART1:
				SET_BIT(DMA2_reg->S[7].CR, 0U);
				
				break;

			default:
				return NOT_OK;

				break;
		}
	}

	return OK;
}

bool UART_receive(UARTx_t UARTx, volatile uint16_t* buf)
{
	if ((NOT_INITTED == UART_init_state[UARTx]) || (UART_STATE_BUSY == UART_state_rx[UARTx] || (NULL == buf) || (USART1 > UARTx) || (USART6 < UARTx)))
	{
		return NOT_OK;
	}
	else
	{
		if (READ_REG(USART_reg[UARTx]->CR1, 1UL, 12U) && (!READ_REG(USART_reg[UARTx]->CR1, 1UL, 10U)))
		{
			buf[0] = READ_REG(USART_reg[UARTx]->DR, 0x1FFUL, 0U);
		}
		else if ((!READ_REG(USART_reg[UARTx]->CR1, 1UL, 12U)) && (READ_REG(USART_reg[UARTx]->CR1, 1UL, 10U)))
		{
			buf[0] = READ_REG(USART_reg[UARTx]->DR, 0x7FUL, 0U);
		}
		else
		{
			buf[0] = READ_REG(USART_reg[UARTx]->DR, 0xFFUL, 0U);
		}

		isUpdated_UART[UARTx] = true;
	}

	return OK;
}

int UART_Read(UARTx_t UARTx) // Returns received data, or -1 if no new data is available.
{
	int data = 0;

	switch (UARTx)
	{
		case USART1:
			NVIC_ICER_setVal(USART1_Interrupt);
			break;
		
		case USART2:
			NVIC_ICER_setVal(USART2_Interrupt);
			break;
			
		case USART3:
			NVIC_ICER_setVal(USART3_Interrupt);
			break;
		
		case UART4:
			NVIC_ICER_setVal(UART4_Interrupt);
			break;
		
		case UART5:
			NVIC_ICER_setVal(UART5_Interrupt);
			break;
		
		case USART6:
			NVIC_ICER_setVal(USART6_Interrupt);
			break;
		
		default:
			break;
	}

	data = (int)UART_recv_buf[UARTx][0];
	isUpdated_UART[UARTx] = false;

	switch (UARTx)
	{
		case USART1:
			NVIC_ISER_setVal(USART1_Interrupt);
			break;
		
		case USART2:
			NVIC_ISER_setVal(USART2_Interrupt);
			break;
			
		case USART3:
			NVIC_ISER_setVal(USART3_Interrupt);
			break;
		
		case UART4:
			NVIC_ISER_setVal(UART4_Interrupt);
			break;
		
		case UART5:
			NVIC_ISER_setVal(UART5_Interrupt);
			break;
		
		case USART6:
			NVIC_ISER_setVal(USART6_Interrupt);
			break;
		
		default:
			break;
	}

	return data;
}
