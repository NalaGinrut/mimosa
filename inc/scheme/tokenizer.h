#ifndef __MIMOSA_SCHEME_TOKENIZER_H__
#define __MIMOSA_SCHEME_TOKENIZER_H__
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

typedef enum Scheme_Token
  { TOK_EOF = -1 ,TOK_LPAREN ,TOK_RPAREN ,TOK_DOT ,
    TOK_ATOM ,TOK_QUOTE ,TOK_COMMENT ,TOK_QUASIQUOTE ,
    TOK_BACKQUOTE ,TOK_COMMA ,TOK_ATMARK ,TOK_SHARP ,TOK_SHARP_CONST ,
    TOK_VECTOR ,TOK_LITERAL
  } scm_tok;

scm_tok scheme_tokenizer(scheme sc);


#endif // End of __MIMOSA_SCHEME_TOKENIZER_H__;
