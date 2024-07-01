#ifndef _OS_CPUTIME_H
#define _OS_CPUTIME_H

#include "stm32f4xx_hal.h"

/**
 * @brief Generate a blocking delay
 * 
 * @param usecs Number of microseconds to delay for
 * 
 * @note This is never actually called with delays of the order of microseconds, it's only called
 *       for multiple hundreds of ms. So we can just use a ms delay routine internally.
*/
static inline void os_cputime_delay_usecs(uint32_t usecs)
{
    HAL_Delay(usecs / 1000);
}

#endif /* _OS_CPUTIME_H */
