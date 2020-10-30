#pragma once

#include <stdint.h>

/* [Warning]
 * reseting a barrier is not thread-safe: even if a thread passed the barrier,
 * you can't be sure that the others have seen that the barrier was open before
 * you reset it.
 */
typedef uint32_t naught_barrier_t;

#define NAUGHT_BARRIER_INITIALIZED(req) req

void naught_barrier_initialize
(
   naught_barrier_t [const static 1],
   const uint32_t req
);

void naught_barrier_join (naught_barrier_t m [const static 1]);
