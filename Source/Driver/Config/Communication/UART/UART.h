#ifndef _UART_H_
#define _UART_H_

#include "init_static.h"
#include "USART_header.h"

#define UART_STATE_READY 1
#define UART_STATE_BUSY 0

extern volatile uint8_t UART_recv_buf[2];
extern bool isUpdated_UART;

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
bool UART_transmit(UARTx_t UARTx, const uint8_t* buf, uint8_t data_length);
bool UART_receive(UARTx_t UARTx, volatile uint8_t* buf);
uint8_t UART_Read(void);

#endif
