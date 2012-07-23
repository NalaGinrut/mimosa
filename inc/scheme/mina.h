#ifndef __MIMOSA_SCHEME_MINA_H__
#define __MIMOSA_SCHEME_MINA_H__
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

typedef enum MINA_type
  {
    BOOL ,LIST ,CONS ,NUMBER ,SYMBOL ,STRING ,
    CONTINUATION ,PROCEDURE ,CLOSURE ,CHAR ,
    SYNTAX
  } mina_type;

/* MINA is the primitive object structure */
typedef struct MINA
{
  mina_type type;
  union
  {
    struct
    {
      u16_t	_len;
      char	*_svalue;
    } _string;

    struct
    {
      char	*_svalue;
    } _symbol;
    
    // use 32bit for efficient reason.
    struct
    {
      u32_t	_ivalue;
    } _number;

    struct
    {
      u8_t	_bvalue; // 1 for TRUE ,0 for FALSE
    } _bool;

    struct
    {
      char	_ch;
    } _char;
    
    struct
    {
      void	*_entry;
      void	*_env;
    } _closure;

    // TODO: continuation & procedure & syntax
    
    struct
    {
      u32_t	_len;
      struct MINA *_lyst;
    } _list;
    
    struct
    {
      struct MINA *_car;
      struct MINA *_cdr;
    } _cons;
  } _object;
} *MINA;

#define MINA_TYPE(m)	((m)->type)
#define IS_STRING(m)	(STRING == MINA_TYPE(m))
#define STRING_VAL(m)	((m)->_object._string._svalue)
#define STRING_LEN(m)	((m)->_object._string._len)

#define IS_NUMBER(m)	(NUMBER == MINA_TYPE(m))
#define NUMBER_VAL(m)	((m)->_object._number._ivalue)

#define IS_CONS(m)	(CONS == MINA_TYPE(m))
#define CAR(m)          ((m)->_object._cons._car)
#define CDR(m)          ((m)->_object._cons._cdr)

#define IS_SYMBOL(m)	(SYMBOL == MINA_TYPE(m))
#define SYMBOL_VAL(s)	((s)->_symbol->_svalue)
// for symbol ,we only compare their head pointer
#define SYMBOL_EQ(s1 ,s2)	SYMBOL_VAL(s1) == SYMBOL_VAL(s2)

#define IS_SYNTAX(m)	(SYNTAX == MINA_TYPE(m))
#define IS_PROC(m)	(PROCEDURE == MINA_TYPE(m))
#define SYNTAX_NAME(m)	strvalue(car(p))

static inline car(MINA mobj);
static inline cdr(MINA mobj);

static inline car(MINA mobj)
{
  if(!mobj)
    panic("mobj is a NULL ptr!\n");

  return CAR(mobj);
}

static inline cdr(MINA mobj)
{
  if(!mobj)
    panic("mobj is a NULL ptr!\n");

  return CDR(mobj);
}

#define caar(m)         car(car(m))
#define cadr(m)         car(cdr(m))
#define cdar(m)         cdr(car(m))
#define cddr(m)         cdr(cdr(m))
#define cadar(m)        car(cdr(car(m)))
#define caddr(m)        car(cdr(cdr(m)))
#define cadaar(m)       car(cdr(car(car(m))))
#define cadddr(m)       car(cdr(cdr(cdr(m))))
#define cddddr(m)       cdr(cdr(cdr(cdr(m))))

void MINA_show_type(MINA mobj);
char *MINA_get_type(MINA mobj);
// type_obj type_of(MINA m);


#endif // End of __MIMOSA_SCHEME_MINA_H__;
