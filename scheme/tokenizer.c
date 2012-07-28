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
#include <scheme/token.h>

static inline char scheme_getchar(scheme sc)
{
  /* TODO: finish this proc, but we'll use getchar() instead first.
   * 	1. we need to record some status while reading chars.
   *	2. maybe something parellel could be added...dunno
   *	3. before we implement a real I/O buffer, use the buffer in struct scheme.
   */

  return sc->cnt_cur? getchar() : sc->strbuff[sc->bp++];
}

static inline void scheme_backchar(scheme sc)
{
  sc->cnt_cur++;
  sc->
}

static inline int is_one_of(const char *str ,char ch)
{
  char *ptr = str;

  while(*ptr != ch && '\0' != *ptr)
    ptr++;
    
  return '0' == *ptr ? 0 : 1;
}

scm_tok scheme_tokenizer(scheme sc)
{
 SK_BEGIN:	// tail-recursive eliminate

  char c = skipspace(sc);

  if(EOF == c)
    return TOK_EOF;
  
  switch(c=scheme_getchar(sc))
    {
    case EOF:
      return TOK_EOF;
    case '(':
      return TOK_LPAREN;
    case ')':
      return TOK_RPAREN;
    case '.':
      c=scheme_getchar(sc);
      if(is_one_of(" \n\t" ,c))
	return TOK_DOT;
	
      scheme_backchar(sc ,c);
      scheme_backchar(sc ,'.');
      return TOK_ATOM;
    case '\'':
      return TOK_QUOTE;
    case ';':
      while ((c=scheme_getchar(sc)) != '\n' && EOF != c)
	;
      if(EOF == c)
	return TOK_EOF;
      else
	goto SK_BEGIN;
    case '"':
      return TOK_QUASIQUOTE;
    case BACKQUOTE:
      return TOK_BACKQUOTE;
    case ',':
      if('@' == (c=scheme_getchar(sc)))
	return TOK_ATMARK;
	
      scheme_backchar(sc,c);
      return TOK_COMMA;
    case '#':
      c=scheme_getchar(sc);
      if('(' == c)
	{
	  return (TOK_VEC);
	}
      else if('!' == c)
	{
	  while('\n' != (c=scheme_getchar(sc)) && EOF != c)
	    ;
	if(c == EOF)
	  return TOK_EOF;
	else
	  goto SK_BEGIN;
	}
      else
	{
	  scheme_backchar(sc ,c);
	  if(is_one_of(" tfodxb\\" ,c))
	    return TOK_SHARP_CONST;
	  else
	    return TOK_SHARP;
	}
    default:
      scheme_backchar(sc ,c);
      return (TOK_ATOM);
    }
}

