#include <stdint.h>

#include <naught/sane_assembly.h>

#include <naught/kernel/barrier.h>

void naught_barrier_initialize
(
   naught_barrier_t b [const static 1],
   const uint32_t count
)
{
   /* I don't know how to differentiate a non-initialized barrier and one that is
    * currently in use.
    */
   *b = count;
}

void naught_barrier_join (naught_barrier_t b [const static 1])
{
   register uint32_t reg;
   register uint32_t reg_condition_register;

   for (;;)
   {
      asm volatile
      (
         ASM_LOAD_WORD_AND_RESERVE_INDEXED " %[buffer], 0, %[barrier_addr]\n"
         : [buffer] "=r" (reg)
         : [barrier_addr] "r" (b)
         : "memory"
      );

      if (reg == 0)
      {
         return;
      }

      reg -= 1;

      asm volatile
      (
         ASM_STORE_WORD_CONDITIONAL_INDEXED " %[buffer], 0, %[barrier_addr]\n"
         ASM_MOVE_FROM_CONDITION_REGISTER " %[condition_register]\n"
         : [buffer] "+r" (reg),
            [condition_register] "=r" (reg_condition_register)
         : [barrier_addr] "r" (b)
         : "memory"
      );

      /*
       * STORE_WORD_CONDITIONAL_INDEXED sets the prefix of Condition Register
       * Field 0 to 0b001 on a successful write, so we should test against:
       * 0010 0000 0000 0000 0000
       */
      if (reg_condition_register & 0x20000000)
      {
         break;
      }
   }

   while ((*b) != 0)
   {
   }
}
