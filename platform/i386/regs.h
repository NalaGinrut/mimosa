#ifndef __MIMOSA_CRN_H
#define __MIMOSA_CRN_H
 /* Copyleft(c)2010 HackerFellowship. All lefts reserved.
  
 * NalaGinrut <NalaGinrut@gmail.com>
  
 * May Lord Bless!Happy Hacking!
  
 * This program is free software;you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundataion;either version 2 of the License,or (at 
 * your option) any later version.
  
 * You should have read the GNU General Public License before start "RTFSC".
  
 * If not,see <http://www.gnu.org/licenses/>
 */




// This CR3 is only for 32bit-paging now...
typedef union CR3
{
  struct inner
  {
  undef1	:3;
  PWT		:1;
  PCD		:1;
  undef2	:7;
  addr		:20; // NOTE: just for 4kB page-dirs;
  }is;
  
  __u32_t all;
}__sys_cr3;


#endif // End of __MIMOSA_CRN_H;










