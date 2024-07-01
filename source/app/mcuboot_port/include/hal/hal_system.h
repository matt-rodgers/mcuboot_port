#ifndef _HAL_SYSTEM_H
#define _HAL_SYSTEM_H

#include "stm32f4xx_hal.h"
#include "core_cm4.h"

static inline void hal_system_reset(void)
{
    NVIC_SystemReset();
}

#endif /* _HAL_SYSTEM_H */
