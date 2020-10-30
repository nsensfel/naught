#include <naught/benchmarks.h>

#include <naught/cpu/cache.h>
#include <naught/cpu/cpu.h>
#include <naught/cpu/monitor.h>

#include <naught/sane_assembly.h>
#include <naught/kernel/output.h>
#include <naught/kernel/barrier.h>
#include <naught/kernel/mutex.h>

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
      NAUGHT_CACHE_L2_SNOOP_HITS
   );

   naught_monitor_counter_initialize
   (
      NAUGHT_MONITOR_COUNTER_1,
      NAUGHT_CACHE_L2_SNOOP_PUSHES
   );

   naught_monitor_counter_initialize
   (
      NAUGHT_MONITOR_COUNTER_2,
    //NAUGHT_CACHE_STALLS_FOR_SNPQ_CYCLES
      NAUGHT_CACHE_L2_RELOADS_FROM_CORENET
   );

   naught_monitor_counter_initialize
   (
      NAUGHT_MONITOR_COUNTER_3,
      NAUGHT_CACHE_EXTERNAL_SNOOP_REQUESTS
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

static inline void asm_load_test
(
   const uint8_t core_id,
   const int runs,
   const int element_ix
)
{
   register int i;
   register uint32_t buffer;
   const uint32_t * element_addr =
      (uint32_t *) (naught_shared_elements + element_ix);

   for (i = 0; i < runs; ++i)
   {
      asm volatile
      (
         ASM_LOAD_WORD_AND_ZERO " %[buffer], 0 (%[line_addr])\n"
         : [buffer] "=r" (buffer)
         : [line_addr] "r" (element_addr)
         : "memory"
      );

      asm volatile
      (
         ASM_DATA_CACHE_BLOCK_FLUSH " 0, %[line_addr]\n"
         :
         : [line_addr] "r" (element_addr)
         : "memory"
      );
   }
}

static inline void asm_store_test
(
   const uint8_t core_id,
   const int runs,
   const int element_ix
)
{
   register int i;
   const uint32_t * element_addr =
      (uint32_t *) (naught_shared_elements + element_ix);

   for (i = 0; i < runs; ++i)
   {
      asm volatile
      (
         ASM_STORE_WORD " %[stored_val], 0 (%[line_addr])\n"
         :
         : [line_addr] "r" (element_addr),
            [stored_val] "i" (0)
         : "memory"
      );

      asm volatile
      (
         ASM_DATA_CACHE_BLOCK_FLUSH " 0, %[line_addr]\n"
         :
         : [line_addr] "r" (element_addr)
         : "memory"
      );
   }
}

static naught_barrier_t meta_barrier = NAUGHT_BARRIER_INITIALIZED(3);
static naught_barrier_t exp_barrier_in[__NAUGHT_BENCH_RUNS];
static naught_barrier_t exp_barrier_out[__NAUGHT_BENCH_RUNS];
static naught_mutex_t output_mutex = NAUGHT_MUTEX_INITIALIZED;

/******************************************************************************/
/**** EXPORTED FUNCTIONS ******************************************************/
/******************************************************************************/
void naught_benchmark_crossfires
(
   const uint8_t core_id,
   const int role,
   const int element
)
{
   uint32_t results[__NAUGHT_BENCH_RUN_RESULTS];
   register int i;
   register int ops_per_run;

   if (core_id == 0)
   {
      for (int i = 0; i < __NAUGHT_BENCH_RUNS; i++)
      {
         exp_barrier_in[i] = NAUGHT_BARRIER_INITIALIZED(3);
         exp_barrier_out[i] = NAUGHT_BARRIER_INITIALIZED(3);
      }
   }

   naught_barrier_join(&meta_barrier);

   ops_per_run = 1000;

   for (i = 0; i < __NAUGHT_BENCH_RUNS; ++i)
   {
      clear_caches(core_id);

      naught_barrier_join(exp_barrier_in + i);
      start_monitor(core_id);

      switch (role)
      {
         case NAUGHT_INSTRUCTION_LOAD:
            asm_load_test(core_id, ops_per_run, element);
            break;

         case NAUGHT_INSTRUCTION_STORE:
            asm_store_test(core_id, ops_per_run, element);
            break;

      }

      store_monitor_results(results, i);
      naught_barrier_join(exp_barrier_in + i);

      naught_mutex_lock(core_id, &output_mutex);
      print_monitor_results(results, i);
      naught_mutex_unlock(core_id, &output_mutex);

      ops_per_run += 1000;
   }
}
