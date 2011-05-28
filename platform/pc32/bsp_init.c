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
#include <kernel.h>
#include <types.h>
#include <libkern.h>
#include <drivers/console.h>
#include <bsp/pmap.h>
#include <bsp/bsp_init.h>

#ifdef __KERN_DEBUG__
#include <debug.h>
#endif

void platform_init()
{
  bsp_init_clear_tmp();
  bsp_init_console();

#ifdef __KERN_DEBUG__
  msg_print("In the beginning,God created the heavens and the earth.\t--Genesis 1:1\n");
#endif


  while(1);

#ifdef __KERN_ONLINE_DEBUG__
  bsp_init_online_debug();
#endif

  //bsp_init_memory();

  //TODO: other init needed.

  /* If all the init depended on platform have done ,we'd jump into
   * the kernel init procedure. Please be sure that ,you can't write any
   * platform specified code in the kernel module. It's generic.
   */

  //kernel_init();
}

static void bsp_init_clear_tmp()
{
  /* NOTE: In general, the BSS section is auto cleared by compiler.
   * But don't forget you are dealing with a KERNEL. That means some
   * memory maybe polluted by boot code. So don't skimp this little 
   * time. Just clear it again. Make sure that all static/global vars
   * are well initialized.
   */

  memset(__bss_start ,0 ,__BSS_SIZE);

}

static void bsp_init_console()
{
  // TODO: init console ,then we could print message.
  console_init();

}

static void bsp_init_online_debug()
{

  // TODO: init serial port just for online debug.
  // The actual serial device init will be later.
  // FIXME: Maybe we can init that just for a once......
}

static void bsp_init_memory()
{
  /* TODO: 
   * 1. detect memory amount
   * 2. init virtual memory
   * 3. deal with page mapping
   * 4. check page mapping if necessary
   */

}
