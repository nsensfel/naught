#pragma once

#include <stdint.h>

#include <nxp/powerpc/registers.h>

#include <naught/sane_assembly.h>

/*
 * Ref for the values: e6500-reference-manual.pdf, p.171,
 * "Performance monitor registers."
 * Ref for what this is: EREF_RM.pdf, p.260 "Performance Monitor Counter
 * Registers (PMCn/UPMCn)."
 */
#define NAUGHT_MONITOR_USER_COUNTER_0                             PMR_UPMC0 // 0
#define NAUGHT_MONITOR_USER_COUNTER_1                             PMR_UPMC1 // 1
#define NAUGHT_MONITOR_USER_COUNTER_2                             PMR_UPMC2 // 2
#define NAUGHT_MONITOR_USER_COUNTER_3                             PMR_UPMC3 // 3

#ifdef PMR_UPMC4
#define NAUGHT_MONITOR_USER_COUNTER_4                             PMR_UPMC4 // 4
#endif
#ifdef PMR_UPMC5
#define NAUGHT_MONITOR_USER_COUNTER_5                             PMR_UPMC5 // 5
#endif

#define NAUGHT_MONITOR_COUNTER_0                                  PMR_PMC0 // 16
#define NAUGHT_MONITOR_COUNTER_1                                  PMR_PMC1 // 17
#define NAUGHT_MONITOR_COUNTER_2                                  PMR_PMC2 // 18
#define NAUGHT_MONITOR_COUNTER_3                                  PMR_PMC3 // 19

#ifdef PMR_PMC4
#define NAUGHT_MONITOR_COUNTER_4                                  PMR_PMC4 // 20
#endif
#ifdef PMR_PMC5
#define NAUGHT_MONITOR_COUNTER_5                                  PMR_PMC5 // 21
#endif

#define NAUGHT_MONITOR_GLOBAL_CONTROL                          PMR_PMGC0 // 400

/*
 * Ref value: e6500-reference-manual.pdf, p.171.
 * Ref content: e6500-reference-manual.pdf, p.173, "Local control A registers."
 */
#define NAUGHT_MONITOR_USER_COUNTER_0_CONTROL_A             PMR_UPMLCA0 // 128
#define NAUGHT_MONITOR_USER_COUNTER_1_CONTROL_A             PMR_UPMLCA1 // 129
#define NAUGHT_MONITOR_USER_COUNTER_2_CONTROL_A             PMR_UPMLCA2 // 130
#define NAUGHT_MONITOR_USER_COUNTER_3_CONTROL_A             PMR_UPMLCA3 // 131

#ifdef PMR_UPMLCA4
#define NAUGHT_MONITOR_USER_COUNTER_4_CONTROL_A             PMR_UPMLCA4 // 132
#endif
#ifdef PMR_UPMLCA5
#define NAUGHT_MONITOR_USER_COUNTER_5_CONTROL_A             PMR_UPMLCA5 // 133
#endif

#define NAUGHT_MONITOR_COUNTER_0_CONTROL_A                     PMR_PMLCA0 // 144
#define NAUGHT_MONITOR_COUNTER_1_CONTROL_A                     PMR_PMLCA1 // 145
#define NAUGHT_MONITOR_COUNTER_2_CONTROL_A                     PMR_PMLCA2 // 146
#define NAUGHT_MONITOR_COUNTER_3_CONTROL_A                     PMR_PMLCA3 // 147

#ifdef PMR_UPMLCA4
#define NAUGHT_MONITOR_COUNTER_4_CONTROL_A                     PMR_PMLCA4 // 148
#endif
#ifdef PMR_UPMLCA4
#define NAUGHT_MONITOR_COUNTER_5_CONTROL_A                     PMR_PMLCA5 // 149
#endif

/*
 * Ref: e6500-reference-manual.pdf, p.173, "Local control A registers."
 * Writes to the CONTROL_A register change the values on bits 32 to 63.
 * We write 32 bits. Bits for the Event ID: 39-47.
 * 0000 0001 1111 1111 0000 0000 0000 0000
 * In hexa: 0x01ff0000
 */
#define NAUGHT_MONITOR_CONTROL_A_EVENT_MASK 0x01ff0000
/* Shift the event to the correct bits. */
#define NAUGHT_MONITOR_CONTROL_A_EVENT_SHIFT 16

/* 1000 0000 0000 0000 0000 0000 0000 0000 */
#define NAUGHT_MONITOR_CONTROL_A_FREEZE_COUNTER 0x80000000

#define naught_monitor_counter_initialize(counter, event)                      \
   MOVE_TO_PERFORMANCE_MONITOR_REGISTER                                        \
   (                                                                           \
      (counter ## _CONTROL_A),                                                 \
      (                                                                        \
         (                                                                     \
            (                                                                  \
               MOVE_FROM_PERFORMANCE_MONITOR_REGISTER(counter ## _CONTROL_A)   \
               & ~NAUGHT_MONITOR_CONTROL_A_EVENT_MASK                          \
            )                                                                  \
            | (event << NAUGHT_MONITOR_CONTROL_A_EVENT_SHIFT)                  \
         )                                                                     \
      )                                                                        \
   );                                                                          \
   MOVE_TO_PERFORMANCE_MONITOR_REGISTER(counter, 0)

#define naught_monitor_counter_read(counter) \
   MOVE_FROM_PERFORMANCE_MONITOR_REGISTER(counter)

#define naught_monitor_counter_freeze(counter)                                 \
   MOVE_TO_PERFORMANCE_MONITOR_REGISTER                                        \
   (                                                                           \
      (counter ## _CONTROL_A),                                                 \
      (                                                                        \
         MOVE_FROM_PERFORMANCE_MONITOR_REGISTER(counter ## _CONTROL_A)         \
         | NAUGHT_MONITOR_CONTROL_A_FREEZE_COUNTER                             \
      )                                                                        \
   );                                                                          \

#define naught_monitor_counter_resume(counter)                                 \
   MOVE_TO_PERFORMANCE_MONITOR_REGISTER                                        \
   (                                                                           \
      (counter ## _CONTROL_A),                                                 \
      (                                                                        \
         MOVE_FROM_PERFORMANCE_MONITOR_REGISTER(counter ## _CONTROL_A)         \
         & ~NAUGHT_MONITOR_CONTROL_A_FREEZE_COUNTER                            \
      )                                                                        \
   );                                                                          \

void naught_monitor_enable (const int privileged);
