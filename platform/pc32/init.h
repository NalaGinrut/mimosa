#ifndef	__MIMOSA_INIT_H
#define __MIMOSA_INIT_H
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


extern char __bss_start[] ,__bss_end[];

#define __BSS_SIZE	(__bss_end - __bss_start)


void platform_init();
void bsp_init_clear_tmp();
void bsp_init_console();
void bsp_init_memory();
void bsp_init_online_debug();
#endif // End of __MIMOSA_INIT_H;
