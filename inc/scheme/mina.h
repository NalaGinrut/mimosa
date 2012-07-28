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

#include <types.h>
#include <bits.h>

typedef enum MINA_type
  {
    BOOL ,LIST ,CONS ,NUMBER ,SYMBOL ,STRING ,PAIR ,
    CONTINUATION ,PROCEDURE ,CLOSURE ,CHAR ,SYNTAX
  } mina_type;

// ENHANCEME: use u32_t and a tagged style to flag the status&type rather than enum.
/* We can only afford 32 types ,an atom example: NUMBER|MINA_ATOM.
 */
#define MINA_ATOM	0x80
#define MINA_IMMU	0x40 // immutable object
#define MINA_MARK	0x20 // marked by GC	

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
      char	_cvalue;
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

#define IS_CHAR(m)	(CHAR == MINA_TYPE(m))
#define CHAR_VAL(m)	((m)->_object._number._cvalue)

#define IS_CONS(m)	(CONS == MINA_TYPE(m))
#define CAR(m)          ((m)->_object._cons._car)
#define CDR(m)          ((m)->_object._cons._cdr)

#define IS_SYMBOL(m)	(SYMBOL == MINA_TYPE(m))
#define SYMBOL_VAL(s)	((s)->_symbol->_svalue)
// for symbol ,we only compare their head pointer
#define SYMBOL_EQ(s1 ,s2)	SYMBOL_VAL(s1) == SYMBOL_VAL(s2)

#define IS_SYNTAX(m)	(SYNTAX == MINA_TYPE(m))
#define IS_PROC(m)	(PROCEDURE == MINA_TYPE(m))
#define SYNTAX_NAME(m)	STRING_VAL(car(m))

static inline int IS_IMMUTABLE(MINA m) { return (MINA_TYPE(m)&IMMUTABLE); }
static inline void SET_IMMUTABLE(MINA m) { MINA_TYPE(m) |= IMMUTABLE; }

static inline int IS_INTEGER(mina m)
{
  return IS_NUMBER(m) && ((m)->_object._number.is_fixnum);
}

static inline int IS_REAL(mina m)
{
  return IS_NUMBER(m) && (!(m)->_object._number.is_fixnum);
}


#define car(mobj)	( (!(mobj) && panic("mobj is a NULL ptr!\n")) || CAR(mobj) )
#define cdr(mobj)	( (!(mobj) && panic("mobj is a NULL ptr!\n")) || CDR(mobj) )

#define caar(m)         car(car(m))
#define cadr(m)         car(cdr(m))
#define cdar(m)         cdr(car(m))
#define cddr(m)         cdr(cdr(m))
#define cadar(m)        car(cdr(car(m)))
#define caddr(m)        car(cdr(cdr(m)))
#define cadaar(m)       car(cdr(car(car(m))))
#define cadddr(m)       car(cdr(cdr(cdr(m))))
#define cddddr(m)       cdr(cdr(cdr(cdr(m))))

typedef void* (*ss_malloc_t)(size_t);
typedef void (*ss_free_t)(void*);

struct Scheme_System
{
  ss_malloc_t malloc;
  ss_free_t free;
  
  // return code
  s32_t retcode; // FIXME: should we use retval.h instead?
  // status record
  u32_t status;	// see SS_* which stands for Scheme-Status

  /* We use 4 registers. */
  MINA args;	/* register for arguments of function */
  MINA env;	/* stack register for current environment */
  MINA code;	/* register for current code */
  MINA dump;	/* stack register for next evaluation */

  MINA sink;            /* when malloc fails */
  MINA NIL;             /* special cell representing empty cell */
  struct MINA _NIL;
  MINA T;               /* special cell representing #t */
  struct MINA _T;
  MINA F;               /* special cell representing #f */
  struct MINA _F;
  MINA EOF_OBJ;         /* special cell representing end-of-file object */
  struct MINA _EOF_OBJ;

  /* FIXME: oblist is actually a symbol table ,
   *	    but we need a more efficient one like RBtree or hash table.
   */
  MINA oblist;          /* pointer to symbol table */
  MINA global_env;      /* pointer to global environment */
  MINA c_nest;          /* stack for nested calls from C */

  MINA free_cell;    /* pointer to top of free cells */
  u32_t fcells;         /* # of free cells */
  
  /* global pointers to special symbols */
  MINA LAMBDA;		/* pointer to syntax lambda */
  MINA QUOTE;           /* pointer to syntax quote */

  MINA QUASIQUOTE;	/* pointer to symbol quasiquote */
  MINA UNQUOTE;         /* pointer to symbol unquote */
  MINA UNQUOTESP;       /* pointer to symbol unquote-splicing */
  MINA FEED_TO;         /* => */
  MINA COLON_HOOK;      /* *colon-hook* */
  MINA ERROR_HOOK;      /* *error-hook* */
  MINA SHARP_HOOK;	/* *sharp-hook* */
  MINA COMPILE_HOOK;	/* *compile-hook* */

  MINA inport;
  MINA outport;
  MINA save_inport;
  MINA loadport;

  /* NOTE: buffer should be a stack, which means we put first char in
   * STRBUFFSIZE-1 position.
   */
#define LINESIZE 1024
  char linebuff[LINESIZE];
#define STRBUFFSIZE 256
  char strbuff[STRBUFFSIZE];
  size_t cnt_cur; // current buffer content bytes count
  size_t bp; // current buffer pointer
  
  scm_tok tok; // current token
  MINA value;
  u32_t op;

  void *ext_data;     /* For the benefit of foreign functions */
  u32_t gensym_cnt;

  void *dump_base;	 /* pointer to base of allocated dump stack */
  size_t dump_size;	 /* number of frames allocated for dump stack */
};

// Scheme Status
#define SS_TRACING   	_B(0) // in tracing mode
#define SS_INTRACTIVE	_B(1) // for an interactive REPL
#define SS_NESTING	_B(2) // nesting status?
#define SS_GC_VERBOSE	_B(3) // if gc_verbose is not zero, print gc status
#define SS_NOMEM	_B(4) // if malloc has failed
#define SS_PRINT	_B(5) // print flag
#define SS_QUIET	_B(6) // if not zero, print banner, prompt, results
#define SS_AEF		_B(7) // all errors fatal

/* num, for generic arithmetic */
typedef struct Scheme_Number
{
  union
  {
    long ivalue;
    double rvalue;
  } value;

  u8_t is_fixnum;
} scm_num;

typedef int (*comp_func_t)(scm_num ,scm_num);

// functions declaration
void* scheme_malloc(size_t size);
void scheme_free(void* ptr);

void MINA_show_type(MINA mobj);
char *MINA_get_type(MINA mobj);
// type_obj type_of(MINA m);

MINA MINA_cons(MINA a ,MINA b);

#endif // End of __MIMOSA_SCHEME_MINA_H__;
