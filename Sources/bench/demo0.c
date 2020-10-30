#include <stdint.h>
#include <stdio.h>

#include <naught/cpu/cache.h>
#include <naught/cpu/monitor.h>

#include <naught/kernel/output.h>

#include <naught/benchmarks.h>

/******************************************************************************/
/**** LOCAL FUNCTIONS *********************************************************/
/******************************************************************************/
static inline void clear_caches (const uint8_t core_id)
{
   naught_debug("[D][C%hu] Clearing L1 Data Cache...\r\n", core_id);

   naught_cache_l1_data_invalidate();

   naught_debug("[D][C%hu] Cleared L1 Data Cache.\r\n", core_id);
   naught_debug("[D][C%hu] Clearing L2 Cache...\r\n", core_id);

   naught_cache_l2_flush(core_id % 4);

   naught_debug("[D][C%hu] Cleared L2 Cache.\r\n", core_id);

   naught_info("[I][C%hu] Cleared caches.\r\n", core_id);
}

static inline void enable_monitoring (const uint8_t core_id)
{
   naught_debug("[D][C%hu] Enabling event monitoring...\r\n", core_id);

   naught_monitor_enable(1);

   naught_debug("[D][C%hu] Enabled event monitoring.\r\n", core_id);
   naught_debug("[D][C%hu] Setting counter 0 to track L2 hits...\r\n", core_id);

   naught_monitor_counter_initialize
   (
      NAUGHT_MONITOR_COUNTER_0,
      NAUGHT_CACHE_L2_HITS
   );

   naught_debug("[D][C%hu] Set counter 0 to track L2 hits.\r\n", core_id);
   naught_debug
   (
      "[D][C%hu] Setting counter 1 to track L2 data accesses...\r\n",
      core_id
   );

   naught_monitor_counter_initialize
   (
      NAUGHT_MONITOR_COUNTER_1,
      NAUGHT_CACHE_L2_DATA_ACCESSES
   );

   naught_debug
   (
      "[D][C%hu] Set counter 1 to track L2 data accesses.\r\n",
      core_id
   );
   naught_debug
   (
      "[D][C%hu] Setting counter 2 to track L1 data stash hits...\r\n",
      core_id
   );

   naught_monitor_counter_initialize
   (
      NAUGHT_MONITOR_COUNTER_2,
      NAUGHT_CACHE_L1_DATA_STASH_HITS
   );
   naught_debug
   (
      "[D][C%hu] Set counter 2 to track L1 data stash hits.\r\n",
      core_id
   );
   naught_debug
   (
      "[D][C%hu] Setting counter 3 to track L1 data load misses...\r\n",
      core_id
   );

   naught_monitor_counter_initialize
   (
      NAUGHT_MONITOR_COUNTER_3,
      NAUGHT_CACHE_L1_DATA_LOAD_MISSES
   );

   naught_debug
   (
      "[D][C%hu] Set counter 3 to track L1 data load misses.\r\n",
      core_id
   );
   naught_info("[I][C%hu] Reset counters.\r\n", core_id);
}

static inline void print_monitoring_results (const uint8_t core_id)
{
   uint32_t test_result;

   /* L2 hits count ***********************************************************/
   naught_debug("[D][C%hu] Retrieving L2 hits count...\r\n", core_id);

   test_result = naught_monitor_counter_read(NAUGHT_MONITOR_COUNTER_0);

   naught_debug("[D][C%hu] Retrieved L2 hits count.\r\n", core_id);
   printf
   (
      "[R][C%hu] Counted %lu L2 hits.\r\n",
      core_id,
      (unsigned long) test_result
   );

   /* L2 data accesses ********************************************************/
   naught_debug("[D][C%hu] Retrieving L2 data accesses count...\r\n", core_id);

   test_result = naught_monitor_counter_read(NAUGHT_MONITOR_COUNTER_1);

   naught_debug("[D][C%hu] Retrieved L2 data accesses count.\r\n", core_id);
   printf
   (
      "[R][C%hu] Counted %lu L2 data accesses.\r\n",
      core_id,
      (unsigned long) test_result
   );

   /* L1 data stash hits ******************************************************/
   naught_debug
   (
      "[D][C%hu] Retrieving L1 data stash hits count...\r\n",
      core_id
   );

   test_result = naught_monitor_counter_read(NAUGHT_MONITOR_COUNTER_2);

   naught_debug
   (
      "[D][C%hu] Retrieved L1 data stash hits count.\r\n",
      core_id
   );

   printf
   (
      "[R][C%hu] Counted %lu L1 data stash hits.\r\n",
      core_id,
      (unsigned long) test_result
   );

   /* L1 data load misses *****************************************************/
   naught_debug
   (
      "[D][C%hu] Retrieving L1 data load misses count...\r\n",
      core_id
   );

   test_result = naught_monitor_counter_read(NAUGHT_MONITOR_COUNTER_3);

   naught_debug
   (
      "[D][C%hu] Retrieved L1 data load misses count.\r\n",
      core_id
   );

   printf
   (
      "[R][C%hu] Counted %lu L1 data load misses.\r\n",
      core_id,
      (unsigned long) test_result
   );
}

