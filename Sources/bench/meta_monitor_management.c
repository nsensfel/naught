#include <naught/cpu/monitor.h>

#include <naught/kernel/mutex.h>
#include <naught/kernel/output.h>

#include <stdint.h>

void naught_benchmark_meta_start_monitor
(
   const int event_0,
   const int event_1,
   const int event_2,
   const int event_3
)
{
   naught_monitor_counter_initialize(NAUGHT_MONITOR_COUNTER_0, event_0);
   naught_monitor_counter_initialize(NAUGHT_MONITOR_COUNTER_1, event_1);
   naught_monitor_counter_initialize(NAUGHT_MONITOR_COUNTER_2, event_2);
   naught_monitor_counter_initialize(NAUGHT_MONITOR_COUNTER_3, event_3);
}

void naught_benchmark_meta_freeze_monitors (void)
{
   naught_monitor_counter_freeze(NAUGHT_MONITOR_COUNTER_0);
   naught_monitor_counter_freeze(NAUGHT_MONITOR_COUNTER_1);
   naught_monitor_counter_freeze(NAUGHT_MONITOR_COUNTER_2);
   naught_monitor_counter_freeze(NAUGHT_MONITOR_COUNTER_3);
}

void naught_benchmark_meta_resume_monitors (void)
{
   naught_monitor_counter_resume(NAUGHT_MONITOR_COUNTER_0);
   naught_monitor_counter_resume(NAUGHT_MONITOR_COUNTER_1);
   naught_monitor_counter_resume(NAUGHT_MONITOR_COUNTER_2);
   naught_monitor_counter_resume(NAUGHT_MONITOR_COUNTER_3);
}

static naught_mutex_t printf_protector = NAUGHT_MUTEX_INITIALIZED;

void naught_benchmark_meta_print_monitor_results
(
   const uint8_t core_id,
   const uint32_t results[const restrict static 1],
   const int run_id
)
{
   const int ix = (run_id * 4);

   naught_mutex_lock(core_id, &printf_protector);
   printf
   (
      "[Core %d] Results for run %d:\r\n"
      "- [0] %lu\r\n"
      "- [1] %lu\r\n"
      "- [2] %lu\r\n"
      "- [3] %lu\r\n",
      (int) core_id,
      run_id,
      (unsigned long int) results[ix],
      (unsigned long int) results[ix + 1],
      (unsigned long int) results[ix + 2],
      (unsigned long int) results[ix + 3]
   );
   naught_mutex_unlock(core_id, &printf_protector);
}

void naught_benchmark_meta_store_monitor_results
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

void naught_benchmark_meta_print_offset_monitor_results
(
   const uint8_t core_id,
   const uint32_t results[const restrict static 1],
   const int run_id,
   const int array_offset,
   const int print_offset
)
{
   const int ix = (run_id * 4) + array_offset;

   naught_mutex_lock(core_id, &printf_protector);
   printf
   (
      "[Core %d] Results for run %d:\r\n"
      "- [%d] %lu\r\n"
      "- [%d] %lu\r\n"
      "- [%d] %lu\r\n"
      "- [%d] %lu\r\n",
      (int) core_id,
      run_id,
      (print_offset), (unsigned long int) results[ix],
      (print_offset + 1), (unsigned long int) results[ix + 1],
      (print_offset + 2), (unsigned long int) results[ix + 2],
      (print_offset + 3), (unsigned long int) results[ix + 3]
   );
   naught_mutex_unlock(core_id, &printf_protector);
}
