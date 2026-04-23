#include "I2C.h"
#include "init_static.h"
#include "bit_operator.h"
#include "RCC_header.h"
#include "Interrupt.h"
#include "GPIO.h"
#include "DMA.h"
#include <string.h>

I2C_t *I2C_reg[3] = 
{
    (I2C_t *)0x40005400,
    (I2C_t *)0x40005800,
    (I2C_t *)0x40005C00
};

volatile bool I2C_init_state[3] =
{
    NOT_INITTED,
    NOT_INITTED,
    NOT_INITTED
};

volatile uint8_t I2C_recv_buf[3][ARR_SIZE] =
{
    {0},
    {0},
    {0}
};

volatile bool I2C_state_tx[3] =
{
    I2C_STATE_READY,
    I2C_STATE_READY,
    I2C_STATE_READY
};

volatile bool I2C_state_rx[3] =
{
    I2C_STATE_READY,
    I2C_STATE_READY,
    I2C_STATE_READY
};

volatile uint8_t isUpdated_I2C[3] =
{
    false,
	false,
	false
};

volatile uint8_t I2C_addr[3];

bool I2C_init(I2Cx_t I2Cx_en)
{
	I2C_init_state[I2Cx_en] = NOT_INITTED;
	static bool is_DMA_Init_done[3] = {false, false, false};

    if ((I2C_STATE_READY == I2C_state_tx[I2Cx_en]) && (I2C_STATE_READY == I2C_state_rx[I2Cx_en]))
    {
		if (false == is_DMA_Init_done[I2Cx_en])
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
					.peri_data_size = byte,
					.mem_data_size = byte,
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
					.peri_data_size = byte,
					.mem_data_size = byte,
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

        	switch (I2Cx_en)
        	{
        	    case I2C1:
        	        // Enable I2C clock
        	        SET_BIT(RCC_reg->APB1ENR, 21U);
        	        // Setup GPIO for I2C
        	        GPIO_setup(GPIOBEN, 8, AF, AF4, OD, PU);	// SCL
	    			GPIO_setup(GPIOBEN, 9, AF, AF4, OD, PU);	// SDA
        	        /*
        	        GPIO_setup(GPIOBEN, 6, AF, AF4, OD, PU);	// SCL
	    			GPIO_setup(GPIOBEN, 7, AF, AF4, OD, PU);	// SDA
        	        */
        	        // Enable ISR for I2C
        	        NVIC_ISER_setVal(I2C1_EV);
        	        NVIC_ISER_setVal(I2C1_ER);

					DMA_direct_param_tx_st.Stream_info_st.DMAx = DMA1;
					DMA_direct_param_tx_st.Stream_info_st.stream = Stream_7;
					DMA_direct_param_tx_st.Stream_info_st.channel = 1;

					DMA_direct_param_rx_st.Stream_info_st.DMAx = DMA1;
					DMA_direct_param_rx_st.Stream_info_st.stream = Stream_5;
					DMA_direct_param_rx_st.Stream_info_st.channel = 1;

        	        break;

        	    case I2C2:
        	        // Enable I2C clock
        	        SET_BIT(RCC_reg->APB1ENR, 22U);
        	        // Setup GPIO for I2C
        	        GPIO_setup(GPIOBEN, 10, AF, AF4, OD, PU);	// SCL
	    			GPIO_setup(GPIOBEN, 11, AF, AF4, OD, PU);	// SDA
        	        // Enable ISR for I2C
        	        NVIC_ISER_setVal(I2C2_EV);
        	        NVIC_ISER_setVal(I2C2_ER);

					DMA_direct_param_tx_st.Stream_info_st.DMAx = DMA1;
					DMA_direct_param_tx_st.Stream_info_st.stream = Stream_7;
					DMA_direct_param_tx_st.Stream_info_st.channel = 7;

					DMA_direct_param_rx_st.Stream_info_st.DMAx = DMA1;
					DMA_direct_param_rx_st.Stream_info_st.stream = Stream_3;
					DMA_direct_param_rx_st.Stream_info_st.channel = 7;

        	        break;

        	    case I2C3:
        	        // Enable I2C clock
        	        SET_BIT(RCC_reg->APB1ENR, 23U);
        	        // Setup GPIO for I2C
        	        GPIO_setup(GPIOAEN, 8, AF, AF4, OD, PU);	// SCL
	    			GPIO_setup(GPIOCEN, 9, AF, AF4, OD, PU);	// SDA
        	        // Enable ISR for I2C
        	        NVIC_ISER_setVal(I2C3_EV);
        	        NVIC_ISER_setVal(I2C3_ER);

					DMA_direct_param_tx_st.Stream_info_st.DMAx = DMA1;
					DMA_direct_param_tx_st.Stream_info_st.stream = Stream_4;
					DMA_direct_param_tx_st.Stream_info_st.channel = 3;

					DMA_direct_param_rx_st.Stream_info_st.DMAx = DMA1;
					DMA_direct_param_rx_st.Stream_info_st.stream = Stream_2;
					DMA_direct_param_rx_st.Stream_info_st.channel = 3;

        	        break;

        	    default:
        	        return NOT_OK;
        	}

        	// Setting for DMA
			if ((NOT_OK == DMA_direct_init(DMA_direct_param_tx_st)) || (NOT_OK == DMA_direct_init(DMA_direct_param_rx_st)))
			{
				return NOT_OK;
			}

			is_DMA_Init_done[I2Cx_en] = true;
		}

		// Check Bus busy
		if (READ_REG(I2C_reg[I2Cx_en]->SR2, 1UL, 1U))
		{
			uint32_t timegap_u32;

			// Software reset
			SET_BIT(I2C_reg[I2Cx_en]->CR1, 15U);
			timegap_u32 = SysTick_cnt_u32;

			// Wait for Bus ready
			while (READ_REG(I2C_reg[I2Cx_en]->SR2, 1UL, 1U))
			{
				if (
					((SysTick_cnt_u32 < timegap_u32) && (5UL <= (SysTick_cnt_u32 + (0xFFFFFFFFUL - timegap_u32) - 1)))
					|| ((SysTick_cnt_u32 >= timegap_u32) && (5UL <= (SysTick_cnt_u32 - timegap_u32)))
				)
				{
					return NOT_OK;
				}
			}

			// clear reset bit
			CLEAR_BIT(I2C_reg[I2Cx_en]->CR1, 15U);
		}

		uint32_t I2C_freq_u32 = APB1_freq / 1000000;
		
        // Setting for I2C
        // Peripheral disable
        CLEAR_BIT(I2C_reg[I2Cx_en]->CR1, 0U);
        // DMA requests enable
        SET_BIT(I2C_reg[I2Cx_en]->CR2, 11U);
        // Enable Event interrupt enable
        SET_BIT(I2C_reg[I2Cx_en]->CR2, 9U);
        // Enable Error interrupt enable
        SET_BIT(I2C_reg[I2Cx_en]->CR2, 8U);
        // Set Peripheral clock frequency
        WRITE_REG(I2C_reg[I2Cx_en]->CR2, 0x3FUL, 0U, I2C_freq_u32);
        // I2C master mode selection: Sm
        CLEAR_BIT(I2C_reg[I2Cx_en]->CCR, 15U);
        // Clock control register in Fm/Sm mode (Master mode)
        WRITE_REG(I2C_reg[I2Cx_en]->CCR, 0xFFFUL, 0U, (I2C_freq_u32 * 5U)); // CCR = APB1 / (2 * 100kHz)
        // Maximum rise time in Fm/Sm mode (Master mode): 1000ns
        WRITE_REG(I2C_reg[I2Cx_en]->TRISE, 0x3FUL, 0U, (I2C_freq_u32 + 1));
        // Acknowledge enable
        SET_BIT(I2C_reg[I2Cx_en]->CR1, 10U);
        // Peripheral enable
        SET_BIT(I2C_reg[I2Cx_en]->CR1, 0U);
		I2C_init_state[I2Cx_en] = INITTED;
    }
    else
    {
        return NOT_OK;
    }

    return OK;
}

