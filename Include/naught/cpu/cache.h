#pragma once

#include <stdint.h>

#define NAUGHT_CACHE_STATE_MODIFIED    0
#define NAUGHT_CACHE_STATE_EXCLUSIVE   1
#define NAUGHT_CACHE_STATE_SHARED      2
#define NAUGHT_CACHE_STATE_INVALID     3
#define NAUGHT_CACHE_STATE_UNKNOWN     4

#define NAUGHT_CACHE_STATE_TRUE_SHARED NAUGHT_CACHE_STATE_UNKNOWN
#define NAUGHT_CACHE_STATE_FORWARD NAUGHT_CACHE_STATE_SHARED

#define NAUGHT_CACHE_L2_CSR0_AS_SPECIAL_REGISTER 0

/* Ref for these event IDs: e6500-reference-manual.pdf, p.523-535|548 */
#define NAUGHT_CACHE_L1_DATA_RELOADS                                       41
#define NAUGHT_CACHE_L1_INSTRUCTION_RELOADS_FROM_FETCH                     60
#define NAUGHT_CACHE_L1_DATA_STASH_HITS                                    97
#define NAUGHT_CACHE_L1_DATA_STASH_REQUESTS                                99
#define NAUGHT_CACHE_L1_DATA_MISSES                                        221
#define NAUGHT_CACHE_L1_DATA_LOAD_MISSES                                   222
#define NAUGHT_CACHE_L1_DATA_STORE_MISSES                                  223
#define NAUGHT_CACHE_L1_INSTRUCTION_MISSES                                 254

#define NAUGHT_CACHE_L2_HITS                                               456
#define NAUGHT_CACHE_L2_MISSES                                             457
#define NAUGHT_CACHE_L2_DEMAND_ACCESSES                                    458
#define NAUGHT_CACHE_L2_ACCESSES                                           459
#define NAUGHT_CACHE_L2_STORE_ALLOCATES                                    460
#define NAUGHT_CACHE_L2_INSTRUCTION_ACCESSES                               461
#define NAUGHT_CACHE_L2_DATA_ACCESSES                                      462
#define NAUGHT_CACHE_L2_INSTRUCTION_MISSES                                 463
#define NAUGHT_CACHE_L2_DATA_MISSES                                        464
#define NAUGHT_CACHE_L2_HITS_PER_THREAD                                    465
#define NAUGHT_CACHE_L2_MISSES_PER_THREAD                                  466
#define NAUGHT_CACHE_L2_DEMAND_ACCESSES_PER_THREAD                         467
#define NAUGHT_CACHE_L2_STORE_ALLOCATES_PER_THREAD                         468
#define NAUGHT_CACHE_L2_INSTRUCTION_ACCESSES_PER_THREAD                    469
#define NAUGHT_CACHE_L2_DATA_ACCESSES_PER_THREAD                           470
#define NAUGHT_CACHE_L2_INSTRUCTION_MISSES_PER_THREAD                      471
#define NAUGHT_CACHE_L2_DATA_MISSES_PER_THREAD                             472
#define NAUGHT_CACHE_L2_RELOADS_FROM_CORENET                               473
#define NAUGHT_CACHE_L2_STASH_REQUESTS                                     474
#define NAUGHT_CACHE_L2_STASH_REQUESTS_DOWNGRADED_TO_SNOOPS                475
#define NAUGHT_CACHE_L2_SNOOP_HITS                                         476
#define NAUGHT_CACHE_L2_SNOOPS_CAUSING_MINT                                477
#define NAUGHT_CACHE_L2_SNOOPS_CAUSING_SINT                                478
#define NAUGHT_CACHE_L2_SNOOP_PUSHES                                       479

#define NAUGHT_CACHE_STALLS_FOR_SNPQ_CYCLES                                494
#define NAUGHT_CACHE_EXTERNAL_SNOOP_REQUESTS                               511

/*
 * From e6500-reference-manual, p.315: a cache block or line is 16 words.
 * p.317: 64-byte (16-word) cache line, coherency-granule size
 * p.480: For 8-bit (byte) and 16-bit (half-word) writes
 */
#define NAUGHT_CACHE_BYTES_PER_WORD 8
#define NAUGHT_CACHE_WORDS_PER_LINE 16
#define NAUGHT_CACHE_LINE_SIZE \
	(NAUGHT_CACHE_BYTES_PER_WORD * NAUGHT_CACHE_WORDS_PER_LINE)
#define NAUGHT_CACHE_L1_HALF_SIZE 32768
#define NAUGHT_CACHE_L2_SIZE 2097152

typedef union __attribute__ ((aligned(NAUGHT_CACHE_LINE_SIZE)))
   {
      uint8_t byte[NAUGHT_CACHE_LINE_SIZE];
      uint16_t int16[NAUGHT_CACHE_LINE_SIZE/2];
      uint32_t int32[NAUGHT_CACHE_LINE_SIZE/4];
      uint64_t int64[NAUGHT_CACHE_LINE_SIZE/8];
   } naught_cache_line_t;

#if (NAUGHT_CACHE_L2_CSR0_AS_SPECIAL_REGISTER == 1)
void naught_cache_l2_enable_local (void);
#else
void naught_cache_l2_enable (const uint8_t cluster);
#endif

void naught_cache_l2_flush (const uint8_t cluster);

void naught_cache_l1_data_disable (void);
void naught_cache_l1_data_enable (void);
void naught_cache_l1_data_invalidate (void);

void naught_cache_l1_instruction_enable (void);
void naught_cache_l1_instruction_invalidate (void);


/* L1 is write-through, so flush = invalidate. */
#define naught_cache_l1_data_flush naught_cache_l1_data_invalidate
#define naught_cache_l1_instruction_flush naught_cache_l1_instruction_invalidate
