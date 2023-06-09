#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"

struct _s_stack
{
  stack_elem *elems;
  unsigned int len;
  unsigned int cap;
};

stack stack_empty()
{
  stack s = malloc(sizeof(struct _s_stack));
  s->len = 0;
  s->cap = 0;
  s->elems = NULL;
  return s;
}

stack stack_push(stack s, stack_elem e)
{
  assert(s != NULL);
  assert(s->cap >= s->len);
  // Reservar memoria si es necesario
  if(s->cap == s->len) {
    size_t newcap = s->len == 0 ? 1 : 2*s->len;
    s->elems = realloc(s->elems, newcap*sizeof(stack_elem));
    s->cap = newcap;
  }
  (s->elems)[s->len] = e;
  ++(s->len);

  return s;
}

stack stack_pop(stack s)
{
  assert(s != NULL);
  --(s->len);
  return s;
}

unsigned int stack_size(stack s)
{
  assert(s != NULL);
  return s->len;
}

stack_elem stack_top(stack s)
{
  assert(s != NULL);
  assert(s->len > 0);
  assert(s->elems != NULL);
  return s->elems[(s->len)-1];
}

bool stack_is_empty(stack s)
{
  assert(s != NULL);
  return s->len == 0;
}

stack_elem *stack_to_array(stack s)
{
  assert(s != NULL);
  stack_elem *arr = NULL;
  if(s->len) {
    arr = calloc(s->len, sizeof(stack_elem));
    arr = memcpy(arr, s->elems, s->len*sizeof(stack_elem));
  }
  return arr;
}

stack stack_destroy(stack s)
{
  assert(s != NULL);
  free(s->elems);
  free(s);
  return NULL;
}