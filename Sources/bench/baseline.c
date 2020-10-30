#include <stdint.h>
#include <stdio.h>

#include <naught/cpu/cache.h>
#include <naught/cpu/monitor.h>
#include <naught/cpu/prediction.h>

#include <naught/kernel/output.h>

#include <naught/benchmarks.h>

#define __NAUGHT_EXP_ELEMENTS 5
#define __NAUGHT_COUNTERS_COUNT 4

#define __NAUGHT_EXPERIMENT_COUNT 1
#define __NAUGHT_RESULTS_COUNT \
   (__NAUGHT_EXPERIMENT_COUNT * __NAUGHT_COUNTERS_COUNT)

#if (__NAUGHT_EXP_ELEMENTS > __NAUGHT_SHARED_ELEMENTS_COUNT)
#error "Too many __NAUGHT_EXP_ELEMENTS."
#endif
/******************************************************************************/
/**** LOCAL FUNCTIONS *********************************************************/
/******************************************************************************/
static inline void enable_monitoring ()
{
   naught_monitor_enable(1);

   naught_monitor_counter_initialize
   (
      NAUGHT_MONITOR_COUNTER_0,
      NAUGHT_CACHE_L2_HITS
   );
   naught_monitor_counter_initialize
   (
      NAUGHT_MONITOR_COUNTER_1,
      NAUGHT_CACHE_L2_DATA_ACCESSES
   );
   naught_monitor_counter_initialize
   (
      NAUGHT_MONITOR_COUNTER_2,
      NAUGHT_CACHE_L2_DATA_MISSES
   );
   naught_monitor_counter_initialize
   (
      NAUGHT_MONITOR_COUNTER_3,
      NAUGHT_CACHE_L1_DATA_MISSES
   );
}


static inline void print_results
(
   const uint8_t core_id,
   uint32_t test_result[const restrict static 4],
   const int experiments
)
{
   int i;

   for (i = 0; i < experiments; ++i)
   {
      int j;

      for (j = 0; j < __NAUGHT_COUNTERS_COUNT; ++j)
      {
         printf
         (
            "[R][C%hu][E%d] PMR_%d: %lu.\r\n",
            core_id,
            i,
            j,
            (unsigned long) test_result[i * __NAUGHT_COUNTERS_COUNT + j]
         );
      }
   }
}



#pragma GCC push_options
//#pragma GCC optimize ("O0")
static inline void step0 ()
{
   register int i;

   for (i = 0; i < __NAUGHT_EXP_ELEMENTS; ++i)
   {
      naught_shared_elements[i].int32[0] = i;
   }
}

static inline void step1 ()
{
   register int i;
   register uint32_t useless;

   for (i = 0; i < __NAUGHT_EXP_ELEMENTS; ++i)
   {
      useless = naught_shared_elements[i].int32[0];
   }
}

static inline void step2 ()
{
   register int i;

   for (i = 0; i < __NAUGHT_EXP_ELEMENTS; ++i)
   {
      naught_shared_elements[i].int32[0] += i;
   }
}

static inline void store_results
(
   uint32_t test_result[const restrict static 4]
)
{
   register uint32_t a, b, c, d;

   /*
    * 'test_result' is stored in the memory, so writing to it may alter the
    * value of the monitor counters, that's why registers are used to store
    * the current values before any access to the memory is made.
    */
   a = naught_monitor_counter_read(NAUGHT_MONITOR_COUNTER_0);
   b = naught_monitor_counter_read(NAUGHT_MONITOR_COUNTER_1);
   c = naught_monitor_counter_read(NAUGHT_MONITOR_COUNTER_2);
   d = naught_monitor_counter_read(NAUGHT_MONITOR_COUNTER_3);

   test_result[0] = a;
   test_result[1] = b;
   test_result[2] = c;
   test_result[3] = d;
}
#pragma GCC pop_options

static inline void step3 ()
{
   register int i;

   for (i = 0; i < __NAUGHT_EXP_ELEMENTS; ++i)
   {
      naught_shared_elements[i].int32[0] = i;
   }
}

static inline void step4 ()
{
   register int i;
   register uint32_t useless;

   for (i = 0; i < __NAUGHT_EXP_ELEMENTS; ++i)
   {
      useless = naught_shared_elements[i].int32[0];
   }
}

static inline void step5 ()
{
   register int i;

   for (i = 0; i < __NAUGHT_EXP_ELEMENTS; ++i)
   {
      naught_shared_elements[i].int32[0] += i;
   }
}

/******************************************************************************/
/**** EXPORTED FUNCTIONS ******************************************************/
/******************************************************************************/
int x;
void naught_benchmark_baseline (const uint8_t core_id)
{
   uint32_t result[__NAUGHT_RESULTS_COUNT];
   register int i;
   register uint32_t * result_ptr;

   result_ptr = result;

   naught_info("[I][C%hu] Started baseline benchmark.\r\n", core_id);
   naught_info
   (
      "[I][C%hu] assert(%d == %d).\r\n",
      core_id,
      sizeof(naught_cache_line_t),
      NAUGHT_CACHE_LINE_SIZE
   );

   naught_prediction_branch_disable();
   naught_cache_l1_data_invalidate();
   naught_cache_l2_flush(core_id/32);
   naught_cache_l1_data_disable();

   x = 1;

   enable_monitoring();
   step0();
   store_results(result_ptr);

   enable_monitoring();
   step1();
   store_results(result_ptr + __NAUGHT_COUNTERS_COUNT);

   enable_monitoring();
   step2();
   store_results(result_ptr + (__NAUGHT_COUNTERS_COUNT * 2));

   naught_cache_l1_data_invalidate();
   naught_cache_l2_flush(core_id/32);

   enable_monitoring();
   step3();
   store_results(result_ptr + (__NAUGHT_COUNTERS_COUNT * 3));

   enable_monitoring();
   step4();
   store_results(result_ptr + (__NAUGHT_COUNTERS_COUNT * 4));

   enable_monitoring();
   step5();
   store_results(result_ptr + (__NAUGHT_COUNTERS_COUNT * 5));

   naught_info("[I][C%hu] Completed benchmark demo 0.\r\n", core_id);

   print_results(core_id, result, __NAUGHT_EXPERIMENT_COUNT);

}
