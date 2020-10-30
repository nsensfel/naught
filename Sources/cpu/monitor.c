#include <naught/sane_assembly.h>
#include <naught/cpu/monitor.h>

#include <stdint.h>

/******************************************************************************/
/**** LOCAL FUNCTIONS *********************************************************/
/******************************************************************************/
static inline uint32_t enable_event_on_control_a
(
   const uint32_t event,
   const uint32_t current_value
)
{
   return
      (
         (current_value & ~NAUGHT_MONITOR_CONTROL_A_EVENT_MASK)
         | (event << NAUGHT_MONITOR_CONTROL_A_EVENT_SHIFT)
      );
}

/******************************************************************************/
/**** EXPORTED FUNCTIONS ******************************************************/
/******************************************************************************/
void naught_monitor_enable (const int privileged)
{
   /* Ref: EREF_RM.pdf, p.257 */
   MOVE_TO_PERFORMANCE_MONITOR_REGISTER
   (
      PMR_PMGC0,
      MOVE_FROM_PERFORMANCE_MONITOR_REGISTER(PMR_PMGC0) & ~PMGC0_FAC
   );
   /* Ref: e6500-reference-manual.pdf, p.186 ("mtpmr(all)") */
   INSTRUCTION_SYNCHRONIZE();
   /* Ref: EREF_RM.pdf, p.257. */
   if (privileged)
   {
      /* TODO: PMGC0_PMIE <- 1 */
   }
   else
   {
      /* TODO: UPMGC0_PMIE <- 1 */
   }
}
