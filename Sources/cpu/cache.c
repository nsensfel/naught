#include <stdint.h>

#include <nxp/powerpc/registers.h>

#include <naught/config.h>
#include <naught/sane_assembly.h>
#include <naught/cpu/cache.h>
/*
 *        Flush: write back data then invalidate.
 *        Invalidate: invalidate all, lose changes.
 */
void naught_cache_l2_flush (const uint8_t cluster)
{
   /*
    * Inspired from "arch/core_init.c", "enable_cache(uint32_t)".
    * Follows e6500-reference-manual.pdf, p.106, L2FL.
    */
   volatile uint32_t * l2csr0_va;
   volatile uint32_t * l2par0_va;
   volatile uint32_t * l2par1_va;
   volatile uint32_t * l2par2_va;
   volatile uint32_t * l2par3_va;
#ifdef NAUGHT_GO_OVERBOARD
   volatile uint32_t * l2par4_va;
   volatile uint32_t * l2par5_va;
   volatile uint32_t * l2par6_va;
   volatile uint32_t * l2par7_va;
#endif

   switch (cluster)
   {
      case 0:
         l2csr0_va =
            (uint32_t *) (NAUGHT_CONFIG_TLB_CCSRBAR_ADDR + MMR_L2REG(C1, CSR0));
         break;

      case 1:
         l2csr0_va =
            (uint32_t *) (NAUGHT_CONFIG_TLB_CCSRBAR_ADDR + MMR_L2REG(C2, CSR0));
         break;

      case 2:
         l2csr0_va =
            (uint32_t *) (NAUGHT_CONFIG_TLB_CCSRBAR_ADDR + MMR_L2REG(C3, CSR0));
         break;

      default:
         return;
   }

   l2par0_va = (uint32_t *) (l2csr0_va + MMR_L2PAR0_OFFSET);
   l2par1_va = (uint32_t *) (l2csr0_va + MMR_L2PAR1_OFFSET);
   l2par2_va = (uint32_t *) (l2csr0_va + MMR_L2PAR2_OFFSET);
   l2par3_va = (uint32_t *) (l2csr0_va + MMR_L2PAR3_OFFSET);

   /*
    * "Clear all the bits of L2PAR0 - L2PAR3 to prevent further allocations."
    * I assume this extends to to L2PAR7.
    */
   *l2par0_va = 0;
   *l2par1_va = 0;
   *l2par2_va = 0;
   *l2par3_va = 0;

   /*
    * (
    *    e6500-reference-manual.pdf, p.111:
    *    "Writing to these registers requires synchronization"
    * )
    */
   INSTRUCTION_SYNCHRONIZE();

   /*
    * "Read L2PAR0 - L2PAR3 to ensure that the changes are in effect."
    * I assume this extends to to L2PAR7.
    */
   while
   (
      (*l2par3_va)
      || (*l2par2_va)
      || (*l2par1_va)
      || (*l2par0_va)
   )
   {
   }

   /* "Write 1 to L2CSR0[L2FL]." */
   *l2csr0_va |= L2CSR0_L2FL;

   /* "Continue to read L2CSR0[L2FL] until it reads 0." */
   while ((*l2csr0_va) & L2CSR0_L2FL)
   {
   }

   /* Ref: e6500-reference-manual.pdf, p.345 "and then perform an isync." */
   INSTRUCTION_SYNCHRONIZE();
}

void naught_cache_l1_data_invalidate (void)
{
   /* e6500-reference-manual.pdf, p.334, "L1 cache flash invalidation" */
   /* Sync requirements from: e6500-reference-manual.pdf, p.186 */
   MEMORY_SYNCHRONIZE();
   INSTRUCTION_SYNCHRONIZE();
   MOVE_TO_SPECIAL_PURPOSE_REGISTER
   (
      SPR_L1CSR0,
      (MOVE_FROM_SPECIAL_PURPOSE_REGISTER(SPR_L1CSR0) | L1CSR0_DCFI)
   );
   INSTRUCTION_SYNCHRONIZE();


   MEMORY_SYNCHRONIZE();
   /* "CFI flags are not sticky", so we wait until it is no longer set. */
   while
   (
      (MOVE_FROM_SPECIAL_PURPOSE_REGISTER(SPR_L1CSR0) & L1CSR0_DCFI)
      == L1CSR0_DCFI
   )
   {
      MEMORY_SYNCHRONIZE();
   }
}

void naught_cache_l1_instruction_invalidate (void)
{
   /* Sync requirements from: e6500-reference-manual.pdf, p.186 */
   /* e6500-reference-manual.pdf, p.334, "L1 cache flash invalidation" */
   MEMORY_SYNCHRONIZE();
   INSTRUCTION_SYNCHRONIZE();
   MOVE_TO_SPECIAL_PURPOSE_REGISTER
   (
      SPR_L1CSR1,
      (MOVE_FROM_SPECIAL_PURPOSE_REGISTER(SPR_L1CSR1) | L1CSR1_ICFI)
   );
   INSTRUCTION_SYNCHRONIZE();


   MEMORY_SYNCHRONIZE();
   /* "CFI flags are not sticky", so we wait until it is no longer set. */
   while
   (
      (MOVE_FROM_SPECIAL_PURPOSE_REGISTER(SPR_L1CSR1) & L1CSR1_ICFI)
      == L1CSR1_ICFI
   )
   {
      MEMORY_SYNCHRONIZE();
   }
}

