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
#include <types.h>
#include <scheme/mina.h>
#include <scheme/opcode.h>

static scm_num num_add(scm_num a ,scm_num b);
static scm_num num_mul(scm_num a ,scm_num b);
static scm_num num_div(scm_num a ,scm_num b);
static scm_num num_intdiv(scm_num a ,scm_num b);
static scm_num num_sub(scm_num a ,scm_num b);
static scm_num num_rem(scm_num a ,scm_num b);
static scm_num num_mod(scm_num a ,scm_num b);
static bool num_eq(scm_num a ,scm_num b);
static bool num_gt(scm_num a ,scm_num b);
static bool num_ge(scm_num a ,scm_num b);
static bool num_lt(scm_num a ,scm_num b);
static bool num_le(scm_num a ,scm_num b);

static int is_list(scheme sc ,MINA a)
{
  return list_length(sc ,a) >= 0;
}

/* Result is:
   proper list: length
   circular list: -1
   not even a pair: -2
   dotted list: -2 minus length before dot
*/
int list_length(scheme sc ,MINA a)
{
  int i = 0;
  MINA slow ,fast;

  slow = fast = a;
  while(1)
    {
      if(fast == sc->NIL)
	return i;
      if(!is_pair(fast))
	return -2 - i;
      fast = cdr(fast);
      i++;
      if(fast == sc->NIL)
	return i;
      if(!is_pair(fast))
	return -2 - i;
      i++;
      fast = cdr(fast);

      /* Safe because we would have already returned if `fast'
	 encountered a non-pair. */
      slow = cdr(slow);
      if (fast == slow)
        {
	  /* the fast pointer has looped back around and caught up
	     with the slow pointer, hence the structure is circular,
	     not of finite length, and therefore not a list */
	  return -1;
        }
    }
}

MINA op_execute(scheme sc ,scm_opcode op)
{
  MINA x;
  scm_num v;
  comp_func_t comp = NULL;

  switch(op)
    {
    case OP_NOT:        /* not */
      s_retbool(is_false(car(sc->args)));
    case OP_BOOLP:       /* boolean? */
      s_retbool(car(sc->args) == sc->F || car(sc->args) == sc->T);
    case OP_EOFOBJP:       /* boolean? */
      s_retbool(car(sc->args) == sc->EOF_OBJ);
    case OP_NULLP:       /* null? */
      s_retbool(car(sc->args) == sc->NIL);
    case OP_NUMEQ:      /* = */
    case OP_LESS:       /* < */
    case OP_GRE:        /* > */
    case OP_LEQ:     
  }
