#include <naught/cpu/cache.h>
#include <naught/cpu/cpu.h>

#include <naught/kernel/barrier.h>

#include <naught/benchmarks.h>

#include <stdint.h>

#define __NAUGHT_BENCH_RUNS 20
#define __NAUGHT_BENCH_RUN_RESULTS (__NAUGHT_BENCH_RUNS * 4)

static naught_barrier_t operation_start = NAUGHT_BARRIER_INITIALIZED(2);
static naught_barrier_t operation_cleanup;
static naught_barrier_t operation_end;

/******************************************************************************/
/**** LOCAL FUNCTIONS *********************************************************/
/******************************************************************************/
static inline void run_experiment
(
   const uint8_t core_id,
   const int local_state,
   const int remote_state,
   const int operation,
   const int i,
   const int elements_count,
   uint32_t results[const restrict static __NAUGHT_BENCH_RUN_RESULTS],
   const int result_print_offset,
   const int event_0,
   const int event_1,
   const int event_2,
   const int event_3
)
{

   naught_barrier_join(&operation_start);

   if (core_id == 0)
   {
      naught_barrier_initialize(&operation_cleanup, 2);
      naught_barrier_initialize(&operation_end, 2);
   }


    naught_benchmark_meta_reach_states
    (
       core_id,
       local_state,
       remote_state,
       elements_count
    );



    if (core_id == 0)
    {
        naught_benchmark_meta_start_monitor
        (
           event_0,
           event_1,
           event_2,
           event_3
        );
        switch (operation)
        {
          case NAUGHT_INSTRUCTION_LOAD:
            naught_benchmark_meta_read_elements(elements_count);
            break;

          case NAUGHT_INSTRUCTION_STORE:
            naught_benchmark_meta_write_elements(elements_count);
            break;

          case NAUGHT_INSTRUCTION_EVICT:
        	naught_benchmark_meta_reset_caches(core_id);
            break;
         }
         naught_benchmark_meta_store_monitor_results(results, i);
         naught_barrier_join(&operation_end);
    }
    else
    {
         naught_benchmark_meta_start_monitor
         (
            event_0,
            event_1,
            event_2,
            event_3
         );
         naught_barrier_join(&operation_end);
         naught_benchmark_meta_store_monitor_results(results, i);
    }


    naught_benchmark_meta_print_offset_monitor_results
    (
      core_id,
      results,
      i,
      0,
      result_print_offset
   );

    naught_barrier_join(&operation_cleanup);
}
/******************************************************************************/
/**** EXPORTED FUNCTIONS ******************************************************/
/******************************************************************************/
void naught_benchmark_omnibenchs
(
   const uint8_t core_id,
   const int local_state,
   const int remote_state,
   const int operation
)
{
   register int i;
   register int elements_count;
   uint32_t results[__NAUGHT_BENCH_RUN_RESULTS];

   elements_count = 1000;

   for (i = 0; i < __NAUGHT_BENCH_RUNS; ++i)
   {
      run_experiment
      (
         core_id,
         local_state,
         remote_state,
         operation,
         i,
         elements_count,
         results,
         0,
         NAUGHT_CACHE_L2_DATA_ACCESSES,
         NAUGHT_CACHE_L2_SNOOP_HITS,
         NAUGHT_CACHE_L2_SNOOP_PUSHES,
         NAUGHT_CACHE_STALLS_FOR_SNPQ_CYCLES
      );

      run_experiment
      (
         core_id,
         local_state,
         remote_state,
         operation,
         i,
         elements_count,
         results,
         4,
         NAUGHT_CACHE_EXTERNAL_SNOOP_REQUESTS,
         NAUGHT_CACHE_L2_RELOADS_FROM_CORENET,
         NAUGHT_CACHE_L2_SNOOPS_CAUSING_MINT,
         NAUGHT_CACHE_L2_SNOOPS_CAUSING_SINT
      );

      run_experiment
      (
         core_id,
         local_state,
         remote_state,
         operation,
         i,
         elements_count,
         results,
         8,
         NAUGHT_CPU_CYCLES,
         NAUGHT_CPU_CYCLES,
         NAUGHT_CPU_CYCLES,
         NAUGHT_CPU_CYCLES
      );

      elements_count += 1000;
   }
}
