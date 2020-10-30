#include <naught/benchmarks.h>

#include <naught/cpu/cache.h>
#include <naught/cpu/cpu.h>
#include <naught/cpu/monitor.h>

#include <naught/sane_assembly.h>
#include <naught/kernel/output.h>

#include <stdint.h>

#define __NAUGHT_BENCH_RUNS 20
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

static inline void freeze_monitors ()
{
   naught_monitor_counter_freeze(NAUGHT_MONITOR_COUNTER_0);
   naught_monitor_counter_freeze(NAUGHT_MONITOR_COUNTER_1);
   naught_monitor_counter_freeze(NAUGHT_MONITOR_COUNTER_2);
   naught_monitor_counter_freeze(NAUGHT_MONITOR_COUNTER_3);
}

static inline void resume_monitors ()
{
   naught_monitor_counter_resume(NAUGHT_MONITOR_COUNTER_0);
   naught_monitor_counter_resume(NAUGHT_MONITOR_COUNTER_1);
   naught_monitor_counter_resume(NAUGHT_MONITOR_COUNTER_2);
   naught_monitor_counter_resume(NAUGHT_MONITOR_COUNTER_3);
}

static inline void asm_load_then_write_test
(
   const uint8_t core_id,
   const int runs
)
{
   register int i, j;
   register uint32_t buffer;

   j = 0;

   for (i = 0; i < runs; ++i)
   {
      if (j == __NAUGHT_SHARED_ELEMENTS_COUNT)
      {
         freeze_monitors();
         clear_caches(core_id);
         j = 0;
         resume_monitors();
      }

      asm volatile
      (
         ASM_LOAD_WORD_AND_ZERO " %[buffer], 0 (%[line_addr])\n"
         : [buffer] "=r" (buffer)
         : [line_addr] "r" (naught_shared_elements + j)
         : "memory"
      );

      asm volatile
      (
         ASM_STORE_WORD " %[stored_val], 0 (%[line_addr])\n"
         :
         : [line_addr] "r" (naught_shared_elements + j),
            [stored_val] "i" (0)
         : "memory"
      );

      j++;
   }
}

/******************************************************************************/
/**** EXPORTED FUNCTIONS ******************************************************/
/******************************************************************************/
void naught_benchmark_exclusive_free_upgrade (const uint8_t core_id)
{
   uint32_t results[__NAUGHT_BENCH_RUN_RESULTS];
   register int i;
   register int ops_per_run;

   ops_per_run = 1000;

   for (i = 0; i < __NAUGHT_BENCH_RUNS; ++i)
   {
      clear_caches(core_id);
      start_monitor(core_id);

      asm_load_then_write_test(core_id, ops_per_run);

      store_monitor_results(results, i);
      print_monitor_results(results, i);

      ops_per_run += 1000;
   }
}
