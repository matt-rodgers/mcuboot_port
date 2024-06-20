#ifndef _LOG_H
#define _LOG_H

#include "SEGGER_RTT.h"

#define LOG(str, ...) SEGGER_RTT_printf(0, str, ##__VA_ARGS__)

#endif /* _LOG_H */
