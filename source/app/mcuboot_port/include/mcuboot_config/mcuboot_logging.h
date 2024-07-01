#ifndef _MCUBOOT_LOGGING_H
#define _MCUBOOT_LOGGING_H

#include "mcuboot_config/mcuboot_config.h"
#include "SEGGER_RTT.h"

#define MCUBOOT_LOG_MODULE_DECLARE(...)
#define MCUBOOT_LOG_MODULE_REGISTER(...)

#if MCUBOOT_LOG_LVL >= MCUBOOT_LOG_LVL_ERR
#define MCUBOOT_LOG_ERR(_fmt, ...) \
  SEGGER_RTT_printf(0, "[ERR] " _fmt "\n", ##__VA_ARGS__);
#else
#define MCUBOOT_LOG_ERR(_fmt, ...)
#endif

#if MCUBOOT_LOG_LVL >= MCUBOOT_LOG_LVL_WRN
#define MCUBOOT_LOG_WRN(_fmt, ...) \
  SEGGER_RTT_printf(0, "[WRN] " _fmt "\n", ##__VA_ARGS__);
#else
#define MCUBOOT_LOG_WRN(_fmt, ...)
#endif

#if MCUBOOT_LOG_LVL >= MCUBOOT_LOG_LVL_INF
#define MCUBOOT_LOG_INF(_fmt, ...) \
  SEGGER_RTT_printf(0, "[INF] " _fmt "\n", ##__VA_ARGS__);
#else
#define MCUBOOT_LOG_INF(_fmt, ...)
#endif

#if MCUBOOT_LOG_LVL >= MCUBOOT_LOG_LVL_DBG
#define MCUBOOT_LOG_DBG(_fmt, ...) \
  SEGGER_RTT_printf(0, "[DBG] " _fmt "\n", ##__VA_ARGS__);
#else
#define MCUBOOT_LOG_DBG(_fmt, ...)
#endif

#endif /* _MCUBOOT_LOGGING_H */
