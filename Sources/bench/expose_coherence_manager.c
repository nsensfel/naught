#include <naught/cpu/cache.h>

#include <naught/benchmarks.h>

/******************************************************************************/
/**** LOCAL FUNCTIONS *********************************************************/
/******************************************************************************/

/******************************************************************************/
/**** EXPORTED FUNCTIONS ******************************************************/
/******************************************************************************/
void naught_benchmark_expose_coherence_manager
(
   const uint8_t core_id,
   const uint8_t core_ix
)
{
   const int core_a_state = NAUGHT_CACHE_STATE_TRUE_SHARED;
   const int core_b_state = NAUGHT_CACHE_STATE_TRUE_SHARED;
   const int core_c_state = NAUGHT_CACHE_STATE_FORWARD;
   const int core_states[3] = {core_a_state, core_b_state, core_c_state};

   naught_benchmark_meta_three_ways_reach_states
   (
      core_id,
      core_ix,
      core_states,
      8000
   );

   const int core_a_stateb = NAUGHT_CACHE_STATE_EXCLUSIVE;
   const int core_b_stateb = NAUGHT_CACHE_STATE_INVALID;
   const int core_c_stateb = NAUGHT_CACHE_STATE_INVALID;
   const int core_statesb[3] = {core_a_stateb, core_b_stateb, core_c_stateb};

   naught_benchmark_meta_three_ways_reach_states
   (
      core_id,
      core_ix,
      core_statesb,
      8000
   );
}
