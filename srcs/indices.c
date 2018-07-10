#include "push_swap.h"
#include <limits.h>

int		max_index(t_stack stack)
{
	int	index;
	int	i;
	int	max;

	i = 0;
	index = 0;
	max = INT_MIN;
	while (i < stack.count)
	{
		if (stack.elements[i] > max)
		{
			max = stack.elements[i];
			index = i;
		}
		i++;
	}
	return (index);
}

int		min_index(t_stack stack)
{
	int	index;
	int	i;
	int	min;

	i = 0;
	index = 0;
	min = INT_MAX;
	while (i < stack.count)
	{
		if (stack.elements[i] < min)
		{
			min = stack.elements[i];
			index = i;
		}
		i++;
	}
	return (index);
}
