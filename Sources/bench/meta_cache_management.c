#include <naught/cpu/cache.h>
#include <naught/cpu/cpu.h>

#include <stdint.h>

void naught_benchmark_meta_reset_caches (const uint8_t core_id)
{
   naught_cache_l1_data_invalidate();
   naught_cache_l2_flush(core_id / NAUGHT_CPU_IDS_PER_CLUSTER);
}

