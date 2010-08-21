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
#include <stdlib.h>
#include <gdsl.h>


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
  int stop;
} sm_t __attribute__ ((aligned (4)));

sm_t *sm_list[8];
sm_t *path[10];			// FIXME: use static list temporally,
	       // change it to dynamically list;

enum operation
{
  clr = 0, set = 1
} op;

sm_t current = { 0, 0, 0, NO };

//gdsl_list_t g_list;

// function declaration;
int set_it (int what);
int clr_it (int what);
int begin ();
int handle_sel (int sel);
int check_op ();
int check_sel ();
int display_path ();
int display_op ();
int display_sel ();
int display_map();

int
main ()
{

	//	g_list=gdsl_list_alloc("global list" ,NULL ,NULL);
	
	begin ();
	return 0;
}

int
set_it (int what)
{
  int ret = OK;

  current.p_order |= what;

  if (current.p_order > 7 || current.p_order == 5)
    ret = NO;

  return OK;
}

int
clr_it (int what)
{
  int ret = OK;

  current.p_order &= what;

  if (current.p_order > 7 || current.p_order == 5)
    ret = NO;

  return OK;
}

int
begin ()
{
  while (current.GP == NO && current.stop == NO)
    {
      check_op ();
      check_sel ();
    }

  display_path ();

  return 0;
}

int
check_op ()
{
  int ret = OK;
  int ch = 0;

  display_op ();

  while (ch = getchar ())
    {
      if (ch == '\n')
	continue;

      switch (ch)
	{
	case 's':
	  op = set;
	  printf ("now you chose to 'set'!\n");
	  goto handle;
	case 'c':
	  op = clr;
	  printf ("now you chose to 'clr'!\n");
	  goto handle;
	case 'f':
	  current.stop = OK;
	  goto handle;
	default:
	  display_op ();
	}
    }
handle:
  return ret;
}

int
handle_sel (int sel)
{
  int ret = OK;

  switch (op)
    {
    case set:
	    printf("now you chose PM\n");
      ret = set_it (sel);
      goto handle;
    case clr:
      ret = clr_it (sel);
      goto handle;
    default:
      printf ("operation error! please check your program!\n");
      exit (1);
    }
  
 handle:
  return ret;
}

int
check_sel ()
{
  int ret = OK;
  int ch = 0;

  if (current.stop == OK)
    return OK;

  display_sel ();

  while (ch = getchar ())
    {
      if (ch == '\n')
	continue;

      switch (ch)
	{
	case 'p':
	  ret = handle_sel (PG);
	  goto handle;
	case 'a':
	  ret = handle_sel (PAE);
	  goto handle;
	case 'l':
	  ret = handle_sel (LME);
	  goto handle;
	case 'q':
	  exit (0);
	default:
	  display_sel ();
	}
    }
  
 handle:
  return ret;
}

int
display_path ()
{
  printf ("path shows~~\n");
  return 0;
}

int
display_op ()
{
  printf ("Please chose a operator:\n"
	  "[S]et\n" "[C]lear\n" "[F]inish\n" "input your chose:");
  return 0;
}

int
display_sel ()
{
  printf ("Please chose which mode should be set:\n"
	  "[P]rotected Mode\n"
	  "Physical [A]ddress Extended\n" "[L]ME\n" "input your chose:");
  return 0;

}

int display_map()
{
	return 0;
}  
