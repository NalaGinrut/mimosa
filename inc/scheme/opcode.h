#ifndef __MIMOSA_SCHEME_OPCODE_H__
#define __MIMOSA_SCHEME_OPCODE_H__
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

/* operator code */
typedef enum scheme_opcode
  {
    OP_LOAD ,OP_T0LVL ,OP_T1LVL ,OP_READ ,OP_VALUEPRINT ,OP_EVAL ,
    OP_E0ARGS ,OP_E1ARGS ,OP_APPLY ,OP_DOMACRO ,OP_LAMBDA ,
    OP_QUOTE ,OP_DEF0 ,OP_DEF1 ,OP_BEGIN ,OP_IF0 ,OP_IF1 ,
    OP_SET0 ,OP_SET1 ,OP_LET0 ,OP_LET1 ,OP_LET2 ,OP_LET0AST ,
    OP_LET1AST ,OP_LET2AST ,OP_LET0REC ,OP_LET1REC ,OP_LET2REC ,
    OP_COND0 ,OP_COND1 ,OP_DELAY ,OP_AND0 ,OP_AND1 ,OP_OR0 ,
    OP_OR1 ,OP_C0STREAM ,OP_C1STREAM ,OP_0MACRO ,OP_1MACRO ,
    OP_CASE0 ,OP_CASE1 ,OP_CASE2 ,
    OP_PEVAL ,OP_PAPPLY ,OP_CONTINUATION ,OP_ADD ,OP_SUB ,
    OP_MUL ,OP_DIV ,OP_REM ,OP_CAR ,OP_CDR ,OP_CONS ,OP_SETCAR ,
    OP_SETCDR ,OP_NOT ,OP_BOOL ,OP_NULL ,OP_ZEROP ,OP_POSP ,
    OP_NEGP ,OP_NEQ ,OP_LESS ,OP_GRE ,OP_LEQ ,OP_GEQ ,OP_SYMBOL ,
    OP_NUMBER ,OP_STRING ,OP_PROC ,OP_PAIR ,OP_EQ ,OP_EQV ,
    OP_FORCE ,OP_WRITE ,OP_DISPLAY ,OP_NEWLINE ,OP_ERR0 ,OP_ERR1 ,
    OP_REVERSE ,OP_APPEND ,OP_PUT ,OP_GET ,OP_QUIT ,OP_GC ,
    OP_GCVERB ,OP_NEWSEGMENT ,OP_RDSEXPR ,OP_RDLIST ,OP_RDDOT ,
    OP_RDQUOTE ,OP_RDQQUOTE ,OP_RDUNQUOTE ,OP_RDUQTSP ,OP_P0LIST ,
    OP_P1LIST ,OP_LIST_LENGTH ,OP_ASSQ ,OP_PRINT_WIDTH ,OP_P0_WIDTH ,
    OP_P1_WIDTH ,OP_GET_CLOSURE ,OP_CLOSUREP ,OP_MACROP ,
  } scm_opcode;

#define is_true(p)       ((p) != sc->F)
#define is_false(p)      ((p) == sc->F)

#endif // End of __MIMOSA_SCHEME_OPCODE_H__;
