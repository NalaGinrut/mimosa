/*	
 *  Copyright (C) 2010-2011  
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
#include <bsp/bsp_mm.h>
#include <types.h>
#include <debug.h>

static void stab_binsearch(const struct Stab *stabs ,int *region_left,
			   int *region_right ,int type, uintptr_t addr);

void kern_debug()
{
  msg_print("oops~I'm no good!");
  while(1);
}

static void stab_binsearch(const struct Stab *stabs ,int *region_left,
			   int *region_right ,int type, uintptr_t addr)
{
  int l = *region_left;
  int r = *region_right;
  int any_matches = 0;
	
  while(l <= r)
    {
      int true_m = (l + r) / 2, m = true_m;
		
      // search for earliest stab with right type
      while(m >= l && stabs[m].n_type != type)
	{
	  m--;
	}
    
      if (m < l)
	{	// no match in [l, m]
	  l = true_m + 1;
	  continue;
	}

      // actual binary search
      any_matches = 1;
      if(stabs[m].n_value < addr)
	{
	  *region_left = m;
	  l = true_m + 1;
	}
      else if(stabs[m].n_value > addr)
	{
	  *region_right = m - 1;
	  r = m - 1;
	}
      else
	{
	  // exact match for 'addr', but continue loop to find
	  // *region_right
	  *region_left = m;
	  l = m;
	  addr++;
	}
    }

  if(!any_matches)
    {
      *region_right = *region_left - 1;
    }
  else
    {
      // find rightmost region containing 'addr'
      for (l = *region_right;
	   l > *region_left && stabs[l].n_type != type;
	   l--)
	/* do nothing */;
      *region_left = l;
    }
}

int debuginfo_eip(uintptr_t addr ,struct Eipdebuginfo *info)
{
  const struct Stab *stabs ,*stab_end;
  const char *stabstr ,*stabstr_end;
  int lfile ,rfile ,lfun ,rfun ,lline ,rline;
  const u32_t ULIM = (u32_t)GET_BSP_VAR(ULIM);
  
  // Initialize *info
  info->eip_file = "<unknown>";
  info->eip_line = 0;
  info->eip_fn_name = "<unknown>";
  info->eip_fn_namelen = 9;
  info->eip_fn_addr = addr;
  info->eip_fn_narg = 0;

  // Find the relevant set of stabs
  if(addr >= ULIM) {
    stabs = __STAB_BEGIN__;
    stab_end = __STAB_END__;
    stabstr = __STABSTR_BEGIN__;
    stabstr_end = __STABSTR_END__;
  } else {
    // Can't search for user-level addresses yet!
    panic("User address");
  }

  cprintf("1 ok!\n");
  // String table validity checks
  if (stabstr_end <= stabstr || stabstr_end[-1] != 0)
    return -1;

  // Search the entire set of stabs for the source file (type N_SO).
  lfile = 0;
  rfile = (stab_end - stabs) - 1;
  stab_binsearch(stabs, &lfile, &rfile, N_SO, addr);

  if (lfile == 0)
    return -1;
  cprintf("2 ok!\n");

  
  // Search within that file's stabs for the function definition
  // (N_FUN).
  lfun = lfile;
  rfun = rfile;
  stab_binsearch(stabs, &lfun, &rfun, N_FUN, addr);

  if(lfun <= rfun) {
    if(stabs[lfun].n_strx < (stabstr_end - stabstr))
      info->eip_fn_name = stabstr + stabs[lfun].n_strx;

    info->eip_fn_addr = stabs[lfun].n_value;
    addr -= info->eip_fn_addr;
    // Search within the function definition for the line number.
    lline = lfun;
    rline = rfun;
  } else {
    info->eip_fn_addr = addr;
    lline = lfile;
    rline = rfile;
  }
  // Ignore stuff after the colon.
  info->eip_fn_namelen = (strchr(info->eip_fn_name ,':') - info->eip_fn_name);

  stab_binsearch(stabs ,&lline ,&rline ,N_SLINE ,addr);

  if( lline <= rline ) {
    if (stabs[lfun].n_strx < (stabstr_end - stabstr))
      info->eip_line = lline;
    else
      panic("get line error!\n");
  } else {
    return -1;
  }

  cprintf("3 ok!\n");

  while (lline >= lfile &&
	 stabs[lline].n_type != N_SOL &&
	 (stabs[lline].n_type != N_SO || !stabs[lline].n_value))
    lline--;

  if(lline >= lfile && stabs[lline].n_strx < (stabstr_end - stabstr))
    info->eip_file = stabstr + stabs[lline].n_strx;

  //info->eip_fn_narg = 0;
  while( stabs[lfun].n_type != N_PSYM )
    lfun++;
  while( stabs[lfun].n_type == N_PSYM )
    {
      lfun++;
      info->eip_fn_narg++;
    }

  return 0;
}
