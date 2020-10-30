#include <stdint.h>

#include <naught/sane_assembly.h>

#include <naught/kernel/mutex.h>

void naught_mutex_initialize (naught_mutex_t m [const static 1])
{
   /* I don't know how to differentiate a non-initialized mutex and one that is
    * currently in use.
    */
   *m = 0;
}

void naught_mutex_lock
(
   const uint8_t core_id,
   naught_mutex_t m [const static 1]
)
{
   register uint32_t reg;
   register uint32_t reg_condition_register;

   for (;;)
   {
      asm volatile
      (
         ASM_LOAD_WORD_AND_RESERVE_INDEXED " %[buffer], 0, %[mutex_addr]\n"
         : [buffer] "=r" (reg)
         : [mutex_addr] "r" (m)
         : "memory"
      );

      if (reg == 0)
      {
         reg = (core_id + 1);

         asm volatile
         (
            ASM_STORE_WORD_CONDITIONAL_INDEXED " %[buffer], 0, %[mutex_addr]\n"
            ASM_MOVE_FROM_CONDITION_REGISTER " %[condition_register]\n"
            : [buffer] "+r" (reg),
               [condition_register] "=r" (reg_condition_register)
            : [mutex_addr] "r" (m)
            : "memory"
         );

         /*
          * STORE_WORD_CONDITIONAL_INDEXED sets the prefix of Condition Register
          * Field 0 to 0b001 on a successful write, so we should test against:
          * 0010 0000 0000 0000 0000
          */
         if (reg_condition_register & 0x20000000)
         {
            return;
         }
      }

      // TODO: pause for a bit?
   }
}

void naught_mutex_unlock
(
   const uint8_t core_id,
   naught_mutex_t m [const static 1]
)
{
   if (*m == (core_id + 1))
   {
      *m = 0;
   }
}
