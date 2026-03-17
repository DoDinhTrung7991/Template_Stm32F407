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
	DMA_t *DMA_reg_tx = NULL;
	DMA_t *DMA_reg_rx = NULL;
	uint8_t DMA_Stream_tx = 0;
	uint8_t DMA_Stream_rx = 0;
	uint32_t DMA_Channel_tx = 0;
	uint32_t DMA_Channel_rx = 0;

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

				break;
			
			case USART2:
				GPIO_setup(GPIOAEN, 2, AF, AF7, PP, NoP);	// TX
				GPIO_setup(GPIOAEN, 3, AF, AF7, PP, NoP);	// RX

				// GPIO_setup(GPIODEN, 5, AF, AF7, PP, NoP);	// TX
				// GPIO_setup(GPIODEN, 6, AF, AF7, PP, NoP);	// RX

				// Enable clock for USART peripheral
				SET_BIT(RCC_reg->APB1ENR, 17U);

				break;

			case USART3:
				GPIO_setup(GPIOBEN, 10, AF, AF7, PP, NoP);	// TX
				GPIO_setup(GPIOBEN, 11, AF, AF7, PP, NoP);	// RX

				// GPIO_setup(GPIOCEN, 10, AF, AF7, PP, NoP);	// TX
				// GPIO_setup(GPIOCEN, 11, AF, AF7, PP, NoP);	// RX

				// Enable clock for USART peripheral
				SET_BIT(RCC_reg->APB1ENR, 18U);

				break;
			
			case UART4:
				GPIO_setup(GPIOAEN, 0, AF, AF8, PP, NoP);	// TX
				GPIO_setup(GPIOAEN, 1, AF, AF8, PP, NoP);	// RX

				// GPIO_setup(GPIOCEN, 10, AF, AF7, PP, NoP);	// TX
				// GPIO_setup(GPIOCEN, 11, AF, AF7, PP, NoP);	// RX

				// Enable clock for UART peripheral
				SET_BIT(RCC_reg->APB1ENR, 19U);

				break;
			
			case UART5:
				GPIO_setup(GPIOCEN, 12, AF, AF8, PP, NoP);	// TX
				GPIO_setup(GPIODEN, 2, AF, AF8, PP, NoP);	// RX

				// Enable clock for UART peripheral
				SET_BIT(RCC_reg->APB1ENR, 20U);

				break;
			
			case USART6:
				GPIO_setup(GPIOCEN, 6, AF, AF8, PP, NoP);	// TX
				GPIO_setup(GPIOCEN, 7, AF, AF8, PP, NoP);	// RX

				// Enable clock for USART peripheral
				SET_BIT(RCC_reg->APB2ENR, 5U);

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

	// Start Interrupt settings
	// Parity error interrupt enable
	CLEAR_BIT(USART_reg[UARTx]->CR1, 8U); // Disabled as it's not handled
	// Enable/Disable Error interrupt
	SET_BIT(USART_reg[UARTx]->CR3, 0U);
	// IDLE interrupt enable
	CLEAR_BIT(USART_reg[UARTx]->CR1, 4U);
	// TXE interrupt enable
	CLEAR_BIT(USART_reg[UARTx]->CR1, 7U);
	// TC interrupt enable
	CLEAR_BIT(USART_reg[UARTx]->CR1, 6U);
	// RXNE interrupt enable
	SET_BIT(USART_reg[UARTx]->CR1, 5U);
	
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
			DMA_reg_tx = DMA2_reg;
			DMA_reg_rx = DMA2_reg;
			DMA_Stream_tx = 7;
			DMA_Stream_rx = 5;
			DMA_Channel_tx = 4;
			DMA_Channel_rx = 4;
			// Enable Clock for DMA2
			SET_BIT(RCC_reg->AHB1ENR, 22U);
			// Enable DMA Interrupt for Tx
			NVIC_ISER_setVal(DMA2_Stream7);
			// Enable DMA Interrupt for Rx
			NVIC_ISER_setVal(DMA2_Stream5);
			
			break;

		default:
			return NOT_OK;

			break;
	}

	if ((8 < DMA_Stream_tx) || (8 < DMA_Stream_rx) || (8 < DMA_Channel_tx) || (8 < DMA_Channel_rx)){
		return NOT_OK;
	}
	
	// Start setting DMA for Tx
	// Reset DMA
	DMA_reg_tx->S[DMA_Stream_tx].CR = 0UL;
	while (READ_REG(DMA_reg_tx->S[DMA_Stream_tx].CR, 1UL, 0U));
	// DMA stream x peripheral address register
	DMA_reg_tx->S[DMA_Stream_tx].PAR = (uint32_t)&USART_reg[UARTx]->DR;
	// Channel selection
	WRITE_REG(DMA_reg_tx->S[DMA_Stream_tx].CR, 7UL, 25U, DMA_Channel_tx);
	// Memory data size
	WRITE_REG(DMA_reg_tx->S[DMA_Stream_tx].CR, 3UL, 13U, 1UL);
	// Peripheral data size
	WRITE_REG(DMA_reg_tx->S[DMA_Stream_tx].CR, 3UL, 11U, 1UL);
	// Memory increment mode
	SET_BIT(DMA_reg_tx->S[DMA_Stream_tx].CR, 10U);
	// Peripheral increment mode
	CLEAR_BIT(DMA_reg_tx->S[DMA_Stream_tx].CR, 9U);
	// Circular mode
	CLEAR_BIT(DMA_reg_tx->S[DMA_Stream_tx].CR, 8U);
	// Data transfer direction
	WRITE_REG(DMA_reg_tx->S[DMA_Stream_tx].CR, 3UL, 6U, 1UL);
	// Peripheral flow controller
	CLEAR_BIT(DMA_reg_tx->S[DMA_Stream_tx].CR, 5U);
	// Transfer complete interrupt enable
	SET_BIT(DMA_reg_tx->S[DMA_Stream_tx].CR, 4U);
	// Transfer error interrupt enable
	CLEAR_BIT(DMA_reg_tx->S[DMA_Stream_tx].CR, 2U);
	// Direct mode error interrupt enable
	CLEAR_BIT(DMA_reg_tx->S[DMA_Stream_tx].CR, 1U);
	// End setting DMA for Tx

	// Start setting DMA for Rx
	// Reset DMA
	DMA_reg_rx->S[DMA_Stream_rx].CR = 0UL;
	while (READ_REG(DMA_reg_rx->S[DMA_Stream_rx].CR, 1UL, 0U));
	// DMA stream x number of data register
	WRITE_REG(DMA_reg_rx->S[DMA_Stream_rx].NDTR, 0xFFFFUL, 0U, 1UL);
	// DMA stream x peripheral address register
	DMA_reg_rx->S[DMA_Stream_rx].PAR = (uint32_t)&USART_reg[UARTx]->DR;
	// DMA stream x memory 0 address register
	DMA_reg_rx->S[DMA_Stream_rx].M0AR = (uint32_t)UART_recv_buf[UARTx];
	// Channel selection
	WRITE_REG(DMA_reg_rx->S[DMA_Stream_rx].CR, 7UL, 25U, DMA_Channel_rx);
	// Memory data size
	WRITE_REG(DMA_reg_rx->S[DMA_Stream_rx].CR, 3UL, 13U, 1UL);
	// Peripheral data size
	WRITE_REG(DMA_reg_rx->S[DMA_Stream_rx].CR, 3UL, 11U, 1UL);
	// Memory increment mode
	CLEAR_BIT(DMA_reg_rx->S[DMA_Stream_rx].CR, 10U);
	// Peripheral increment mode
	CLEAR_BIT(DMA_reg_rx->S[DMA_Stream_rx].CR, 9U);
	// Circular mode
	CLEAR_BIT(DMA_reg_rx->S[DMA_Stream_rx].CR, 8U);
	// Data transfer direction
	WRITE_REG(DMA_reg_rx->S[DMA_Stream_rx].CR, 3UL, 6U, 0UL);
	// Peripheral flow controller
	CLEAR_BIT(DMA_reg_rx->S[DMA_Stream_rx].CR, 5U);
	// Transfer complete interrupt enable
	SET_BIT(DMA_reg_rx->S[DMA_Stream_rx].CR, 4U);
	// Transfer error interrupt enable
	CLEAR_BIT(DMA_reg_rx->S[DMA_Stream_rx].CR, 2U);
	// Direct mode error interrupt enable
	CLEAR_BIT(DMA_reg_rx->S[DMA_Stream_rx].CR, 1U);
	//Enable Stream
	SET_BIT(DMA_reg_rx->S[DMA_Stream_rx].CR, 0U);
	// End setting DMA for Rx

	// End DMA settings

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
		DMA_t *DMA_reg_tx = NULL;
		uint8_t DMA_Stream_tx = 0;

		switch (UARTx)
		{
			case USART1:
				DMA_reg_tx = DMA2_reg;
				DMA_Stream_tx = 7;

				break;

			default:
				return NOT_OK;

				break;
		}
		
		UART_state_tx[UARTx] = UART_STATE_BUSY;
		// Disable DMA Stream
		CLEAR_BIT(DMA_reg_tx->S[DMA_Stream_tx].CR, 0U);
		while (READ_REG(DMA_reg_tx->S[DMA_Stream_tx].CR, 1UL, 0U));
		DMA_reg_tx->S[DMA_Stream_tx].NDTR = data_length;
		DMA_reg_tx->S[DMA_Stream_tx].M0AR = (uint32_t)buf;
		// Enable DMA Stream
		SET_BIT(DMA_reg_tx->S[DMA_Stream_tx].CR, 0U);
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
