#include <naught/cpu/cache.h>

#include <naught/kernel/barrier.h>

#include <naught/benchmarks.h>

#include <stdint.h>

#define __NAUGHT_CORE_COUNTS 3
#define __NAUGHT_EVENT_0 NAUGHT_CPU_CYCLES
#define __NAUGHT_EVENT_1 NAUGHT_CACHE_L2_SNOOPS_CAUSING_MINT
#define __NAUGHT_EVENT_2 NAUGHT_CACHE_L2_SNOOPS_CAUSING_SINT
#define __NAUGHT_EVENT_3 NAUGHT_CACHE_L2_DATA_ACCESSES

static naught_barrier_t start_of_fun_barrier = \
   NAUGHT_BARRIER_INITIALIZED(__NAUGHT_CORE_COUNTS);
static naught_barrier_t caches_reset_barrier = \
   NAUGHT_BARRIER_INITIALIZED(__NAUGHT_CORE_COUNTS);
static naught_barrier_t end_of_fun_barrier;
static naught_barrier_t cleanup_barrier;

static naught_barrier_t intermittent_barrier_a = \
   NAUGHT_BARRIER_INITIALIZED(__NAUGHT_CORE_COUNTS);

static naught_barrier_t intermittent_barrier_b = \
   NAUGHT_BARRIER_INITIALIZED(__NAUGHT_CORE_COUNTS);

/******************************************************************************/
/**** LOCAL FUNCTIONS *********************************************************/
/******************************************************************************/

static inline int mod (const int a, const int b)
{
    int r = (a % b);

    return (r < 0) ? (r + b) : r;
}

static int left_index (const int index)
{
   return mod((index - 1), __NAUGHT_CORE_COUNTS);
}

static int right_index (const int index)
{
   return ((index + 1) % __NAUGHT_CORE_COUNTS);
}

static void reset_all_intermittent_barriers (void)
{
   naught_barrier_initialize(&start_of_fun_barrier, __NAUGHT_CORE_COUNTS);
   naught_barrier_initialize(&caches_reset_barrier, __NAUGHT_CORE_COUNTS);

   naught_barrier_initialize(&intermittent_barrier_a, __NAUGHT_CORE_COUNTS);
   naught_barrier_initialize(&intermittent_barrier_b, __NAUGHT_CORE_COUNTS);
}


static void handle_own_state_modified
(
   const uint8_t core_id,
   const int state_ix,
   const int target_state [const restrict static __NAUGHT_CORE_COUNTS],
   const int elements_count
)
{
   // left_target_state == NAUGHT_CACHE_STATE_INVALID
   // right_target_state == NAUGHT_CACHE_STATE_INVALID
   naught_benchmark_meta_write_elements(elements_count);
   naught_barrier_join(&intermittent_barrier_a);
   naught_barrier_join(&intermittent_barrier_b);
}

static void handle_own_state_exclusive
(
   const uint8_t core_id,
   const int state_ix,
   const int target_state [const restrict static __NAUGHT_CORE_COUNTS],
   const int elements_count
)
{
   // left_target_state == NAUGHT_CACHE_STATE_INVALID
   // right_target_state == NAUGHT_CACHE_STATE_INVALID
   naught_benchmark_meta_read_elements(elements_count);
   naught_barrier_join(&intermittent_barrier_a);
   naught_barrier_join(&intermittent_barrier_b);
}

static void handle_own_state_shared
(
   const uint8_t core_id,
   const int state_ix,
   const int target_state [const restrict static __NAUGHT_CORE_COUNTS],
   const int elements_count
)
{

   // Load the values, the state on our right will also load them.
   naught_barrier_join(&intermittent_barrier_a);
   naught_benchmark_meta_read_elements(elements_count);
   naught_barrier_join(&intermittent_barrier_b);
}

static void handle_own_state_unknown
(
   const uint8_t core_id,
   const int state_ix,
   const int target_state [const restrict static __NAUGHT_CORE_COUNTS],
   const int elements_count
)
{

   // Load the values, the state on our right will also load them.
   naught_benchmark_meta_read_elements(elements_count);
   naught_barrier_join(&intermittent_barrier_a);
   naught_barrier_join(&intermittent_barrier_b);
}

static void handle_own_state_invalid
(
   const uint8_t core_id,
   const int state_ix,
   const int target_state [const restrict static __NAUGHT_CORE_COUNTS],
   const int elements_count
)
{
   switch (target_state[left_index(state_ix)])
   {
      case NAUGHT_CACHE_STATE_MODIFIED:
         naught_barrier_join(&intermittent_barrier_a);
  	 naught_barrier_join(&intermittent_barrier_b);
         // Nothing to do.
         break;

      case NAUGHT_CACHE_STATE_EXCLUSIVE:
         naught_barrier_join(&intermittent_barrier_a);
   	 naught_barrier_join(&intermittent_barrier_b);
         // Nothing to do.
         break;

      case NAUGHT_CACHE_STATE_UNKNOWN:
         naught_barrier_join(&intermittent_barrier_a);
         naught_benchmark_meta_read_elements(elements_count);
   	 naught_barrier_join(&intermittent_barrier_b);
         naught_benchmark_meta_reset_caches(core_id);
         break;

      case NAUGHT_CACHE_STATE_SHARED:
         naught_benchmark_meta_read_elements(elements_count);
         naught_barrier_join(&intermittent_barrier_a);
   	 naught_barrier_join(&intermittent_barrier_b);
         naught_benchmark_meta_reset_caches(core_id);
         break;

      case NAUGHT_CACHE_STATE_INVALID:
         naught_barrier_join(&intermittent_barrier_a);
   	 naught_barrier_join(&intermittent_barrier_b);
         // Nothing to do.
         break;
   }
}

/******************************************************************************/
/**** EXPORTED FUNCTIONS ******************************************************/
/******************************************************************************/
void naught_benchmark_meta_three_ways_reach_states
(
   const uint8_t core_id,
   const int state_ix,
   const int target_state [const restrict static __NAUGHT_CORE_COUNTS],
   const int elements_count
)
{
   if (core_id == 0)
   {
      naught_barrier_initialize(&cleanup_barrier, __NAUGHT_CORE_COUNTS);
      naught_barrier_initialize(&end_of_fun_barrier, __NAUGHT_CORE_COUNTS);
   }

   naught_barrier_join(&start_of_fun_barrier);

   naught_benchmark_meta_reset_caches(core_id);

   naught_barrier_join(&caches_reset_barrier);

   switch (target_state[state_ix])
   {
      case NAUGHT_CACHE_STATE_MODIFIED:
         handle_own_state_modified
         (
            core_id,
            state_ix,
            target_state,
            elements_count
         );
         break;

      case NAUGHT_CACHE_STATE_EXCLUSIVE:
         handle_own_state_exclusive
         (
            core_id,
            state_ix,
            target_state,
            elements_count
         );
         break;

      case NAUGHT_CACHE_STATE_SHARED:
         handle_own_state_shared
         (
            core_id,
            state_ix,
            target_state,
            elements_count
         );
         break;

      case NAUGHT_CACHE_STATE_INVALID:
         handle_own_state_invalid
         (
            core_id,
            state_ix,
            target_state,
            elements_count
         );
         break;

      case NAUGHT_CACHE_STATE_UNKNOWN:
         handle_own_state_unknown
         (
            core_id,
            state_ix,
            target_state,
            elements_count
         );
         break;
   }

   naught_barrier_join(&cleanup_barrier);

   if (core_id == 0)
   {
      reset_all_intermittent_barriers();
   }

   naught_barrier_join(&end_of_fun_barrier);
}