bool I2C_master_recv(I2Cx_t I2Cx_en, uint8_t addr_u8, uint32_t length_u32)
{
	if (
		(NOT_INITTED == I2C_init_state[I2Cx_en])
		|| (I2C_STATE_BUSY == I2C_state_tx[I2Cx_en])
		|| (I2C_STATE_BUSY == I2C_state_rx[I2Cx_en])
		|| (length_u32 > ARR_SIZE)
	)
	{
		return NOT_OK;
	}
	else
	{
		// Check Bus busy
		if (READ_REG(I2C_reg[I2Cx_en]->SR2, 1UL, 1U))
		{
			uint32_t timegap_u32;

			// Software reset
			SET_BIT(I2C_reg[I2Cx_en]->CR1, 15U);
			timegap_u32 = SysTick_cnt_u32;

			// Wait for Bus ready
			while (READ_REG(I2C_reg[I2Cx_en]->SR2, 1UL, 1U))
			{
				if (
					((SysTick_cnt_u32 < timegap_u32) && (5UL <= (SysTick_cnt_u32 + (0xFFFFFFFFUL - timegap_u32) - 1)))
					|| ((SysTick_cnt_u32 >= timegap_u32) && (5UL <= (SysTick_cnt_u32 - timegap_u32)))
				)
				{
					return NOT_OK;
				}
			}

			// clear reset bit
			CLEAR_BIT(I2C_reg[I2Cx_en]->CR1, 15U);

			// Setup I2C again
			if (NOT_OK == I2C_init(I2Cx_en))
			{
				return NOT_OK;
			}
		}

		buffer_t buffer_info_rx_st = (buffer_t)
		{
			.data_length = length_u32,
			.peri_addr = &I2C_reg[I2Cx_en]->DR,
			.mem_addr = (volatile uint8_t *)I2C_recv_buf[I2Cx_en]
		};

		stream_channel_t Stream_info_st;

		switch (I2Cx_en)
        {
            case I2C1:
                Stream_info_st.DMAx = DMA1;
				Stream_info_st.stream = Stream_5;
				Stream_info_st.channel = 1;

                break;

            case I2C2:
                Stream_info_st.DMAx = DMA1;
				Stream_info_st.stream = Stream_3;
				Stream_info_st.channel = 7;

                break;

            case I2C3:
                Stream_info_st.DMAx = DMA1;
				Stream_info_st.stream = Stream_2;
				Stream_info_st.channel = 3;

                break;

            default:
                return NOT_OK;
        }

		isUpdated_I2C[I2Cx_en] = false;
		I2C_state_rx[I2Cx_en] = I2C_STATE_BUSY;
		// Reset buffer BEFORE starting DMA to avoid race conditions
	    memset((void*)I2C_recv_buf[I2Cx_en], 0, ARR_SIZE * sizeof(*I2C_recv_buf[I2Cx_en]));
		I2C_addr[I2Cx_en] = ((addr_u8 << 1U) | 1U);
		// Setup DMA
		DMA_transfer(Stream_info_st, buffer_info_rx_st);
		// Ensure ACK is enabled before starting
		SET_BIT(I2C_reg[I2Cx_en]->CR1, 10U);
		// Generate START Condition
		SET_BIT(I2C_reg[I2Cx_en]->CR1, 8U);
	}

	return OK;
}