void naught_cache_l1_data_disable (void)
{
   /*
    * e6500-reference-manual.pdf, p.100:
    * "After L1 data cache has been enabled, if L1CSR0[CE] = 0 [...], any
    * stashing to the L1 data cache must first be disabled."
    */

   /* Sync requirements from: e6500-reference-manual.pdf, p.186 */

   MEMORY_SYNCHRONIZE();
   INSTRUCTION_SYNCHRONIZE();
   /* Disable L1 Data cache stashing, according to EREF_RM.pdf, p.169 */
   MOVE_TO_SPECIAL_PURPOSE_REGISTER
   (
      SPR_L1CSR2,
      (
         MOVE_FROM_SPECIAL_PURPOSE_REGISTER(SPR_L1CSR2)
         & ~L1CSR2_DCSTASHID
      )
   );
   INSTRUCTION_SYNCHRONIZE();
   MEMORY_SYNCHRONIZE();


   MEMORY_SYNCHRONIZE();
   INSTRUCTION_SYNCHRONIZE();
   /* Disable L1 Data cache, according to EREF_RM.pdf, p.165 */
   MOVE_TO_SPECIAL_PURPOSE_REGISTER
   (
      SPR_L1CSR0,
      (
         MOVE_FROM_SPECIAL_PURPOSE_REGISTER(SPR_L1CSR0)
         & ~L1CSR0_DCE /* Data Cache Enable */
      )
   );
   INSTRUCTION_SYNCHRONIZE();
}

/* Ref: e6500-reference-manual.pdf, p.345: enable l2 first. */
void naught_cache_l1_data_enable (void)
{
   /* Ref: EREF_RM.pdf, p.165 */
   /* "L1CSR0[DCE] <- 1" requires completed flash invalidate of the cache. */
   naught_cache_l1_data_invalidate();

   /* Sync requirements from: e6500-reference-manual.pdf, p.186 */

   MEMORY_SYNCHRONIZE();
   INSTRUCTION_SYNCHRONIZE();
   MOVE_TO_SPECIAL_PURPOSE_REGISTER
   (
      SPR_L1CSR0,
      (
         MOVE_FROM_SPECIAL_PURPOSE_REGISTER(SPR_L1CSR0)
         | L1CSR0_DCE /* Data Cache Enable */
      )
   );
   INSTRUCTION_SYNCHRONIZE();
}

/* Ref: e6500-reference-manual.pdf, p.345: enable l2 first. */
void naught_cache_l1_instruction_enable (void)
{
   /* Ref: EREF_RM.pdf, p.168 */
   /* "L1CSR1[ICE] <- 1" requires completed flash invalidate of the cache. */
   naught_cache_l1_instruction_invalidate();

   /* Sync requirements from: e6500-reference-manual.pdf, p.186 */

   MEMORY_SYNCHRONIZE();
   INSTRUCTION_SYNCHRONIZE();
   MOVE_TO_SPECIAL_PURPOSE_REGISTER
   (
      SPR_L1CSR1,
      (
         MOVE_FROM_SPECIAL_PURPOSE_REGISTER(SPR_L1CSR1)
         | L1CSR1_ICE /* Instruction Cache Enable */
      )
   );
   INSTRUCTION_SYNCHRONIZE();
}

#if (NAUGHT_CACHE_L2_CSR0_AS_SPECIAL_REGISTER == 1)
/*
 * How to enable L2 properly {e6500-reference-manual.pdf, p.345}:
 * Set L2CSR0[L2E] = 1.
 * (L2CSR0[L2E] = 1) req flush of data. This paragraph mentions L2FI, but the
 * next sections points out that you actually need more...
 *
 * How to flush L2 properly {e6500-reference-manual.pdf, p.345}:
 * Simultaneously set (L2CSR0[L2FI] = 1) and (L2CSR0[L2LFC] = 1).
 * Actually, you'll find that there is something else to be done before:
 * indicating what part of the cache to flush (L2CSR0[L2FCID] = 0b11)
 * {EREF_RM.pdf, p.179}.
 *
 * Also, error checking (L2CSR0[L2PE]) should be enabled at the same time as
 * L2CSR0[L2E] {EREF_RM.pdf, p.177}.
 *
 * Finally, the e6500 core does not implement L2CSR0[L2FCID], but always
 * consider it to be 0b11 {e6500-reference-manual.pdf, p.104|106}.
 *
 * How the L2CSR0 register is accessed is ambiguous:
 * - SPR_L2CSR0 is defined {EREF_RM.pdf, p.84}, and {EREF_RM.pdf, p.281} lists mtspr(L2CSR0), which
 *   would indicate that it is used as a special register like L1CSR0 is.
 * - {EREF_RM.pdf, p.88} and {e6500-reference-manual.pdf, p.103} list L2CSR0 as
 *   part of an MMR (Memory Mapped Register block), which are found on the
 *   CCSRBAR and accessed through the TLB.
 *
 * I believe it more likely that the TLB approach is the one to use on the
 * T4240, but I'll leave a way to switch to SPR approach just in case.
 *
 * Thus:
 * 1/ L2CSR0[L2FI] & L2CSR0[L2FLC]
 * 2/ L2CSR0[L2PE] & L2CSR0[L2E]
 */
