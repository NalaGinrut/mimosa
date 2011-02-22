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


#include <now/bsp_types.h>
#include "init.h"

#ifdef __KERN_DEBUG__
#include <debug.h>
#endif

void platform_init()
{

  bsp_init_clear_tmp();
  bsp_init_console();

#ifdef __KERN_ONLINE_DEBUG__
  bsp_init_online_debug();
#endif



}

void bsp_init_clear_tmp()
{
  /* NOTE: In general, the BSS section is auto cleared by compiler.
   * But don't forget you are dealing with a KERNEL. That means some
   * memory maybe polluted by boot code. So don't skimp this little 
   * time. Just clear it again. Make sure that all static/global vars
   * are well initialized.
   */

  memset(__bss_start ,0 ,__BSS_SIZE);

}

void bsp_init_console()
{
  // TODO: init console ,then we could print message.
}

void bsp_init_online_debug()
{

  // TODO: init serial port just for online debug.
  // The actual serial device init will be later.
  // FIXME: Maybe we can init that just for a once......
}
