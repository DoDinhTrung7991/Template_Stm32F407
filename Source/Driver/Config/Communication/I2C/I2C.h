#ifndef _I2C_H_
#define _I2C_H_

// Driver is only written for Sm mode and Master

#include "stdUtility.h"
#include "I2C_header.h"
#include "queue.h"

#define I2C_STATE_READY 1
#define I2C_STATE_BUSY 0

typedef enum
{
    I2C1,
    I2C2,
    I2C3
} I2Cx_t;

typedef enum
{
    RECV,
    SEND
} SEND_or_RECV_t;

extern volatile bool I2C_init_state[3];
extern volatile uint8_t I2C_recv_buf[3][ARR_SIZE];
extern volatile bool I2C_state_tx[3];
extern volatile bool I2C_state_rx[3];
extern volatile uint8_t isUpdated_I2C[3];
extern volatile uint8_t I2C_addr[3];

bool I2C_init(I2Cx_t I2Cx_en);
bool I2C_master_recv(I2Cx_t I2Cx_en, uint8_t addr_u8, uint32_t length_u32);
bool I2C_master_send(I2Cx_t I2Cx_en, uint8_t addr_u8, const uint8_t *buf, uint32_t length_u32);

#endif
