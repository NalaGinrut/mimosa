#ifndef	__MIMOSA_MUTEX_H
#define __MIMOSA_MUTEX_H
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

#include <types.h>
#include <lock.h>


// all mutex is spin type;
typedef u32_t mutex_t;

void mutex_wait(mutex_t *mutex);
void mutex_signal(mutex_t *mutex);

void mutex_set_wait(mutex_t *mutex ,u8_t offset);
void mutex_set_signal(mutex_t *mutex ,u8_t offset);

#endif // End of __MIMOSA_MUTEX_H;
