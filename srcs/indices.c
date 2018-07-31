#include "push_swap.h"
#include <limits.h>

int		max_index(t_int_array *array)
{
	int	index;
	int	i;
	int	max;

	i = 0;
	index = 0;
	max = INT_MIN;
	while (i < array->count)
	{
		if ((array->data)[i] > max)
		{
			max = array->data[i];
			index = i;
		}
		i++;
	}
	return (index);
}

