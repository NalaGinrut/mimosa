#ifndef __MIMOSA_PC32_PLATFORM_CPP_LD
#define __MIMOSA_PC32_PLATFORM_CPP_LD
/*	
 *  Copyright (C) 2010-2011,2016
 *	"Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>
 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


/* This ld script used for kernel linking. 
 * Modify it may effect the whole kernel framework, so DON'T MODIFY IT!!!
 */

#include <generic/generic.ld.h>
#include <osconfig.h>
#include <global.h>

/* pc32 platform need some ISA reserved address, I'll define it later.
 */
/*
 * Virtual memory map:                                Permissions
 *                                                    kernel/user
 *
 *    4 Gig -------->  +------------------------------+
 *                     |                              | RW/--
 *                     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                     :              .               :
 *                     :              .               :
 *                     :              .               :
 *                     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| RW/--
 *                     |                              | RW/--
 *                     |   Remapped Physical Memory   | RW/--
 *                     |                              | RW/--
 *    KERNBASE ----->  +------------------------------+ 0xc0000000
 *                     |  Cur. Page Table (Kern. RW)  | RW/--  PTSIZE
 *    VPT,KSTACKTOP--> +------------------------------+ 0xbfc00000      --+
 *                     |         Kernel Stack         | RW/--  KSTKSIZE   |
 *                     | - - - - - - - - - - - - - - -|                 PTSIZE
 *                     |      Invalid Memory (*)      | --/--             |
 *    ULIM     ------> +------------------------------+ 0xbf800000      --+
 *                     |  Cur. Page Table (User R-)   | R-/R-  PTSIZE
 *    UVPT      ---->  +------------------------------+ 0xbf400000
 *                     |          RO PAGES            | R-/R-  PTSIZE
 *    UPAGES    ---->  +------------------------------+ 0xbf000000
 *                     |           RO ENVS            | R-/R-  PTSIZE
 * UTOP,UENVS ------>  +------------------------------+ 0xbec00000
 * UXSTACKTOP -/       |     User Exception Stack     | RW/RW  PGSIZE
 *                     +------------------------------+ 0xbebff000
 *                     |       Empty Memory (*)       | --/--  PGSIZE
 *    USTACKTOP  --->  +------------------------------+ 0xbebfe000
 *                     |      Normal User Stack       | RW/RW  PGSIZE
 *                     +------------------------------+ 0xbebfd000
 *                     |                              |
 *                     |                              |
 *                     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                     .                              .
 *                     .                              .
 *                     .                              .
 *                     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
 *                     |     Program Data & Heap      |
 *    UTEXT -------->  +------------------------------+ 0x00800000
 *    PFTEMP ------->  |       Empty Memory (*)       |        PTSIZE
 *                     |                              |
 *    UTEMP -------->  +------------------------------+ 0x00400000      --+
 *                     |       Empty Memory (*)       |                   |
 *                     | - - - - - - - - - - - - - - -|                   |
 *                     |  User STAB Data (optional)   |                 PTSIZE
 *    USTABDATA ---->  +------------------------------+ 0x00200000        |
 *                     |       Empty Memory (*)       |                   |
 *    0 ------------>  +------------------------------+                 --+
 *
 * (*) Note: The kernel ensures that "Invalid Memory" (ULIM) is *never*
 *     mapped.  "Empty Memory" is normally unmapped, but user programs may
 *     map pages there if desired.  JOS user programs map pages temporarily
 *     at UTEMP.
 */

/* memory layout of BSP ,you should change them with "make genconf"
 * DO NOT MODIFY THEM MANUALLY!!!
 */
BSP_SYM(VPT) = KERN_BASE - PT_SIZE;
BSP_SYM(KSTKTOP) = GET_BSP_VAR(VPT);
BSP_SYM(ULIM) = GET_BSP_VAR(KSTKTOP) - PT_SIZE;
BSP_SYM(UVPT) = GET_BSP_VAR(ULIM) - PT_SIZE;
BSP_SYM(UPAGES) = GET_BSP_VAR(UVPT) - PT_SIZE;
BSP_SYM(UENVS) = GET_BSP_VAR(UPAGES) - PT_SIZE;
BSP_SYM(UTOP) = GET_BSP_VAR(UENVS);
BSP_SYM(UXSTKTOP) = GET_BSP_VAR(UTOP);
BSP_SYM(USTKTOP) = GET_BSP_VAR(UTOP) - 2 * PG_SIZE;
BSP_SYM(UTEXT) = 2 * PT_SIZE;
BSP_SYM(UTEMP) = PT_SIZE;
BSP_SYM(PFTEMP) = GET_BSP_VAR(UTEMP) + PT_SIZE - PG_SIZE;
BSP_SYM(USTABDATA) = PT_SIZE / 2;

#define BSP_SPECFIC_SECTION

#endif // End of __MIMOSA_PC32_PLATFORM_CPP_LD
