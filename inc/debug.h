#ifndef	__MIMOSA_DEBUG_H
#define __MIMOSA_DEBUG_H
#ifdef USE_PC32_DEBUG
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

/* online debug take advantage of serial port to debug kernel from another
 * machine. Not implemented yet.
 * TODO: Can we implement it with gdb-server or similar?
 */
//#define __KERN_ONLINE_DEBUG__

#include <debug/display.h>
#include <debug/trace.h>
#include <types.h>
#include <stab.h>

extern const struct Stab __STAB_BEGIN__[];	// Beginning of stabs table
extern const struct Stab __STAB_END__[];	// End of stabs table
extern const char __STABSTR_BEGIN__[];		// Beginning of string table
extern const char __STABSTR_END__[];		// End of string tabl

// Debug information about a particular instruction pointer
struct Eipdebuginfo {
  const char *eip_file;           // Source code filename for EIP
  int eip_line;                   // Source code linenumber for EIP

  const char *eip_fn_name;        // Name of function containing EIP
  //  - Note: not null terminated!
  int eip_fn_namelen;             // Length of function name
  uintptr_t eip_fn_addr;          // Address of start of function
  int eip_fn_narg;                // Number of function arguments
};

int debuginfo_eip(uintptr_t eip ,struct Eipdebuginfo *info);

#endif // End of USE_PC32_DEBUG;
#endif // End of __MIMOSA_DEBUG_H;
