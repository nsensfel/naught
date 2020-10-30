//#include <misc/misc.h>

#include <stdint.h>

#include <naught/benchmarks.h>

void naught_benchmark_demo1_desync (const uint8_t core_id)
{
   if ((core_id % 8) != 0)
   {
      return;
   }

//   sleep(core_id * 2);
   naught_benchmark_baseline(core_id);
}

void naught_benchmark_demo1 (const uint8_t core_id)
{
   if ((core_id % 8) != 0)
   {
      return;
   }

   naught_benchmark_baseline(core_id);
}
