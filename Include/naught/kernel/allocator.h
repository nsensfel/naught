#pragma once

#include <stdint.h>

void naught_allocator_init (void);
void * naught_allocator_get (const uint8_t core_id, const uint32_t size);
