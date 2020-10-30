/*
 * Copyright (C) 2008-2010 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CORE_REGS_H
#define CORE_REGS_H

// FIXME: Separate out APUs and other target-specific definitions

#define MSRBIT_CM        32 // Computation Mode
#define MSRBIT_GS        35 // Guest State
#define MSRBIT_UCLE      37 // User-mode Cache Lock Enable
#define MSRBIT_SPE       38 // SPE Available
#define MSRBIT_WE        45 // Wait Enable
#define MSRBIT_CE        46 // Critical Enable
#define MSRBIT_EE        48 // External Enable
#define MSRBIT_PR        49 // User Mode
#define MSRBIT_FP        50 // Floating Point Available
#define MSRBIT_ME        51 // Machine Check Available
#define MSRBIT_FE0       52 // Floating Point Exception 0
#define MSRBIT_DE        54 // Debug Mode Enable
#define MSRBIT_FE1       55 // Floating Point Exception 1
#define MSRBIT_IS        58 // Instruction Address Space
#define MSRBIT_DS        59 // Data Address Space
#define MSRBIT_PMM       61 // Performance Monitor Mask
#define MSRBIT_RI        62 // Recoverable interrupt

#define MSR_CM           (1 << (63 - MSRBIT_CM))
#define MSR_GS           (1 << (63 - MSRBIT_GS))
#define MSR_UCLE         (1 << (63 - MSRBIT_UCLE))
#define MSR_SPE          (1 << (63 - MSRBIT_SPE))
#define MSR_WE           (1 << (63 - MSRBIT_WE))
#define MSR_CE           (1 << (63 - MSRBIT_CE))
#define MSR_EE           (1 << (63 - MSRBIT_EE))
#define MSR_PR           (1 << (63 - MSRBIT_PR))
#define MSR_FP           (1 << (63 - MSRBIT_FP))
#define MSR_ME           (1 << (63 - MSRBIT_ME))
#define MSR_FE0          (1 << (63 - MSRBIT_FE0))
#define MSR_DE           (1 << (63 - MSRBIT_DE))
#define MSR_FE1          (1 << (63 - MSRBIT_FE1))
#define MSR_IS           (1 << (63 - MSRBIT_IS))
#define MSR_DS           (1 << (63 - MSRBIT_DS))
#define MSR_PMM          (1 << (63 - MSRBIT_PMM))
#define MSR_RI           (1 << (63 - MSRBIT_RI))

// MOVE
#define MSR_HVPRIV       (MSR_GS | MSR_UCLE | MSR_DE | MSR_WE)
#define MSR_HVPRIV_GDEBUG (MSR_GS | MSR_UCLE | MSR_WE)

#define SPR_XER          1    // Integer Exception Register
#define SPR_LR           8    // Link Register
#define SPR_CTR          9    // Count Register
#define SPR_DEC          22   // Decrementer

#define SPR_SRR0         26   // Save/Restore PC register
#define SPR_SRR1         27   // Save/Restore MSR register

#define SPR_PID          48   // Process ID Register

#define SPR_DECAR        54   // Decrementer Auto-Reload

#define SPR_CSRR0        58   // Critical SRR0
#define SPR_CSRR1        59   // Critical SRR1
#define SPR_DEAR         61   // Data Error Address Register

#define SPR_ESR          62   // Exception Syndrome Register
#define   ESR_PIL          0x08000000 // Illegal Instruction (Prog)
#define   ESR_PPR          0x04000000 // Privileged Instruction (Prog)
#define   ESR_PTR          0x02000000 // Trap (Prog)
#define   ESR_FP           0x01000000 // Floating Point (Align, DSI, DTLB, Prog)
#define   ESR_ST           0x00800000 // Store Operation (Align, DSI, DTLB)
#define   ESR_DLK          0x00200000 // D-cache locking (DSI)
#define   ESR_ILK          0x00100000 // I-cache locking (DSI)
#define   ESR_APU          0x00080000 // Auxiliary Proc (Align, DSI, DTLB, Prog)
#define   ESR_PUO          0x00040000 // Unimplemented Operation (Prog)
#define   ESR_BO           0x00020000 // Byte-ordering (DSI, ISI)
#define   ESR_PIE          0x00010000 // Imprecise Exception (Prog)
#define   ESR_SPE          0x00000080 // SPE/Embedded FP/Altivec
                                      // (Align, DSI, DTLB,
                                      //  Embedded FP Data/Round)
#define   ESR_EPID         0x00000040 // External PID Access
#define   ESR_VLEMI        0x00000020 // VLE instruction
#define   ESR_MIF          0x00000002 // Misaligned Insn Fetch (ITLB, ISI)
#define   ESR_XTE          0x00000001 // External Transaction Err (ISI, DSI)


#define SPR_IVPR         63   // Interrupt Vector Prefix Register
#define IVPR_MASK        (~0xffff)

#define SPR_TBL          268  // Timebase Lower
#define SPR_TBU          269  // Timebase Upper

// SPR General Registers
#define SPR_USPRG0       256
#define SPR_USPRG3       259
#define SPR_USPRG4       260
#define SPR_USPRG5       261
#define SPR_USPRG6       262
#define SPR_USPRG7       263

#define SPR_UTBL         268
#define SPR_UTBU         269

#define SPR_SPRG0        272
#define SPR_SPRG1        273
#define SPR_SPRG2        274
#define SPR_SPRG3        275
#define SPR_SPRG4        276
#define SPR_SPRG5        277
#define SPR_SPRG6        278
#define SPR_SPRG7        279

#define SPR_TBWL         284  // Timebase Lower for Writing
#define SPR_TBWU         285  // Timebase Upper for Writing

#define SPR_PIR          286  // Processor ID Register
#define SPR_PVR          287  // Processor Version Register

#define SPR_DBSR         304  // Debug Status Register
#define   DBSR_MRR         0x30000000 // Most recent reset
#define   DBSR_ICMP        0x08000000 // Instruction complete debug event
#define   DBSR_BRT         0x04000000 // Branch taken debug event
#define   DBSR_IRPT        0x02000000 // Interrupt taken debug event
#define   DBSR_TRAP        0x01000000 // Trap instruction debug event
#define   DBSR_IAC1        0x00800000 // IAC1 debug event
#define   DBSR_IAC2        0x00400000 // IAC2 debug event
#define   DBSR_IAC3        0x00200000 // IAC3 debug event -- reserved in e500mc
#define   DBSR_IAC4        0x00100000 // IAC4 debug event -- reserved in e500mc
#define   DBSR_DAC1R       0x00080000 // DAC1 read debug event
#define   DBSR_DAC1W       0x00040000 // DAC1 write debug event
#define   DBSR_DAC2R       0x00020000 // DAC2 read debug event
#define   DBSR_DAC2W       0x00010000 // DAC2 write debug event
#define   DBSR_RET         0x00008000 // Return debug event

#define SPR_DBSRWR       306  // DBSR Write Register

#define SPR_EPCR        307  // Embedded Processor Control Register
#define   EPCR_EXTGS      0x80000000 // Guest gets external ints
#define   EPCR_DTLBGS     0x40000000 // Guest gets DTLB errors
#define   EPCR_ITLBGS     0x20000000 // Guest gets ITLB errors
#define   EPCR_DSIGS      0x10000000 // Guest gets DSIs
#define   EPCR_ISIGS      0x08000000 // Guest gets ISIs
#define   EPCR_DUVD       0x04000000 // Disable Embedded HV Debug
#define   EPCR_ICM        0x02000000 // Interrupt Compuation Mode
#define   EPCR_GICM       0x01000000 // Guest Interrupt Compuation Mode
#define   EPCR_DGTMI      0x00800000 // Disable guest TLB management insns
#define   EPCR_DMIUH      0x00400000 // Disable MAS int updates for hypervisor

#define SPR_DBCR0        308  // Debug control register 0
#define   DBCR0_EDM        0x80000000 // External debug mode
#define   DBCR0_IDM        0x40000000 // Internal debug mode
#define   DBCR0_RST        0x30000000 // Reset mask
#define   DBCR0_ICMP       0x08000000 // Instruction complete debug event
#define   DBCR0_BRT        0x04000000 // Branch taken debug event
#define   DBCR0_IRPT       0x02000000 // Interrupt taken debug event
#define   DBCR0_TRAP       0x01000000 // Trap instruction debug event
#define   DBCR0_IAC1       0x00800000 // IAC1 debug event
#define   DBCR0_IAC2       0x00400000 // IAC2 debug event
#define   DBCR0_IAC3       0x00200000 // IAC3 debug event -- reserved in e500mc
#define   DBCR0_IAC4       0x00100000 // IAC4 debug event -- reserved in e500mc
#define   DBCR0_DAC1R      0x00080000 // DAC1 read debug event
#define   DBCR0_DAC1W      0x00040000 // DAC1 write debug event
#define   DBCR0_DAC2R      0x00020000 // DAC2 read debug event
#define   DBCR0_DAC2W      0x00010000 // DAC2 write debug event
#define   DBCR0_RET        0x00008000 // Return debug event
#define   DBCR0_FT         0x00000001 // Freeze timers on debug event

#define SPR_DBCR1        309  // Debug control register 1
#define   DBCR1_IAC1ER_EAMSK 0x30000000 // IAC1 effective address mask
#define   DBCR1_IAC1ER_RADDR 0x10000000 // IAC1 real addr unsupported
#define   DBCR1_IAC2ER_EAMSK 0x03000000 // IAC2 effective address mask
#define   DBCR1_IAC2ER_RADDR 0x01000000 // IAC2 real addr unsupported

#define SPR_DBCR2        310  // Debug control register 2
#define   DBCR2_DAC1US_MSK   0xc0000000 // DAC1 User/Supervisor mode mask
#define   DBCR2_DAC1ER_EAMSK 0x30000000 // DAC1 effective address mask
#define   DBCR2_DAC1ER_RADDR 0x10000000 // DAC1 real addr unsupported
#define   DBCR2_DAC2US_MSK   0x0c000000 // DAC2 User/Supervisor mode mask
#define   DBCR2_DAC2ER_EAMSK 0x03000000 // DAC2 effective address mask
#define   DBCR2_DAC2ER_RADDR 0x01000000 // DAC2 real addr unsupported

#define SPR_MSRP         311  // MSR Protect
#define   MSRP_UCLEP     0x04000000 // Protect MSR[UCLE]
#define   MSRP_DEP       0x00000200 // Protect MSR[DE]
#define   MSRP_PMMP      0x00000004 // Protect MSR[PMM]

#define SPR_IAC1         312  // Instruction address compare register 1
#define SPR_IAC2         313  // Instruction address compare register 2
#define SPR_DAC1         316  // Data address compare register 1
#define SPR_DAC2         317  // Data address compare register 2

#define SPR_TSR          336  //  Timer Status Register
#define   TSR_ENW          0x80000000 // Watchdog enabled
#define   TSR_WIS          0x40000000 // Watchdog Int Pending
#define   TSR_WRS          0x30000000 // Watchdog Reset Status
#define   TSR_DIS          0x08000000 // Decrementer Int Pending
#define   TSR_FIS          0x04000000 // Fixed Interval Int Pending

#define SPR_LPIDR        338  // Logical Partition ID

#define SPR_TCR          340  //  Timer Control Register
#define   TCR_WP	   0xC0000000
#define   TCR_WPEXT        0x001E0000
#define   TCR_WP_MASK      (TCR_WPEXT | TCR_WP) // Watchdog Time Period Mask
// Convert TCR[WP|WPEXT] to an integer
#define   TCR_WP_TO_INT(x) \
	((((x) & TCR_WPEXT) >> 15) | (((x) & TCR_WP) >> 30))
// Convert integer to TCR[WP|WPEXT] bits
#define   TCR_INT_TO_WP(x) \
	((((x) << 15) & TCR_WPEXT) | (((x) << 30) & TCR_WP))
#define   TCR_WRC          0x30000000 // Watchdog Reset Control
#define   TCR_WRC_NOP      0x00000000 // Do nothing on 2nd Timeout
#define   TCR_WRC_INT      0x10000000 // Send Int to MPIC on 2nd Timeout
#define   TCR_WRC_REQ      0x20000000 // Ext Reset Request on 2nd Timeout
#define   TCR_WRC_RESET    0x30000000 // Reset Core on 2nd Timeout
#define   TCR_WIE          0x08000000 // Watchdog Int Enable
#define   TCR_DIE          0x04000000 // Decrementer Int Enable
#define   TCR_DIE_SHIFT    26
#define   TCR_FP           0x03000000 // FIT count low bits
#define   TCR_FPEXT        0x0001E000 // FIT count high bits
#define   TCR_FP_MASK      (TCR_FPEXT | TCR_FP) // FIT Period Mask
#define   TCR_ARE          0x00400000 // Auto-reload enable
#define   TCR_FIE          0x00800000 // Fixed Interval Int Enable
#define   TCR_FIE_SHIFT    23
// Convert TCR[FP|FPEXT] to an integer
#define   TCR_FP_TO_INT(x) \
	((((x) & TCR_FPEXT) >> 11) | (((x) & TCR_FP) >> 24))
// Convert integer to TCR[FP|FPEXT] bits
#define   TCR_INT_TO_FP(x) \
	((((x) << 11) & TCR_FPEXT) | (((x) << 24) & TCR_FP))

// Guest SPR General Registers
#define SPR_GSPRG0       368
#define SPR_GSPRG1       369
#define SPR_GSPRG2       370
#define SPR_GSPRG3       371

#define SPR_GSRR0        378  // Guest SRR0
#define SPR_GSRR1        379  // Guest SRR1
#define SPR_GEPR         380  // Guest EPR
#define SPR_GDEAR        381  // Guest DEAR
#define SPR_GPIR         382  // Guest PIR
#define SPR_GESR         383  // Guest ESR

#define IVOR_MASK        0x0000fff0
#define SPR_IVOR0        400  // Critical Input
#define SPR_IVOR1        401  // Machine Check
#define SPR_IVOR2        402  // Data Storage (DSI)
#define SPR_IVOR3        403  // Instruction Storage (ISI)
#define SPR_IVOR4        404  // External Input
#define SPR_IVOR5        405  // Alignment
#define SPR_IVOR6        406  // Program
#define SPR_IVOR7        407  // FP Unavailable
#define SPR_IVOR8        408  // System Call
#define SPR_IVOR9        409  // Auxiliary Processor Unavailable
#define SPR_IVOR10       410  // Decrementer
#define SPR_IVOR11       411  // Fixed Interval Timer
#define SPR_IVOR12       412  // Watchdog
#define SPR_IVOR13       413  // DTLB Error
#define SPR_IVOR14       414  // ITLB Error
#define SPR_IVOR15       415  // Debug

#define SPR_IVOR38       432  // Guest Processor Doorbell
#define SPR_IVOR39       433  // Guest Processor Doorbell Critical
#define SPR_IVOR40       434  // Hypervisor System Call
#define SPR_IVOR41       435  // Hypervisor Privelege

#define SPR_GIVOR2       440  // Guest DSI
#define SPR_GIVOR3       441  // guest ISI
#define SPR_GIVOR4       442  // Guest External Input
#define SPR_GIVOR8       443  // Guest System Call
#define SPR_GIVOR13      444  // Guest DTLB Error
#define SPR_GIVOR14      445  // Guest ITLB Error
#define SPR_GIVPR        447  // Guest IVPR

#define SPR_L1CFG0       515
#define SPR_L1CFG1       516

#define SPR_NPIDR        517 // Nexus Processor ID Register

#define SPR_L2CFG0       519 // L2 Cache Configuration Register 0

#define SPR_ATBL         526  // Alternate Time Base Lower
#define SPR_ATBU         527  // Alternate Time Base Upper

#define SPR_IVOR32       528  // Altivec/SPE/Embedded FP Unavailable
#define SPR_IVOR33       529  // Altivec Assist/Embedded FP Data
#define SPR_IVOR34       530  // Embedded FP Round
#define SPR_IVOR35       531  // Performance Monitor
#define SPR_IVOR36       532  // Processor Doorbell
#define SPR_IVOR37       533  // Processor Doorbell Critical

#define SPR_DBCR4        563
#define   DBCR4_DAC1XM     0x0000f000 // DAC1 extended mask control
#define   DBCR4_DAC1XM_RNG 0x0000c000 // DAC1XM maximum supported range
#define   DBCR4_DAC2XM     0x00000f00 // DAC2 extended mask control
#define   DBCR4_DAC2XM_RNG 0x00000c00 // DAC2XM maximum supported range

#define SPR_MCARU        569  // Machine Check Address Upper
#define SPR_MCSRR0       570  // Machine Check SRR0
#define SPR_MCSRR1       571  // Machine Check SRR1
#define SPR_MCSR         572  // Machine Check Status
#define   MCSR_MCP         0x80000000 // Input to core
#define   MCSR_ICPERR      0x40000000 // Instruction cache parity error
#define   MCSR_DCPERR      0x20000000 // Data cache parity error
#define   MCSR_L2MMU_MHIT  0x08000000 // L2 MMU simultaneous hits
#define   MCSR_NMI         0x00100000 // Non-Maskable Interrupt
#define   MCSR_MAV         0x00080000 // Address Valid
#define   MCSR_MEA         0x00040000 // MCAR is virtual
#define   MCSR_IF          0x00010000 // Instruction Fetch
#define   MCSR_LD          0x00008000 // Load
#define   MCSR_ST          0x00004000 // Store
#define   MCSR_LDG         0x00002000 // Guarded load
#define   MCSR_BSL2_ERR    0x00000001 // L2 cache error
#define SPR_MCAR         573  // Machine check Address

#define SPR_DSRR0        574  // Debug SRR0
#define SPR_DSRR1        575  // Debug SRR1
#define SPR_DDAM         576  // Debug Data Acquisition Message

// SPR General Registers
#define SPR_SPRG8        604
#define SPR_SPRG9        605

#define  SPR_L1CSR2        606         // L1 Cache Control and Status Register 2
#define  L1CSR2_DCWS       0x40000000  // Data cache write shadow
#define  L1CSR2_DCSTASHID  0x000003ff  // Data cache stash ID
#define  SPR_L1CSR3        607         // L1 Cache Control and Status Register 3

#define SPR_PID1         633  // Process ID Register 1 (e500v1, e500v2)
#define SPR_PID2         634  // Process ID Register 2 (e500v1, e500v2)

#define SPR_TLB0CFG      688  // TLB 0 Config Register
#define SPR_TLB1CFG      689  // TLB 1 Config Register
#define   TLBCFG_ASSOC_MASK  0xff000000 // Associativity of TLB
#define   TLBCFG_ASSOC_SHIFT 24
#define   TLBCFG_NENTRY_MASK 0x00000fff // Number of entries in TLB

#define SPR_CDCSR0       696  // Core Device Control and Status 0
#define   CDCSR0_SPE       0
#define   CDCSR0_MTHREAD   8
#define   CDCSR0_ALTIVEC   16
#define   CDCSR0_FPU       24
#define   CDCSR_AWARE      0x80
#define   CDCSR_PRESENT    0x40
#define   CDCSR_GET_STATE(x)   ((x) >> 3) & 7)
#define   CDCSR_GET_CONTROL(x) ((x) & 7)
#define   CDCSR_STATE(x)       ((x) << 3) & 7)
#define   CDCSR_CONTROL(x)     ((x) & 7)

#define SPR_EPR          702  // External Proxy Register

#define SPR_L2ERRINTEN   720 // L2 Cache  Error Interrupt Enable Register
#define SPR_L2ERRATTR    721 // L2 Cache Error Attribute Register
#define SPR_L2ERRADDR    722 // L2 Cache Error Address Capture Register
#define SPR_L2ERREADDR   723 // L2 Cache Error Extended Address Capture Register
#define SPR_L2ERRCTL     724 // L2 Cache Error Control Register
#define SPR_L2ERRDIS     725 // L2 Cache Error Disable Register

#define SPR_EPLC         947  // External PID Load Context
#define SPR_EPSC         948  // External PID Store Context
#define   EPC_EPR          0x80000000 // 1 = user, 0 = kernel
#define   EPCBIT_EPR       32
#define   EPC_EAS          0x40000000 // Address Space
#define   EPCBIT_EAS       33
#define   EPC_EGS          0x20000000 // 1 = guest, 0 = hypervisor
#define   EPCBIT_EGS       34
#define   EPC_ELPID        0x00ff0000
#define   EPC_ELPID_SHIFT  16
#define   EPC_EPID         0x00003fff
#define   EPC_EPID_SHIFT   0

#define SPR_DEVENT       975  // Debug Event Select Register

#define SPR_HDBCR0       976 // Hardware Debug Control Register 0
#define SPR_HDBCR1       977 // Hardware Debug Control Register 1
#define SPR_HDBCR2       978 // Hardware Debug Control Register 2
#define SPR_HDBCR3       979 // Hardware Debug Control Register 3
#define SPR_HDBCR4       980 // Hardware Debug Control Register 4
#define SPR_HDBCR5       981 // Hardware Debug Control Register 5
#define SPR_HDBCR6       982 // Hardware Debug Control Register 6

#define SPR_NSPD         983 // Nexus SPR Access Data Register
#define SPR_NSPC         984 // Nexus SPR Access Configuration Register

#define SPR_L2ERRINJHI   985 // L2 Cache Error Injection Mask High Register
#define SPR_L2ERRINJLO   986 // L2 Cache Error Injection Mask Low Register
#define SPR_L2ERRINJCTL  987 // L2 Cache Error Injection Control Register
#define SPR_L2CAPTDATAHI 988 // L2 Cache Error Capture Data High Register
#define SPR_L2CAPTDATALO 989 // L2 Cache Error Capture Data Low Register
#define SPR_L2CAPTECC    990 // L2 Cache Error Capture ECC Syndrome Register
#define SPR_L2ERRDET     991 // L2 Cache Error Detect Register

#define SPR_HID0         1008 // Hardware Implementation Dependent 0
#define   HID0_EMCP        0x80000000 // Enable Machine Check Pin
#define   HID0_L2MMU_MHD   0x40000000 // Enable L2MMU Multi-Hit Detection
#define   HID0_DOZE        0x00800000
#define   HID0_NAP         0x00400000
#define   HID0_SLEEP       0x00200000
#define   HID0_DPM         0x00100000 // Dynamic Power Management
#define   HID0_EDPM        0x00080000 // Enhanced Dynamic Power Management
#define   HID0_ICR         0x00020000 // Interrupts Clear Reservation
#define   HID0_EIEC        0x00008000 // Enable Internal Error Checking
#define   HID0_ENMAS7      0x00000080 // Enable MAS7 Update
#define   HID0_DCFA        0x00000040 // Data Cache Flush Assist
#define   HID0_CIGLSO      0x00000010 // Cache-Inhibited Guarded Ordering
#define   HID0_NOPTI       0x00000001 // No-op Cache Touch Instructions

#define SPR_L1CSR0       1010 // L1 Cache Control and Status Register 0
#define   L1CSR0_DCPE      0x00010000 // Data Cache Parity Enable
#define   L1CSR0_DCSLC     0x00000800 // Data Cache Snoop Lock Clear
#define   L1CSR0_DCUL      0x00000400 // Data Cache Unable to Lock
#define   L1CSR0_DCLO      0x00000200 // Data Cache Lock Overflow
#define   L1CSR0_DCLFC     0x00000100 // Data Cache Lock Bits Flash Clear
#define   L1CSR0_DCBZ32    0x00000008 // dcbz works on 32-byte blocks
#define   L1CSR0_DCFI      0x00000002 // Data Cache Flash Invalidate
#define   L1CSR0_DCE       0x00000001 // Data Cache Enable

#define SPR_L1CSR1       1011 // L1 Cache Control and Status Register 1
#define   L1CSR1_ICPE      0x00010000 // Instruction Cache Parity Enable
#define   L1CSR1_ICSLC     0x00000800 // Instruction Cache Snoop Lock Clear
#define   L1CSR1_ICUL      0x00000400 // Instruction Cache Unable to Lock
#define   L1CSR1_ICLO      0x00000200 // Instruction Cache Lock Overflow
#define   L1CSR1_ICLFC     0x00000100 // Instruction Cache Lock Bits Flash Clear
#define   L1CSR1_ICFI      0x00000002 // Instruction Cache Flash Invalidate
#define   L1CSR1_ICE       0x00000001 // Instruction Cache Enable

#define SPR_L2CSR0      1017       // L2 Cache Control and Status Register 0
#define  L2CSR0_L2E     0x80000000 // L2 Enable
#define  L2CSR0_L2PE    0x40000000 // L2 Parity Enable
#define  L2CSR0_L2WP    0x1c000000 // L2 Way Partitioning
#define  L2CSR0_L2FI    0x00200000 // L2 Flash Invalidate
#define  L2CSR0_L2IO    0x00100000 // L2 Instruction Only
#define  L2CSR0_L2DO    0x00010000 // L2 Data Only
#define  L2CSR0_L2FL    0x00000800 // L2 Flush
#define  L2CSR0_L2LFC   0x00000400 // L2 Cache Lock Flash Clear
#define  L2CSR0_L2FCID  0x00000300 // L2 Cache Lock Flash Clear Instruction or Data
#define  L2CSR0_L2SLC   0x00000040 // L2 Cache Snoop Lock Clear
#define  L2CSR0_L2LO    0x00000020 // L2 Cache Lock Overflow

#define SPR_L2CSR1       1018 // L2 Cache Control and Status Register 1

// L2 memory mapped registers
// NOTE: taken from T4240 maybe they should be moved there
#define MMR_L2_C1 0xC20000UL
#define MMR_L2_C2 0xC60000UL
#define MMR_L2_C3 0xCA0000UL
#define MMR_L2CSR0_OFFSET 0
#define MMR_L2PAR0_OFFSET 0x0208
#define MMR_L2PAR1_OFFSET 0x0218
#define MMR_L2PAR2_OFFSET 0x0228
#define MMR_L2PAR3_OFFSET 0x0238
#define MMR_L2CSR0(X) MMR_L2_ ## X + MMR_L2CSR0_OFFSET
#define MMR_L2PAR0(X) MMR_L2_ ## X + MMR_L2PAR0_OFFSET
#define MMR_L2PAR1(X) MMR_L2_ ## X + MMR_L2PAR1_OFFSET
#define MMR_L2PAR2(X) MMR_L2_ ## X + MMR_L2PAR2_OFFSET
#define MMR_L2PAR3(X) MMR_L2_ ## X + MMR_L2PAR3_OFFSET
// Generic macro that can be used as a way to access
// a specific L2 cluster register.
// So for example to access L2 CSR0 of cluster 1 just write:
//    MMR_L2REG(C1,CSR0)
#define MMR_L2REG(C,R) MMR_L2_ ## C + MMR_L2 ## R ## _OFFSET

#define SPR_MMUCSR0      1012 // MMU Control and Status Register 0
#define   MMUCSR_L2TLB0_FI 0x00000004 // Invalidate TLB0
#define   MMUCSR_L2TLB1_FI 0x00000002 // Invalidate TLB1

#define SPR_BUCSR        1013
#define   BUCSR_STACEN     (1 << 24)  // Segment target address cache (STAC) enable
#define   BUCSR_LSEN       (1 << 22)  // Link Stack enable
#define   BUCSR_BBFI       0x00000200 // Branch Buffer Flash Invalidate
#define   BUCSR_BPEN       0x00000001 // Branch Prediction Enable

#define SPR_MMUCFG       1015 // MMU Configuration Register
#define   MMUCFG_LPIDSIZE  0x0f000000 // Number of LPID bits
#define   MMUCFG_LPIDSIZE_SHIFT 24
#define   MMUCFG_RASIZE    0x00fe0000 // Number of real-address bits
#define   MMUCFG_RASIZE_SHIFT   17
#define   MMUCFG_NPIDS     0x00007800 // Number of PID registers
#define   MMUCFG_NPIDS_SHIFT    11
#define   MMUCFG_PIDSIZE   0x000007c0 // Bits in a PID register, minus one
#define   MMUCFG_PIDSIZE_SHIFT  6
#define   MMUCFG_NTLBS     0x0000000c // Number of TLBs
#define   MMUCFG_NTLBS_SHIFT    2
#define   MMUCFG_MAVN      0x00000003 // MMU architecture version

#define SPR_SVR          1023 // System Version Register

#define PMR_UPMC0      0
#define PMR_UPMC1      1
#define PMR_UPMC2      2
#define PMR_UPMC3      3
#define PMR_PMC0       16
#define PMR_PMC1       17
#define PMR_PMC2       18
#define PMR_PMC3       19
#define PMR_UPMLCA0    128
#define PMR_UPMLCA1    129
#define PMR_UPMLCA2    130
#define PMR_UPMLCA3    131
#define PMR_PMLCA0     144
#define PMR_PMLCA1     145
#define PMR_PMLCA2     146
#define PMR_PMLCA3     147
#define   PMLCA_FC         0x80000000
#define   PMLCA_FCS        0x40000000
#define   PMLCA_FCU        0x20000000
#define   PMLCA_FCM1       0x10000000
#define   PMLCA_FCM0       0x08000000
#define   PMLCA_CE         0x04000000
#define   PMLCA_EVENT      0x00ff0000
#define   PMLCA_EVENT_SHIFT 16
#define PMR_UPMLCB0    256
#define PMR_UPMLCB1    257
#define PMR_UPMLCB2    258
#define PMR_UPMLCB3    259
#define PMR_PMLCB0     272
#define PMR_PMLCB1     273
#define PMR_PMLCB2     274
#define PMR_PMLCB3     275
#define   PMLCB_THRESHMUL  0x00000700
#define   PMLCB_THRESHMUL_SHIFT 8
#define   PMLCB_THRESHOLD  0x0000003f
#define   PMLCB_THRESHOLD_SHIFT 0
#define PMR_UPMGC0     384
#define PMR_PMGC0      400
#define   PMGC0_FAC        0x80000000
#define   PMGC0_PMIE       0x40000000
#define   PMGC0_FCECE      0x20000000

// MMU registers
#define SPR_MAS0         624  // MMU Assist Register 0
#define SPR_MAS1         625  // MMU Assist Register 1
#define SPR_MAS2         626  // MMU Assist Register 2
#define SPR_MAS3         627  // MMU Assist Register 3
#define SPR_MAS4         628  // MMU Assist Register 4
#define SPR_MAS5         339  // MMU Assist Register 5
#define SPR_MAS6         630  // MMU Assist Register 6
#define SPR_MAS7         944  // MMU Assist Register 7
#define SPR_MAS8         341  // MMU Assist Register 8

#define TLB0 0
#define TLB1 1

#define   MAS0_TLBSEL(x)     ((x << 28) & 0x10000000)
#define   MAS0_ESEL(x)       ((x << 16) & 0x003F0000)
#define   MAS0_GET_TLBSEL(x) ((x >> 28) & 3)
#define   MAS0_GET_TLB0ESEL(x)((x >> 16) & 3)
#define   MAS0_GET_TLB1ESEL(x)((x >> 16) & 63)
#define   MAS0_TLBSEL1       0x10000000
#define   MAS0_TLBSEL0       0x00000000
#define   MAS0_TLBSEL_MASK   0x30000000
#define   MAS0_ESEL_TLB1MASK 0x003F0000
#define   MAS0_ESEL_TLB0MASK 0x00030000
#define   MAS0_ESEL_MASK     0x0fff0000
#define   MAS0_ESEL_SHIFT    16
#define   MAS0_NV_MASK       0x00000003
#define   MAS0_NV_SHIFT      0
#define   MAS0_RESERVED      0xe000f000

#define   MAS1_VALID         0x80000000
#define   MAS1_IPROT         0x40000000
#define   MAS1_IPROT_SHIFT   30
#define   MAS1_TID_MASK      0x00FF0000
#define   MAS1_TID_SHIFT     16
#define   MAS1_TS            0x00001000
#define   MAS1_TS_SHIFT      12
#define   MAS1_TSIZE_MASK    0x00000F00
#define   MAS1_TSIZE_SHIFT   8
#define   MAS1_GETTID(mas1)  (((mas1) & MAS1_TID_MASK) >> MAS1_TID_SHIFT)
#define   MAS1_GETTS(mas1)   (((mas1) & MAS1_TS) >> MAS1_TS_SHIFT)
#define   MAS1_GETTSIZE(mas1)(((mas1) & MAS1_TSIZE_MASK) >> MAS1_TSIZE_SHIFT)
#define   MAS1_RESERVED      0x0000e0ff

#define   MAS2_EPN           (~0xfffUL)
#define   MAS2_EPN_SHIFT     12
#define   MAS2_X0            0x00000040
#define   MAS2_X1            0x00000020
#define   MAS2_W             0x00000010
#define   MAS2_I             0x00000008
#define   MAS2_M             0x00000004
#define   MAS2_G             0x00000002
#define   MAS2_E             0x00000001
#define   MAS2_TLB0_ENTRY_IDX_MASK  0x0007f000
#define   MAS2_TLB0_ENTRY_IDX_SHIFT 12
#define   MAS2_RESERVED      0x00000f00
#define   MAS2_FLAGS         0x000000ff

#define   MAS3_RPN           0xFFFFF000
#define   MAS3_RPN_SHIFT     12
#define   MAS3_USER          0x000003c0
#define   MAS3_U0            0x00000200
#define   MAS3_U1            0x00000100
#define   MAS3_U2            0x00000080
#define   MAS3_U3            0x00000040
#define   MAS3_UX            0x00000020
#define   MAS3_SX            0x00000010
#define   MAS3_UW            0x00000008
#define   MAS3_SW            0x00000004
#define   MAS3_UR            0x00000002
#define   MAS3_SR            0x00000001
#define   MAS3_RESERVED      0x00000c00
#define   MAS3_FLAGS         0x0000003f

#define   MAS4_TLBSELD1      0x10000000
#define   MAS4_TLBSELD0      0x00000000
#define   MAS4_TSIZED_MASK   0x00000F00
#define   MAS4_TSIZED_SHIFT  8
#define   MAS4_X0D           0x00000040
#define   MAS4_X1D           0x00000020
#define   MAS4_WD            0x00000010
#define   MAS4_ID            0x00000008
#define   MAS4_MD            0x00000004
#define   MAS4_GD            0x00000002
#define   MAS4_ED            0x00000001

#define   MAS5_SGS           0x80000000 // Search GS
#define   MAS5_SLPID         0x000000ff // Search LPID

#define   MAS6_SPID_MASK     0x00FF0000
#define   MAS6_SPID_SHIFT    16
#define   MAS6_SAS           0x00000001

#define   MAS7_RPN           0x0000000f
#define   MAS7_RESERVED      0xfffffff0

#define   MAS8_GTS           0x80000000 /* Guest space */
#define   MAS8_GTS_SHIFT     31
#define   MAS8_VF            0x40000000 /* Virtualization Fault */
#define   MAS8_VF_SHIFT      30
#define   MAS8_TLPID         0x000000ff


#define TLB_TSIZE_4K   1
#define TLB_TSIZE_16K  2
#define TLB_TSIZE_64K  3
#define TLB_TSIZE_256K 4
#define TLB_TSIZE_1M   5
#define TLB_TSIZE_4M   6
#define TLB_TSIZE_16M  7
#define TLB_TSIZE_64M  8
#define TLB_TSIZE_256M 9
#define TLB_TSIZE_1G   10
#define TLB_TSIZE_4G   11

#define TLB_MAS2_IO    (MAS2_I | MAS2_G)
#define TLB_MAS2_MEM   (MAS2_M)

#define TLB_MAS3_KERN  (MAS3_SR | MAS3_SW | MAS3_SX)
#define TLB_MAS3_KDATA (MAS3_SR | MAS3_SW)

#define TLB_MAS8_HV    0
#define TLB_MAS8_GUEST MAS8_GTS

#define TLBIVAX_VA       (~0xfffUL)
#define TLBIVAX_RESERVED 0xff3
#define TLBIVAX_INV_ALL  0x004
#define TLBIVAX_TLB_NUM  0x018
#define TLBIVAX_TLB0     0x000
#define TLBIVAX_TLB1     0x008
#define TLBIVAX_TLB_NUM_SHIFT 3


#endif
