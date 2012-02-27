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


#include <types.h>
#include <kernel.h>
#include <mm/mm.h>
#include <tm/tm.h>
#include <env.h>

#ifdef __KERN_DEBUG__
#include <debug.h>
#include <kshell.h>
#endif

void kernel_init()
{

  //TODO: init all kernel modules

#ifdef __KERN_DEBUG__
  struct Trapframe *tf;
  mimosa_kshell_run();
#endif
    
  // Call env_init at the end

  env_init();
}
