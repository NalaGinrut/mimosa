/*	
 *  Copyright (C) 2010-2012  
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

#ifdef USE_KERN_SHELL
  mimosa_kshell_run(NULL);
#endif // End of USE_KERN_SHELL;

#endif

  /*
  mimosa_memory_init();
  mimosa_fs_init();
  mimosa_interrupt_init();
  */
  
  // Call env_init at the end

  env_init();
}
