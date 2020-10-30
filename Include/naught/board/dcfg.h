#pragma once

#include <stdint.h>

#define NAUGHT_DCFG_ADDR_OFFSET 0x000E0000

/* T4240RM, p.2458 - 2464 */
typedef struct {
  uint32_t porsr1;
  uint32_t porsr2;
  uint32_t gpporcr1;
  uint32_t gpporcr2;
  uint32_t fusesr;
  uint32_t devdisr1;
  uint32_t devdisr2;
  uint32_t devdisr3;
  uint32_t devdisr4;
  uint32_t devdisr5;
  uint32_t coredisr;
  uint32_t pvr;
  uint32_t svr;
  uint32_t rstcr;
  uint32_t rstrqpblsr;
  uint32_t rstrqmr1;
  uint32_t rstrqsr1;
  uint32_t rstrqwdtmr;
  uint32_t rstrqwdtsr;
  uint32_t bbr;
  uint32_t rcwsr1;
  uint32_t rcwsr2;
  uint32_t rcwsr3;
  uint32_t rcwsr4;
  uint32_t rcwsr5;
  uint32_t rcwsr6;
  uint32_t rcwsr7;
  uint32_t rcwsr8;
  uint32_t rcwsr9;
  uint32_t rcwsr10;
  uint32_t rcwsr11;
  uint32_t rcwsr12;
  uint32_t rcwsr13;
  uint32_t rcwsr14;
  uint32_t rcwsr15;
  uint32_t rcwsr16;
  uint32_t scratchrw1;
  uint32_t scratchrw2;
  uint32_t scratchrw3;
  uint32_t scratchrw4;
  uint32_t scratchrw1r1;
  uint32_t scratchrw1r2;
  uint32_t scratchrw1r3;
  uint32_t scratchrw1r4;
  uint32_t crstsr0;
  uint32_t crstsr1;
  uint32_t crstsr2;
  uint32_t crstsr3;
  uint32_t crstsr4;
  uint32_t crstsr5;
  uint32_t crstsr6;
  uint32_t crstsr7;
  uint32_t crstsr8;
  uint32_t crstsr9;
  uint32_t crstsr10;
  uint32_t crstsr11;
  uint32_t usb1liodnr;
  uint32_t usb2liodnr;
  uint32_t sata1liodnr;
  uint32_t sata2liodnr;
  uint32_t dma1liodnr;
  uint32_t dma2liodnr;
  uint32_t dma3liodnr;
  uint32_t pamubypenr;
  uint32_t dmacr1;
  uint32_t tp_ityp0;
  uint32_t tp_ityp1;
  uint32_t tp_ityp2;
  uint32_t tp_ityp3;
  uint32_t tp_ityp4;
  uint32_t tp_ityp5;
  uint32_t tp_ityp6;
  uint32_t tp_ityp7;
  uint32_t tp_ityp8;
  uint32_t tp_ityp9;
  uint32_t tp_ityp10;
  uint32_t tp_ityp11;
  uint32_t tp_ityp12;
  uint32_t tp_ityp13;
  uint32_t tp_ityp14;
  uint32_t tp_ityp15;
  uint32_t tp_ityp16;
  uint32_t tp_ityp17;
  uint32_t tp_ityp18;
  uint32_t tp_ityp19;
  uint32_t tp_ityp20;
  uint32_t tp_ityp21;
  uint32_t tp_ityp22;
  uint32_t tp_ityp23;
  uint32_t tp_ityp24;
  uint32_t tp_ityp25;
  uint32_t tp_ityp26;
  uint32_t tp_ityp27;
  uint32_t tp_ityp28;
  uint32_t tp_ityp29;
  uint32_t tp_ityp30;
  uint32_t tp_ityp31;
  uint32_t tp_ityp32;
  uint32_t tp_ityp33;
  uint32_t tp_ityp34;
  uint32_t tp_ityp35;
  uint32_t tp_ityp36;
  uint32_t tp_ityp37;
  uint32_t tp_ityp38;
  uint32_t tp_ityp39;
  uint32_t tp_ityp40;
  uint32_t tp_ityp41;
  uint32_t tp_ityp42;
  uint32_t tp_ityp43;
  uint32_t tp_ityp44;
  uint32_t tp_ityp45;
  uint32_t tp_ityp46;
  uint32_t tp_ityp47;
  uint32_t tp_ityp48;
  uint32_t tp_ityp49;
  uint32_t tp_ityp50;
  uint32_t tp_ityp51;
  uint32_t tp_ityp52;
  uint32_t tp_ityp53;
  uint32_t tp_ityp54;
  uint32_t tp_ityp55;
  uint32_t tp_ityp56;
  uint32_t tp_ityp57;
  uint32_t tp_ityp58;
  uint32_t tp_ityp59;
  uint32_t tp_ityp60;
  uint32_t tp_ityp61;
  uint32_t tp_ityp62;
  uint32_t tp_ityp63;
  uint32_t cluster1;
  uint32_t cluster2;
  uint32_t cluster3;
  uint32_t qmbm_warmrst;
  uint32_t ddrclkdr;
  uint32_t ifcclkdr;
  uint32_t sdhcpcr;
} naught_dcfg_ccsr_t;
