#pragma once

#define NAUGHT_PRINT_DEBUG_MESSAGES 0
#define NAUGHT_PRINT_INFO_MESSAGES 1

#include <stdio.h>

#if NAUGHT_PRINT_DEBUG_MESSAGES == 1
#define naught_debug(...) printf(__VA_ARGS__)
#else
#define naught_debug(...)
#endif

#if NAUGHT_PRINT_INFO_MESSAGES == 1
#define naught_info(...) printf(__VA_ARGS__)
#else
#define naught_info(...)
#endif