#pragma GCC push_options
#pragma GCC optimize ("O0")
static inline void perform (const uint8_t core_id)
{
   register int i;

   naught_debug("[D][C%hu] Results before starting:\r\n", core_id);
   print_monitoring_results(core_id);

   naught_info("[I][C%hu] Part 0 in progress...\r\n", core_id);
   naught_debug("[D][C%hu] Writing to 'naught_shared_elements'...\r\n", core_id);

   for (i = 0; i < __NAUGHT_SHARED_ELEMENTS_COUNT; ++i)
   {
      naught_shared_elements[i].int32[0] = i;
   }

   naught_info("[I][C%hu] Wrote to 'naught_shared_elements'.\r\n", core_id);

   print_monitoring_results(core_id);
   enable_monitoring(core_id);

   naught_debug("[D][C%hu] Clearing L1 Data Cache...\r\n", core_id);

   naught_cache_l1_data_invalidate();

   naught_info("[I][C%hu] Cleared L1 Data Cache.\r\n", core_id);
   naught_debug("[D][C%hu] Incrementing 'naught_shared_elements'...\r\n", core_id);

   for (i = 0; i < __NAUGHT_SHARED_ELEMENTS_COUNT; ++i)
   {
      naught_shared_elements[i].int32[0] += i;
   }

   naught_info("[I][C%hu] Incremented 'naught_shared_elements'.\r\n", core_id);

   print_monitoring_results(core_id);
   enable_monitoring(core_id);

   naught_info("[I][C%hu] Part 0 Completed.\r\n", core_id);

   clear_caches(core_id);

   naught_info("[I][C%hu] Part 1 in progress...\r\n", core_id);

   naught_debug("[D][C%hu] Writing to 'naught_shared_elements'...\r\n", core_id);

   for (i = 0; i < __NAUGHT_SHARED_ELEMENTS_COUNT; ++i)
   {
      naught_shared_elements[i].int32[0] = i;
   }

   naught_info("[I][C%hu] Wrote to 'naught_shared_elements'.\r\n", core_id);

   print_monitoring_results(core_id);
   enable_monitoring(core_id);

   naught_debug("[D][C%hu] Incrementing 'naught_shared_elements'...\r\n", core_id);

   for (i = 0; i < __NAUGHT_SHARED_ELEMENTS_COUNT; ++i)
   {
      naught_shared_elements[i].int32[0] += i;
   }

   naught_info("[I][C%hu] Incremented 'naught_shared_elements'.\r\n", core_id);

   print_monitoring_results(core_id);
}
#pragma GCC pop_options


/******************************************************************************/
/**** EXPORTED FUNCTIONS ******************************************************/
/******************************************************************************/
void naught_benchmark_demo0 (const uint8_t core_id)
{
   if (core_id != 0)
   {
      naught_debug("[D][C%hu] Denied access to benchmark demo 0.\r\n", core_id);

      return;
   }

   naught_info("[I][C%hu] Started benchmark demo 0.\r\n", core_id);
   clear_caches(core_id);
   enable_monitoring(core_id);
   perform(core_id);
   naught_info("[I][C%hu] Completed benchmark demo 0.\r\n", core_id);
}
