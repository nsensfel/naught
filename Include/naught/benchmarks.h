#pragma once

#include <naught/cpu/cache.h>

#include <stdint.h>

#define NAUGHT_INSTRUCTION_LOAD  0
#define NAUGHT_INSTRUCTION_STORE 1
#define NAUGHT_INSTRUCTION_EVICT 2
#define NAUGHT_INSTRUCTION_NOP   3
#define NAUGHT_INSTRUCTION_LOAD_W_OFFSET  4
#define NAUGHT_INSTRUCTION_STORE_W_OFFSET 5

void naught_benchmark_demo0 (const uint8_t core_id);
void naught_benchmark_demo1 (const uint8_t core_id);
void naught_benchmark_demo1_desync (const uint8_t core_id);
void naught_benchmark_baseline (const uint8_t core_id);

void naught_benchmark_no_missing_mechanic
(
   const uint8_t core_id,
   const int instruction
);

void naught_benchmark_exclusive_free_upgrade (const uint8_t core_id);

void naught_benchmark_exclusive_vs_shared
(
   const uint8_t core_id,
   const int role
);

void naught_benchmark_exclusive_no_free_lunch
(
   const uint8_t core_id,
   const int role
);

void naught_benchmark_break_code_warrior (const uint8_t core_id);

void naught_benchmark_modified_upon_gets
(
   const uint8_t core_id,
   const int role
);

void naught_benchmark_shared_to_exclusive
(
   const uint8_t core_id,
   const int role
);

void naught_benchmark_crossfires
(
   const uint8_t core_id,
   const int role,
   const int element
);

void naught_benchmark_omnibenchs
(
   const uint8_t core_id,
   const int local_state,
   const int remote_state,
   const int operation
);

void naught_benchmark_three_ways_omnibenchs
(
   const uint8_t core_id,
   const int state_ix,
   const int target_state [const restrict static 3],
   const int operation
);

void naught_benchmark_expose_coherence_manager
(
   const uint8_t core_id,
   const uint8_t core_ix
);

/******************************************************************************/
/**** CACHE MANAGEMENT ********************************************************/
/******************************************************************************/
void naught_benchmark_meta_reset_caches (const uint8_t core_id);

/******************************************************************************/
/**** MONITOR MANAGEMENT ******************************************************/
/******************************************************************************/
void naught_benchmark_meta_start_monitor
(
   const int event_0,
   const int event_1,
   const int event_2,
   const int event_3
);

void naught_benchmark_meta_freeze_monitors (void);
void naught_benchmark_meta_resume_monitors (void);

void naught_benchmark_meta_print_monitor_results
(
   const uint8_t core_id,
   const uint32_t results[const restrict static 1],
   const int run_id
);

void naught_benchmark_meta_print_offset_monitor_results
(
   const uint8_t core_id,
   const uint32_t results[const restrict static 1],
   const int run_id,
   const int array_offset,
   const int print_offset
);

void naught_benchmark_meta_store_monitor_results
(
   uint32_t results[const restrict static 1],
   int run_id
);

/******************************************************************************/
/**** OPERATIONS **************************************************************/
/******************************************************************************/
void naught_benchmark_meta_read_elements (const int elements_count);
void naught_benchmark_meta_write_elements (const int elements_count);
void naught_benchmark_meta_read_elements_offset
(
   const int elements_count,
   const int offset
);
void naught_benchmark_meta_write_elements_offset
(
   const int elements_count,
   const int offset
);

/*
 * Not available because I can't actually evict a single local line. Empty the
 * whole cache instead by using naught_benchmark_meta_reset_caches.
 * dcb{i,f} -> invalidates/flushes both the local *and* all remote copies.
 */
//void naught_benchmark_meta_evict_elements (const int elements_count);

/******************************************************************************/
/**** REACH STATE *************************************************************/
/******************************************************************************/
void naught_benchmark_meta_reach_states
(
   const uint8_t core_id,
   const int own_target_state,
   const int other_target_state,
   const int elements_count
);

void naught_benchmark_meta_three_ways_reach_states
(
   const uint8_t core_id,
   const int state_ix,
   const int target_state [const restrict static 3],
   const int elements_count
);

#define __NAUGHT_SHARED_ELEMENTS_COUNT 22000
naught_cache_line_t naught_shared_elements[__NAUGHT_SHARED_ELEMENTS_COUNT];
