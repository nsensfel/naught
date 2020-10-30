#include <naught/benchmarks.h>

#include <naught/cpu/cache.h>
#include <naught/cpu/cpu.h>
#include <naught/cpu/monitor.h>

#include <naught/sane_assembly.h>

#include <naught/kernel/barrier.h>
#include <naught/kernel/mutex.h>
#include <naught/kernel/output.h>

#include <stdint.h>

#define __NAUGHT_BENCH_RUNS 10
#define __NAUGHT_BENCH_RUN_RESULTS (__NAUGHT_BENCH_RUNS * 4)

/******************************************************************************/
/**** LOCAL FUNCTIONS *********************************************************/
/******************************************************************************/
static inline void clear_caches (const uint8_t core_id)
{
   naught_cache_l1_data_invalidate();
   naught_cache_l2_flush(core_id % 4);
}

static inline void start_monitor ()
{
	   naught_monitor_counter_initialize
	   (
	      NAUGHT_MONITOR_COUNTER_0,
	      NAUGHT_CPU_CYCLES
	   );

	   naught_monitor_counter_initialize
	   (
	      NAUGHT_MONITOR_COUNTER_1,
	      NAUGHT_CACHE_L2_SNOOPS_CAUSING_MINT
	   );

	   naught_monitor_counter_initialize
	   (
	      NAUGHT_MONITOR_COUNTER_2,
	      NAUGHT_CACHE_L2_SNOOPS_CAUSING_SINT
	   );

	   naught_monitor_counter_initialize
	   (
	      NAUGHT_MONITOR_COUNTER_3,
	      NAUGHT_CACHE_L2_DATA_ACCESSES
	   );
}

static inline void store_monitor_results
(
   uint32_t results[const restrict static 1],
   int run_id
)
{
   run_id = run_id * 4;

   results[run_id] = naught_monitor_counter_read(NAUGHT_MONITOR_COUNTER_0);
   results[run_id + 1] = naught_monitor_counter_read(NAUGHT_MONITOR_COUNTER_1);
   results[run_id + 2] = naught_monitor_counter_read(NAUGHT_MONITOR_COUNTER_2);
   results[run_id + 3] = naught_monitor_counter_read(NAUGHT_MONITOR_COUNTER_3);
}

static inline void print_monitor_results
(
   uint32_t results[const restrict static 1],
   const int run_id
)
{
   const int ix = (run_id * 4);

   printf
   (
      "Results for run %d:\r\n"
      "- [0] %lu\r\n"
      "- [1] %lu\r\n"
      "- [2] %lu\r\n"
      "- [3] %lu\r\n",
      run_id,
      (unsigned long int) results[ix],
      (unsigned long int) results[ix + 1],
      (unsigned long int) results[ix + 2],
      (unsigned long int) results[ix + 3]
   );
}

static inline void load_test (const uint8_t core_id, const int runs)
{
   register int32_t whatever;
   register int i, j;

   j = 0;
   whatever = 0;

   for (i = 0; i < runs; ++i)
   {
      whatever += naught_shared_elements[j].int32[0];

      j++;
   }

   if (j == __NAUGHT_SHARED_ELEMENTS_COUNT)
   {
      j = 0;
   }

   naught_shared_elements[j].int32[0] = whatever;
}

static inline void asm_load_test (const uint8_t core_id, const int runs)
{
   register int i, j;
   register uint32_t buffer;

   j = 0;

   for (i = 0; i < runs; ++i)
   {
      asm volatile
      (
         ASM_LOAD_WORD_AND_ZERO " %[buffer], 0 (%[line_addr])\n"
         : [buffer] "=r" (buffer)
         : [line_addr] "r" (naught_shared_elements + j)
         : "memory"
      );

      j++;
   }
}

static naught_barrier_t barrier_a = NAUGHT_BARRIER_INITIALIZED(2);
static naught_barrier_t barrier_b = NAUGHT_BARRIER_INITIALIZED(2);
static naught_barrier_t barrier_c = NAUGHT_BARRIER_INITIALIZED(2);

/******************************************************************************/
/**** EXPORTED FUNCTIONS ******************************************************/
/******************************************************************************/
void naught_benchmark_shared_to_exclusive
(
   const uint8_t core_id,
   const int role
)
{
   const int ops_per_run = 1000;

   switch (role)
   {
      case 0:
         load_test(core_id, ops_per_run);
         // Should now have the set in Exclusive.
         naught_barrier_join(&barrier_a);

         naught_barrier_join(&barrier_b);
         // Should now have the set in Shared.

         clear_caches(core_id);
         // Should now have the set in Invalid.

         naught_barrier_join(&barrier_c);
         break;

      case 1:
         naught_barrier_join(&barrier_a);

         load_test(core_id, ops_per_run);

         // Should now have the set in Shared.
         naught_barrier_join(&barrier_b);

         clear_caches(core_id);

         naught_barrier_join(&barrier_c);

         load_test(core_id, ops_per_run);
         // Should have the set in Shared, but maybe Exclusive?
         break;

      case 2:
         naught_barrier_join(&barrier_a);

         load_test(core_id, ops_per_run);

         // Should now have the set in Shared.
         naught_barrier_join(&barrier_b);
         naught_barrier_join(&barrier_c);

         // Should have the set in Shared, but maybe Exclusive?
         break;
   }
}
