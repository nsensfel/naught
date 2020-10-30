#include <nxp/powerpc/registers.h>

#include <naught/sane_assembly.h>

void naught_prediction_branch_disable (void)
{
   /* e6500-reference-manual.pdf, p.81 */
   MOVE_TO_SPECIAL_PURPOSE_REGISTER
   (
      SPR_BUCSR,
      (
         MOVE_FROM_SPECIAL_PURPOSE_REGISTER(SPR_BUCSR)
         & ~BUCSR_BPEN
      )
   );

   /*
    * Reference for the required synchronization:
    * e6500-reference-manual.pdf, p.188
    */
   INSTRUCTION_SYNCHRONIZE();
}
