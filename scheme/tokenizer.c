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

scm_tok scheme_tokenizer(scheme sc)
{
 SK_BEGIN:	// tail-recursive eliminate
  char c = skipspace(sc);
  if(EOF == c)
    return TOK_EOF;
  
  switch(c=inchar(sc))
    {
    case EOF:
      return TOK_EOF;
    case '(':
      return TOK_LPAREN;
    case ')':
      return TOK_RPAREN;
    case '.':
      c=inchar(sc);
      if(is_one_of(" \n\t",c))
	return TOK_DOT;
	
      backchar(sc,c);
      backchar(sc,'.');
      return TOK_ATOM;
    case '\'':
      return TOK_QUOTE;
    case ';':
      while ((c=inchar(sc)) != '\n' && c!=EOF)
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
      if('@' == (c=inchar(sc)))
	return TOK_ATMARK;
	
      backchar(sc,c);
      return TOK_COMMA;
    case '#':
      c=inchar(sc);
      if('(' == c)
	{
	  return (TOK_VEC);
	}
      else if(c == '!')
	{
	  while((c=inchar(sc)) != '\n' && c!=EOF)
	    ;
	if(c == EOF)
	  return TOK_EOF;
	else
	  goto SK_BEGIN;
	}
      else
	{
	  backchar(sc,c);
	  if(is_one_of(" tfodxb\\",c))
	    return TOK_SHARP_CONST;
	  else
	    return TOK_SHARP;
	}
    default:
      backchar(sc,c);
      return (TOK_ATOM);
    }
}

