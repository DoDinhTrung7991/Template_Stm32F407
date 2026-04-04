#include "stdUtility.h"
#include "IWDG_header.h"

typedef enum
{
    _500ms,
    _1000ms,
    _2000ms,
    _4000ms,
    _8000ms,
    _16000ms,
    _32000ms
} IWDG_timeout_t;

bool IWDG_init(IWDG_timeout_t timeout);
void IWDG_reset(void);
