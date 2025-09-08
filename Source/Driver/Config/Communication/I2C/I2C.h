#ifndef _I2C_H_
#define _I2C_H_

#include "stdUtility.h"

#define I2C_STATE_READY 1
#define I2C_STATE_BUSY 0

#define INITTED 1
#define NOT_INITTED 0

typedef enum
{
    I2C1,
    I2C2,
    I2C3
} I2Cx_t;

bool I2C_init(I2Cx_t I2Cx_en);

#endif

