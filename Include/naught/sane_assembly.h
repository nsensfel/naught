#pragma once

#include <stdint.h>

#include <naught/macro_utils.h>

#define __NAUGHT_VALUE_FROM_REGISTER(type, cmd, reg) \
   ({ \
      type result;\
      \
      asm volatile(cmd " %0," NAUGHT_STRINGIFY_VALUE(reg) : "=r" (result)); \
      \
      result; \
   })

#define __NAUGHT_VALUE_TO_REGISTER(cmd, reg, val) \
   asm volatile(cmd " " NAUGHT_STRINGIFY_VALUE(reg)",%0" : : "r" (val))

#define MOVE_FROM_PERFORMANCE_MONITOR_REGISTER(reg) \
   __NAUGHT_VALUE_FROM_REGISTER(uint32_t, "mfpmr", reg)

#define MOVE_FROM_SPECIAL_PURPOSE_REGISTER(reg) \
   __NAUGHT_VALUE_FROM_REGISTER(uint32_t, "mfspr", reg)

#define MOVE_FROM_MACHINE_STATE_REGISTER(reg) \
   __NAUGHT_VALUE_FROM_REGISTER(uint32_t, "mfmsr", reg)

#define MOVE_TO_PERFORMANCE_MONITOR_REGISTER(reg, val) \
   __NAUGHT_VALUE_TO_REGISTER("mtpmr", reg, val)

#define MOVE_TO_SPECIAL_PURPOSE_REGISTER(reg, val) \
   __NAUGHT_VALUE_TO_REGISTER("mtspr", reg, val)

#define MOVE_TO_MACHINE_STATE_REGISTER(val) \
	asm volatile("mtmsr %0" : : "r" (val))

#define INSTRUCTION_SYNCHRONIZE() asm volatile("isync" : : : "memory")

#define SYNCHRONIZE() asm volatile("msync" : : : "memory")
#define MEMORY_SYNCHRONIZE() SYNCHRONIZE()

#define ASM_DATA_CACHE_BLOCK_FLUSH "dcbf"
#define ASM_DATA_CACHE_BLOCK_INVALIDATE "dcbi"
#define ASM_LOAD_WORD_AND_RESERVE_INDEXED "lwarx"
#define ASM_LOAD_WORD_AND_ZERO "lwz"
#define ASM_STORE_WORD "stw"
#define ASM_STORE_WORD_CONDITIONAL_INDEXED "stwcx."
#define ASM_MOVE_FROM_CONDITION_REGISTER "mfcr"

#define ASM_REAL_ADDRESS_COMPUTE "rac"
#define ASM_CACHE_LINE_FLUSH "clf"

