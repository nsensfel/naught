#pragma once

#include <stdint.h>

typedef uint32_t naught_mutex_t;

#define NAUGHT_MUTEX_INITIALIZED 0

void naught_mutex_initialize (naught_mutex_t [const static 1]);
void naught_mutex_lock
(
   const uint8_t core_id,
   naught_mutex_t m [const static 1]
);
void naught_mutex_unlock
(
   const uint8_t core_id,
   naught_mutex_t m [const static 1]
);
