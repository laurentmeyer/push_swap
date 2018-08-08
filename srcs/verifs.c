#include "push_swap.h"

int swappable_increasing(int *array, int len)
{
	int	*copy;
	int	i;

	if (len <= 2)
		return (1);
	if (NULL == (copy = (int *)malloc(len * sizeof(int))))
		return (ERR);
	ft_memcpy(copy, array, len * sizeof(int));
	i = 0;
	while (++i < len)
		if (copy[i - 1] > copy[i])
		{
			ft_swap_int(copy + i - 1, copy + i);
			++i;
		}
	i = 0;
	while (i < len - 1 && copy[i] < copy[i + 1])
		++i;
	free(copy);
	return (i == len);
}

int swappable_decreasing(int *array, int len)
{
	int	*copy;
	int	i;

	if (len <= 2)
		return (1);
	if (NULL == (copy = (int *)malloc(len * sizeof(int))))
		return (ERR);
	ft_memcpy(copy, array, len * sizeof(int));
	i = 0;
	while (++i < len)
		if (copy[i - 1] < copy[i])
		{
			ft_swap_int(copy + i - 1, copy + i);
			++i;
		}
	i = 0;
	while (i < len - 1 && copy[i] > copy[i + 1])
		++i;
	free(copy);
	return (i == len - 1);
}

int		sortable_by_rotation(t_int_array *array, int ascending)
{
	int	i;
	int	breaks;

	if (array->count <= 2)
		return (1);
	i = 0;
	breaks = 0;
	while (i < array->count - 1)
	{
		if ((ASCENDING == ascending && (array->data)[i] > (array->data)[i + 1])
			|| (DESCENDING == ascending && (array->data)[i] < (array->data)[i + 1]))
			breaks++;
		++i;
	}
	return (breaks < 2);
}

int  is_sorted(t_int_array *array)
{
  int  i;
 
  if (array->count == 1)
    return (1);
	i = 0;
  while (i < array->count - 1)
  {
    if ((array->data)[i] <= (array->data)[i + 1])
      return (0);
    ++i;
  }
  return (1);
}