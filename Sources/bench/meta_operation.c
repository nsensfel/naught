#include <stdint.h>

#include <naught/benchmarks.h>
#include <naught/sane_assembly.h>

void naught_benchmark_meta_read_elements (const int elements_count)
{
   register int i;
   register uint32_t buffer;

   for (i = 0; i < elements_count; ++i)
   {
      asm volatile
      (
         ASM_LOAD_WORD_AND_ZERO " %[buffer], 0 (%[line_addr])\n"
         : [buffer] "=r" (buffer)
         : [line_addr] "r" (naught_shared_elements + i)
         : "memory"
      );
   }
}

void naught_benchmark_meta_write_elements (const int elements_count)
{
   register int i;

   for (i = 0; i < elements_count; ++i)
   {
      asm volatile
      (
         ASM_STORE_WORD " %[stored_val], 0 (%[line_addr])\n"
         :
         : [line_addr] "r" (naught_shared_elements + i),
            [stored_val] "i" (0)
         : "memory"
      );
   }
}

void naught_benchmark_meta_evict_elements (const int elements_count)
{
   register int i;

   for (i = 0; i < elements_count; ++i)
   {
      asm volatile
      (
         ASM_DATA_CACHE_BLOCK_INVALIDATE " 0, %[line_addr]\n"
         :
         : [line_addr] "r" (naught_shared_elements + i)
         : "memory"
      );
   }
}

void naught_benchmark_meta_read_elements_offset
(
   const int elements_count,
   const int offset
)
{
   register int i;
   register uint32_t buffer;

   for (i = 0; i < elements_count; ++i)
   {
      asm volatile
      (
         ASM_LOAD_WORD_AND_ZERO " %[buffer], 0 (%[line_addr])\n"
         : [buffer] "=r" (buffer)
         : [line_addr] "r" (&(naught_shared_elements[i].int32[offset]))
         : "memory"
      );
   }
}

void naught_benchmark_meta_write_elements_offset
(
   const int elements_count,
   const int offset
)
{
   register int i;

   for (i = 0; i < elements_count; ++i)
   {
      asm volatile
      (
         ASM_STORE_WORD " %[stored_val], 0 (%[line_addr])\n"
         :
         : [line_addr] "r" (&(naught_shared_elements[i].int32[offset])),
            [stored_val] "i" (0)
         : "memory"
      );
   }
}
