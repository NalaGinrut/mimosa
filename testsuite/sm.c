#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <gdsl.h>

typedef unsigned int u32_t;
typedef u32_t state_t;

typedef int (*sm_handler_t)(void *data);

struct State_Machine
{
  state_t state;
  struct State_Machine *next;
  sm_handler_t handle;
}sm_t;

int sm_init(char *name ,

int main()
{
  return 0;
}
