#include "push_swap.h"

// int		sortable_by_rotation(t_stack stack, int ascending)
// {
// 	int	i;
// 	int	breaks;

// 	if (stack.count <= 2)
// 		return (1);
	
// 	i = 0;
// 	breaks = 0;
// 	while (i < stack.count - 1)
// 	{
// 		if ((ascending && stack.elements[i] > stack.elements[i + 1])
// 			|| (!ascending && stack.elements[i] < stack.elements[i + 1]))
// 			breaks++;
// 		++i;
// 	}
// 	return (breaks < 2);
// }

// int		sortable_by_rotation(t_stack stack, int ascending)
// {
// 	int	i;
// 	int	breaks;

// 	if (stack.count <= 2)
// 		return (1);
	
// 	i = 0;
// 	breaks = 0;
// 	while (i < stack.count - 1)
// 	{
// 		if ((ascending && stack.elements[i] > stack.elements[i + 1])
// 			|| (!ascending && stack.elements[i] < stack.elements[i + 1]))
// 			breaks++;
// 		++i;
// 	}
// 	return (breaks < 2);
// }

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