#ifndef _MCUBOOT_ASSERT_H
#define _MCUBOOT_ASSERT_H

#include "log.h"

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x

#define ASSERT(cond) \
    do { \
        if (!(cond)) { \
            LOG("[ASSERTION FAIL]: file " __FILE__ ", line " STRINGIZE(__LINE__) "\n"); \
        } \
        while (1) {} \
    } while (0)

#endif /* _MCUBOOT_ASSERT_H */
