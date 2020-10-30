#include <stdint.h>

//#define NAUGHT_BREAK_CODE_WARRIOR_WITH_ZERO
#ifdef NAUGHT_BREAK_CODE_WARRIOR_WITH_ZERO
static int witness = 0;
#else
static int witness = 1000;
#endif

void naught_benchmark_break_code_warrior (uint8_t core_id)
{
   int i;

   if (core_id == 0)
   {
      witness = 2000;
   }

   witness += 1;

   switch (witness)
   {
      case 1000:
         i = 0;
         break;

      case 1001:
         i = 1;
         break;

      case 1002:
         i = 2;
         break;

      case 1003:
         i = 3;
         break;

      case 2000:
         i = 4;

      case 2001:
         i = 5;

      case 2002:
         i = 6;

      case 2003:
         i = 7;
         break;

      default:
         i = 100;
         break;
   }

   while (1) { i++; }
}
