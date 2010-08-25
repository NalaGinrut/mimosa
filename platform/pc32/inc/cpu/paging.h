#ifndef __MIMOSA_PAGING_H
#define __MIMOSA_PAGING_H
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

#if __X86_PAGING__


#if __BIT32_PAGING__

#if __BIT32_PAGING_NO_PSE__
typedef struct Page_Dir_Entry
{
}pde_t; // Page Directory Entry;
#endif // End of __BIT32_PAGING_NO_PSE;__

#endif // End of __BIT32_PAGING__;



#endif // End of __X86_PAGING__;

#endif // End of __MIMOSA_PAGING_H;