bool I2C_master_send(I2Cx_t I2Cx_en, uint8_t addr_u8, const uint8_t *buf, uint32_t length_u32)
{
	if (
		(NOT_INITTED == I2C_init_state[I2Cx_en])
		|| (I2C_STATE_BUSY == I2C_state_tx[I2Cx_en])
		|| (I2C_STATE_BUSY == I2C_state_rx[I2Cx_en])
		|| (NULL == buf)
		|| (0 == length_u32)
	)
	{
		return NOT_OK;
	}
	else
	{
		// Check Bus busy
		if (READ_REG(I2C_reg[I2Cx_en]->SR2, 1UL, 1U))
		{
			uint32_t timegap_u32;

			// Software reset
			SET_BIT(I2C_reg[I2Cx_en]->CR1, 15U);
			timegap_u32 = SysTick_cnt_u32;

			// Wait for Bus ready
			while (READ_REG(I2C_reg[I2Cx_en]->SR2, 1UL, 1U))
			{
				if (
					((SysTick_cnt_u32 < timegap_u32) && (5UL <= (SysTick_cnt_u32 + (0xFFFFFFFFUL - timegap_u32) - 1)))
					|| ((SysTick_cnt_u32 >= timegap_u32) && (5UL <= (SysTick_cnt_u32 - timegap_u32)))
				)
				{
					return NOT_OK;
				}
			}

			// clear reset bit
			CLEAR_BIT(I2C_reg[I2Cx_en]->CR1, 15U);

			// Setup I2C again
			if (NOT_OK == I2C_init(I2Cx_en))
			{
				return NOT_OK;
			}
		}

		buffer_t buffer_info_tx_st = (buffer_t)
		{
			.data_length = length_u32,
			.peri_addr = &I2C_reg[I2Cx_en]->DR,
			.mem_addr = (volatile uint8_t *)buf
		};

		stream_channel_t Stream_info_st;

		switch (I2Cx_en)
        {
            case I2C1:
                Stream_info_st.DMAx = DMA1;
				Stream_info_st.stream = Stream_7;
				Stream_info_st.channel = 1;
                break;

            case I2C2:
                Stream_info_st.DMAx = DMA1;
				Stream_info_st.stream = Stream_7;
				Stream_info_st.channel = 7;
                break;

            case I2C3:
                Stream_info_st.DMAx = DMA1;
				Stream_info_st.stream = Stream_4;
				Stream_info_st.channel = 3;
                break;

            default:
                return NOT_OK;
        }

		I2C_state_tx[I2Cx_en] = I2C_STATE_BUSY;
		// Write address: LSB = 0 for transmitter
		I2C_addr[I2Cx_en] = (addr_u8 << 1U);
		// Setup DMA
		DMA_transfer(Stream_info_st, buffer_info_tx_st);
		// Ensure ACK is enabled (though primarily needed for RX, it's good practice)
		SET_BIT(I2C_reg[I2Cx_en]->CR1, 10U);
		// Generate START Condition
		SET_BIT(I2C_reg[I2Cx_en]->CR1, 8U);
	}
	return OK;
}
