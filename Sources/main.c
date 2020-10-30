//////////////////////////
//   Project Stationery  //
//////////////////////////

#include <stdio.h>
#include <stdint.h>

#include <naught/benchmarks.h>

#include <naught/cpu/cache.h>

typedef void (IntHndlr)(long);
extern void InterruptHandler(long cause);
#if SMPTARGET
   #include "smp_target.h"
#endif

int main()
{
   /*
   Because the interrupt vector code is shared, each thread needs to register
   its own InterruptHandeler routine in SPRG0 (SPR 272)
   *//*
   register IntHndlr* isr = InterruptHandler;
   asm("mtspr 272, %0" : : "r" (isr));
         */
   int i=0;

   unsigned long proc_id;

   asm ("mfpir %0" : "=r" (proc_id));

#if SMPTARGET
   initSmp();
#endif

   //naught_benchmark_break_code_warrior((uint8_t) proc_id);

   naught_cache_l1_instruction_enable();
   //naught_cache_l1_data_enable();
   const int core_a_state = NAUGHT_CACHE_STATE_INVALID;
   const int core_b_state = NAUGHT_CACHE_STATE_INVALID;
   const int core_c_state = NAUGHT_CACHE_STATE_INVALID;

   const int core_states[3] = {core_a_state, core_b_state, core_c_state};

   const int core_a_operation = NAUGHT_INSTRUCTION_LOAD;
   const int core_b_operation = NAUGHT_INSTRUCTION_NOP;
   const int core_c_operation = NAUGHT_INSTRUCTION_NOP;

#ifdef NAUGHT_UNrrrrDEF
   if (proc_id == 0)
   {
	   naught_benchmark_three_ways_omnibenchs
	   (
		  (uint8_t) proc_id,
		  0,
		  core_states,
		  core_a_operation
	   );

   }
   else if (proc_id < 60)
   {
	   naught_benchmark_three_ways_omnibenchs
	   (
		  (uint8_t) proc_id,
		  1,
		  core_states,
		  core_b_operation
	   );
   }
   else
   {
	   naught_benchmark_three_ways_omnibenchs
	   (
		  (uint8_t) proc_id,
		  2,
		  core_states,
		  core_c_operation
	   );
   }
#else

#endif
   if (proc_id == 0) {naught_benchmark_expose_coherence_manager((uint8_t) proc_id, 0);}
   else if (proc_id < 60) {naught_benchmark_expose_coherence_manager((uint8_t) proc_id, 1);}
   else {naught_benchmark_expose_coherence_manager((uint8_t) proc_id, 2);}
   //printf("Core%lu-Thread%lu: Welcome to CodeWarrior!\r\n", proc_id >> 3, proc_id % 8);
   //asm("sc"); // generate a system call exception to demonstrate the ISR


   while (1) { i++; } // loop forever
}

