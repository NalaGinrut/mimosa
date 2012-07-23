/*	
 *  Copyright (C) 2012  
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
#include <libkern.h>
#include <types.h>
#include <error.h>
#include <mina.h>

// actually, this function is useless, only for debug.
void MINA_show_type(MINA mobj)
{
  char *t = NULL;
  
  switch(mobj->type)
    {
    BOOL: t = "type: Bool"; break;
    LIST: t = "type: List"; break;
    CONS: t = "type: Cons"; break;
    NUMBER: t = "type: Number"; break;
    SYMBOL: t = "type: Symbol"; break;
    STRING: t = "type: String"; break;
    default: panic("invalid type: %d!" ,mobj->type);
    }

  cprintf("%s\n" ,t);
}

char *MINA_get_type(MINA mobj)
{
  // TODO: finish this function after memory-alloc implementation is done.
}

/* TODO: we need something like type_of to get the type and use the type itself as an object.
 */
// type_obj type_of(MINA m) {}

