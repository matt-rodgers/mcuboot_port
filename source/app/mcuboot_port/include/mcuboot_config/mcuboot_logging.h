#ifndef _MCUBOOT_LOGGING_H
#define _MCUBOOT_LOGGING_H

#include "SEGGER_RTT.h"

#define MCUBOOT_LOG_MODULE_DECLARE(...)
#define MCUBOOT_LOG_MODULE_REGISTER(...)

#define MCUBOOT_LOG_ERR(_fmt, ...) \
  SEGGER_RTT_printf(0, "[ERR] " _fmt, ##__VA_ARGS__);
#define MCUBOOT_LOG_WRN(_fmt, ...) \
  SEGGER_RTT_printf(0, "[WRN] " _fmt, ##__VA_ARGS__);
#define MCUBOOT_LOG_INF(_fmt, ...) \
  SEGGER_RTT_printf(0, "[INF] " _fmt, ##__VA_ARGS__);
#define MCUBOOT_LOG_DBG(_fmt, ...) \
  SEGGER_RTT_printf(0, "[DBG] " _fmt, ##__VA_ARGS__);

#endif /* _MCUBOOT_LOGGING_H */
