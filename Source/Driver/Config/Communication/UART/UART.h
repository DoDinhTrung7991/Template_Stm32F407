#ifndef _UART_H_
#define _UART_H_

#include "init_static.h"
#include "USART_header.h"
#include "DMA_header.h"

#define UART_STATE_READY 1
#define UART_STATE_BUSY 0

extern volatile bool UART_init_state[6];
extern volatile uint16_t UART_recv_buf[6][1];
extern volatile bool UART_state_tx[6];
extern volatile bool UART_state_rx[6];
extern volatile uint8_t isUpdated_UART[6];

typedef enum
{
    USART1,
    USART2,
    USART3,
    UART4,
    UART5,
    USART6
} UARTx_t;

bool UART_init(UARTx_t UARTx, uint32_t baudrate);
bool UART_transmit(UARTx_t UARTx, const uint16_t *buf, uint8_t data_length);
bool UART_receive(UARTx_t UARTx, volatile uint16_t* buf);
int UART_Read(UARTx_t UARTx);

#endif
