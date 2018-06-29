#include "push_swap.h"

int  is_sorted(t_stack stack)
{
  int  i;
 
  if (stack.count == 1)
    return (1);
  i = 0;
  while (i < stack.count - 1)
  {
    if ((stack.elements)[i] <= (stack.elements)[i + 1])
      return (0);
    ++i;
  }
  return (1);
}