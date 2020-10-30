#include <naught/benchmarks.h>

#include <naught/cpu/cache.h>

#include <naught/kernel/mutex.h>

#include <naught/sane_assembly.h>

#include <stdint.h>

/******************************************************************************/
/**** LOCAL FUNCTIONS *********************************************************/
/******************************************************************************/
static inline void clear_caches (const uint8_t core_id)
{
   naught_cache_l1_data_invalidate();
   naught_cache_l2_flush(core_id % 4);
}

static inline void asm_store_test (const uint8_t core_id, const int runs)
{
   int i, j;

   j = 0;

   for (i = 0; i < runs; ++i)
   {
      if (j == __NAUGHT_SHARED_ELEMENTS_COUNT)
      {
         j = 0;
      }

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

static inline void asm_load_test (const uint8_t core_id, const int runs)
{
   register int i, j;
   register uint32_t buffer;

   j = 0;

   for (i = 0; i < runs; ++i)
   {

      asm volatile
      (
         ASM_LOAD_WORD_AND_ZERO " %[buffer], 0 (%[line_addr])\n"
         : [buffer] "=r" (buffer)
         : [line_addr] "r" (naught_shared_elements + j)
         : "memory"
      );

      j++;
   }
}

static uint8_t step = 0;
static naught_mutex_t mutex;

/******************************************************************************/
/**** EXPORTED FUNCTIONS ******************************************************/
/******************************************************************************/
void naught_benchmark_modified_upon_gets
(
   const uint8_t core_id,
   const int role
)
{
   int ops_per_run;

   ops_per_run = 1000;

   switch (role)
   {
      case 0:
         naught_mutex_initialize(&mutex);

         naught_mutex_lock(core_id, &mutex);

         step = 1;

         asm_store_test(core_id, ops_per_run);
         naught_mutex_unlock(core_id, &mutex);

         break;

      case 1:
         while (step == 0)
         {
         }

         naught_mutex_lock(core_id, &mutex);
         asm_load_test(core_id, ops_per_run);
         naught_mutex_unlock(core_id, &mutex);

         break;
   }
}
