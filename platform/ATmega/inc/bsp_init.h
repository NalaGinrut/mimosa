#ifndef	__MIMOSA_BSP_INIT_H
#define __MIMOSA_BSP_INIT_H
/*
 *  Copyright (C) 2016
 *      "Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>
 
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

extern char __bss_start[] ,__bss_end[];

#define __BSS_SIZE	(__bss_end - __bss_start)

void platform_init();
static void bsp_init_clear_tmp();
static void bsp_init_console();
static void bsp_init_memory();
static void bsp_init_online_debug();
static void bsp_init_platform_specific();
#endif // End of __MIMOSA_BSP_INIT_H;