void naught_cache_l2_enable_local (void)
{
   /*
    * Sync requirements from: EREF_RM.pdf, p.281 mtspr(L2CSR0)
    */
   /*
   MEMORY_SYNCHRONIZE();
   INSTRUCTION_SYNCHRONIZE();

   MOVE_TO_SPECIAL_PURPOSE_REGISTER
   (
      SPR_L2CSR0,
      (
         MOVE_FROM_SPECIAL_PURPOSE_REGISTER(SPR_L2CSR0)
         | L2CSR0_L2FCID
      )
   );

   INSTRUCTION_SYNCHRONIZE();
   */

   MEMORY_SYNCHRONIZE();
   INSTRUCTION_SYNCHRONIZE();

   MOVE_TO_SPECIAL_PURPOSE_REGISTER
   (
      SPR_L2CSR0,
      (
         MOVE_FROM_SPECIAL_PURPOSE_REGISTER(SPR_L2CSR0)
         | L2CSR0_L2FL
         | L2CSR0_L2LFC
      )
   );

   INSTRUCTION_SYNCHRONIZE();

   MEMORY_SYNCHRONIZE();
   INSTRUCTION_SYNCHRONIZE();

   MOVE_TO_SPECIAL_PURPOSE_REGISTER
   (
      SPR_L2CSR0,
      (
         MOVE_FROM_SPECIAL_PURPOSE_REGISTER(SPR_L2CSR0)
         | L2CSR0_L2E
         | L2CSR0_L2PE
      )
   );

   INSTRUCTION_SYNCHRONIZE();
}
#else
void naught_cache_l2_enable (const uint8_t cluster)
{
   /* XXX: BROKEN, DO NOT USE */
   /*
    * This is using the MMR, which, according to
    * {e6500-reference-manual.pdf, p.75}, should be synchronized by performing
    * load operations until we are sure that the 'write' was performed.
    * Additional synchronizations may be required.
    */
   volatile uint32_t * l2csr0_va;

   /* Ref: e6500-reference-manual.pdf, p.73 */
   switch (cluster)
   {
      case 0:
         l2csr0_va =
            (uint32_t *) (NAUGHT_CONFIG_TLB_CCSRBAR_ADDR + MMR_L2REG(C1, CSR0));
         break;

      case 1:
         l2csr0_va =
            (uint32_t *) (NAUGHT_CONFIG_TLB_CCSRBAR_ADDR + MMR_L2REG(C2, CSR0));
         break;

      case 2:
         l2csr0_va =
            (uint32_t *) (NAUGHT_CONFIG_TLB_CCSRBAR_ADDR + MMR_L2REG(C3, CSR0));
         break;

      default:
         return;
   }
   /*
    * Ref: EREF_RM.pdf, p.177:
    * "before it is enabled"
    * "L2CSR0[L2LFC] = 1", "L2CSR0[L2FI] = 1", "L2CSR0[L2FCID] = 0b11".
    */

   /* Ref: EREF_RM.pdf, p.179, must set L2CSR0[L2FCID] *before* flush */
   /*
   *l2csr0_va |= (L2CSR0_L2FCID);

   INSTRUCTION_SYNCHRONIZE();

   while (((*l2csr0_va) & L2CSR0_L2FCID) != L2CSR0_L2FCID)
   {
   }
   */
   *l2csr0_va |= (L2CSR0_L2FL | L2CSR0_L2LFC);


   /* "Continue to read L2CSR0[L2FL] until it reads 0." */
   while (((*l2csr0_va) & L2CSR0_L2FL) == L2CSR0_L2FL)
   {
   }


   /* Ref: e6500-reference-manual.pdf, p.345 "and then perform an isync." */
   INSTRUCTION_SYNCHRONIZE();

   /*
    * "The setting of L2CSR0[L2E] must be preceded by a sync and isync"
    *
    * Ref: EREF_RM.pdf, p.177:
    * "L2PE should only be set when L2E is set in the same operation"
    */
   MEMORY_SYNCHRONIZE();
   INSTRUCTION_SYNCHRONIZE();
   /* Let's also enable error checking (L2PE) */
   *l2csr0_va |= (L2CSR0_L2E | L2CSR0_L2PE);

   while (((*l2csr0_va) & L2CSR0_L2E) != L2CSR0_L2E)
   {
	   MEMORY_SYNCHRONIZE();
   }

}
#endif
