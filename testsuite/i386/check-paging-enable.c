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


// This program could help you to check the paging_enabling order problem;

#include <stdio.h>

#define PG     	(0x1)
#define PAE	((0x1)<<1)
#define LME	((0x1)<<2)

#define	P_S1	0
#define	P_S2	1
#define	P_S3	2
#define	L_S1	3
#define	L_S2	4
#define	A_S1	5
#define	ALL	6

#define OK	1
#define NO	0

typedef struct STATE_MACHINE
{
  int p_order;
  int GP;
  int next;
}sm_t __attribute__((aligned(4)));

sm_t *sm_list[8];
sm_t *path[10];// FIXME: use static list temporally,
               // change it to dynamically list;

enum operation
{
  clr=0 ,set=1
}op;

sm_t current={ 0 ,0 ,0 };

// function declaration;
int set_it(int what);
int clr_it(int what);
int begin();
int handle_sel(int sel);
int check_sm(int selector);
int display_path();
int display_op();
int display_sel();


int main()
{


  return 0;
}

int set_it(int what)
{
  int ret=OK;

  current.p_order |= what;
  
  if( current.p_order > 7 ||
      current.p_order == 5 )
    ret=NO;

  return OK;
}

int clr_it(int what)
{
  int ret=OK;
  
  current.p_order &= what;
  
  if( current.p_order > 7 ||
      current.p_order == 5 )
    ret=NO;

  return OK;
}

int begin()
{	
  switch( getchar() )
    {
    case 's':
      op=set;
      printf("now you chose to 'set'!\n"); 
      goto handle;
    case 'c':
      op=clr;
      printf("now you chose to 'clr'!\n");
      goto handle;
    default:
      display_op();
    }
  
  return 0;
}

int handle_sel(int sel)
{	
  int ret=OK;
  switch(op)
    {
    case set:
      ret=set_it(sel);
      break;
    case clr:
      ret=clr_it(sel);
      break;
    default:
      printf("operation error! please check your program!\n");
      exit(1);
    }
  return ret;
}

int check_sm(int sel)
{
  switch(sel)
    {	
    case 'p':
      handle_sel(PG);
      break;
    case 'a':
      handle_sel(PAE);
      break;
    case 'l':
      handle_sel(LME);
      break;
    case 'q':
      exit(0);
    default:
      greeting();
    }
  
  return 0;
}

int display_path()
{
  return 0;
}

int display_op()
{}

int display_sel()
{}
