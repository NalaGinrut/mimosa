#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <malloc.h>
#include <gdsl.h>

#define INDEX	1
#define VALUE	'a'




typedef struct AAA
{
  int index;
  int value;
} elem_t;

static void trav_list_fwd (gdsl_list_t l);

gdsl_element_t make_elem (void *data);
void free_elem (gdsl_element_t elem);


int
main ()
{
  gdsl_list_t list = gdsl_list_alloc ("char list",
				      NULL,
				      NULL);
  int i = 0;

  for (i = 0; i < 60000; i++)
    {
      elem_t *e = (elem_t *) malloc (sizeof (elem_t));
      e->index = INDEX + i;
      e->value = VALUE;
      gdsl_list_insert_head (list, e);
    }

  trav_list_fwd (list);
  gdsl_list_free (list);

  return 0;
}


static void
trav_list_fwd (gdsl_list_t l)
{
  gdsl_element_t e;
  gdsl_list_cursor_t c = gdsl_list_cursor_alloc (l);

  printf ("%s (->) = ( ", gdsl_list_get_name (l));

  for (gdsl_list_cursor_move_to_head (c);
       (e = gdsl_list_cursor_get_content (c));
       gdsl_list_cursor_step_forward (c))
    {
      elem_t *content = (elem_t *) e;
      printf ("index: %d ; value: %c\n", content->index, content->value);
    }

  printf (")\n");

  gdsl_list_cursor_free (c);
}

gdsl_element_t
make_elem (void *data)
{
  return (gdsl_element_t) malloc (sizeof (elem_t));
}

void
free_elem (gdsl_element_t elem)
{
  free (elem);
}
