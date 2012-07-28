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

void* scheme_malloc(size_t size)
{
  /* TODO: This function will be insteaded by kernel-malloc
   *	   Now we just use a simple stack memory alloc to emulate it.
   */

  
  
}

void scheme_free(void* ptr)
{
  // TODO: use kernel-free
}

void scheme_gc(MINA x ,MINA y)
{
  /* TODO: Try to implement a real-time GC.
   * 	   But actually we don't need it at present.
   */
}

MINA MINA_new(scheme sc ,MINA a ,MINA b)
{
  register MINA x;

  if(NIL == free_cell) // if pool is dry up
    {
      scheme_gc(a ,b);

      if(!alloc_cellseg(1))
	panic("run out of cells  --- unable to recover cells");
    }
  
  x = free_cell;
  free_cell = cdr(x);
  fcells--;
  return (x);
}

MINA MINA_make_string(char   *str)
{
  register MINA x = MINA_new(sc ,NIL, NIL);

  strvalue(x) = store_string(str);
  type(x) = (T_STRING | T_ATOM);
  keynum(x) = (short) (-1);
  return (x);
}

#define STR_IS_SYMNAME(s ,m)	strcmp(s ,SYMBOL_VAL(car(m)))
MINA MINA_make_symbol(scheme sc ,char *name)
{
  register MINA x = sc->oblist;

  // checkout symbol table
  while(x != sc->NIL && !STR_IS_SYMNAME(name ,x))
    x = cdr(x);

  // find a valid obj whose symbol name is "name" then return it
  if(x != NIL)
    return car(x);

  // no such an obj ,then we create a new one
  x = cons(MINA_make_string(name) ,NIL);
  MINA_TYPE(x) = SYMBOL;
  oblist = cons(x ,oblist); // insert new obj into symbol table
  return x;
}

/* make symbol or number atom from string */
MINA MINA_make_atom(char *str)
{
  char c;
  char *ptr = NULL;

  ptr = str;
  if(!isdigit(c = *p++))
    {
      if((c != '+' && c != '-') || !isdigit(*p))
	return MINA_make_symbol(q);
    }
  
  for( ; (c = *p) != 0; ++p)
    if(!isdigit(c))
      return MINA_make_symbol(q);

  return MINA_make_number(atol(q));
}

void scheme_init(scheme sc)
{
  int i ,n = sizeof(dispatch_table)/sizeof(dispatch_table[0]);
  MINA x;

  num_zero.is_fixnum=1;
  num_zero.value.ivalue=0;
  num_one.is_fixnum=1;
  num_one.value.ivalue=1;

  sc->gensym_cnt = 0;
  sc->malloc = scheme_malloc;
  sc->free = scheme_free;
  sc->last_cell_seg = -1;
  sc->sink = &sc->_sink;
  sc->NIL = &sc->_NIL;
  sc->T = &sc->_T;
  sc->F = &sc->_F;
  sc->EOF_OBJ = &sc->_EOF_OBJ;
  sc->oblist = &sc->_NIL;
  sc->free_cell = &sc->_NIL;
  sc->fcells = 0;
  sc->status |= (SS_INTRACTIVE | SS_NESTING) & ~(SS_NOMEM | SS_QUIET);

  dump_stack_initialize(sc);
  sc->code = &sc->_NIL;

  /* init sc->NIL */
  MINA_TYPE(sc->NIL) = (MINA_ATOM | MINA_MARK);
  car(sc->NIL) = cdr(sc->NIL) = sc->NIL;
  /* init T */
  MINA_TYPE(sc->T) = (MINA_ATOM | MINA_MARK);
  car(sc->T) = cdr(sc->T) = sc->T;
  /* init F */
  MINA_TYPE(sc->F) = (MINA_ATOM | MINA_MARK);
  car(sc->F) = cdr(sc->F) = sc->F;
  /* init sink */
  MINA_TYPE(sc->sink) = (PAIR | MINA_MARK);
  car(sc->sink) = sc->NIL;
  /* init c_nest */
  sc->c_nest = sc->NIL;

  sc->oblist = oblist_initial_value(sc);
  /* init global_env */
  new_frame_in_env(sc, sc->NIL);
  sc->global_env = sc->envir;
  /* init else */
  x = mk_symbol(sc,"else");
  new_slot_in_env(sc, x, sc->T);

  assign_syntax(sc, "lambda");
  assign_syntax(sc, "quote");
  assign_syntax(sc, "define");
  assign_syntax(sc, "if");
  assign_syntax(sc, "begin");
  assign_syntax(sc, "set!");
  assign_syntax(sc, "let");
  assign_syntax(sc, "let*");
  assign_syntax(sc, "letrec");
  assign_syntax(sc, "cond");
  assign_syntax(sc, "delay");
  assign_syntax(sc, "and");
  assign_syntax(sc, "or");
  assign_syntax(sc, "cons-stream");
  assign_syntax(sc, "macro");
  assign_syntax(sc, "case");

  for(i=0; i<n; i++) {
    if(dispatch_table[i].name!=0) {
      assign_proc(sc, (enum scheme_opcodes)i, dispatch_table[i].name);
    }
  }

  /* initialization of global pointers to special symbols */
  sc->LAMBDA = mk_symbol(sc, "lambda");
  sc->QUOTE = mk_symbol(sc, "quote");
  sc->QQUOTE = mk_symbol(sc, "quasiquote");
  sc->UNQUOTE = mk_symbol(sc, "unquote");
  sc->UNQUOTESP = mk_symbol(sc, "unquote-splicing");
  sc->FEED_TO = mk_symbol(sc, "=>");
  sc->COLON_HOOK = mk_symbol(sc,"*colon-hook*");
  sc->ERROR_HOOK = mk_symbol(sc, "*error-hook*");
  sc->SHARP_HOOK = mk_symbol(sc, "*sharp-hook*");
  sc->COMPILE_HOOK = mk_symbol(sc, "*compile-hook*");

  return !sc->no_memory;
}

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

char *MINA_typeof(MINA mobj)
{
  /* TODO: finish this function after memory-alloc implementation is done.
   *	   It'll return the type as a string. So we need strndup. 
   */
}

MINA MINA_cons(MINA a ,MINA b)
{
  register MINA x = get_cell(a ,b);
  
  MINA_TYPE(x) = PAIR;
  car(x) = a;
  cdr(x) = b;

  return (x);
}


/* TODO: we need something like type_of to get the type and use the type itself as an object.
 */
// type_obj type_of(MINA m) {}

