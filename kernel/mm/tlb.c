/*	
 *  Copyright (C) 2012
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

#include <osconfig.h>
#include <tlb.h>

/* <Discription>:
 * Flushes all TLB entries (including those that refer to global pages,
 * that is, pages whose Global flag is set). 
 *
 * <Usage>:
 * Changing the kernel page table entries.
 */
void flush_tlb_all()
{}

/* <Discription>:
 * Flushes all TLB entries in a given range of linear addresses
 * (including those that refer to global pages).
 *
 * <Usage>:
 * Changing a range of kernel page table entries.
 */
void flush_tlb_kernel_range(start ,end)
{}

/* <Discription>:
 * Flushes all TLB entries of the non-global pages owned by the current process. 
 *
 * <Usage>:
 * Performing a process switch.
 */
void flush_tlb()
{}

/* <Discription>:
 * Flushes all TLB entries of the non-global pages owned by a given process. 
 *
 * <Usage>:
 * Forking a new process.
 */
void flush_tlb_mm(who)
{}

/* <Discription>:
 * Flushes the TLB entries corresponding to a Releasing a linear linear
 * address interval of a given process.
 *
 * <Usage>:
 * address interval of a process
 */
void flush_tlb_range(who ,range)
{}

/* <Discription>:
 * Flushes the TLB entries of a given contiguous subset of page tables of
 * a given process. 
 *
 * <Usage>:
 * Releasing some page tables of a process.
 */
void flush_tlb_pgtables(who ,pt)
{}

/* <Discription>:
 * Flushes the TLB of a single Page Table entry of a given process.
 *
 * <Usage>:
 * Processing a Page Fault.
 */
void flush_tlb_page(who)
{}


 



