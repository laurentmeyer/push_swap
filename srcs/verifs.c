#include "push_swap.h"

// int         swappable_increasing(t_int_array *array, int start)
// {
//     int i;

//     i = start;
//     if (i >= array->count - 2)
//         return (1);
//     while ((array->data)[i] <= (array->data)[i + 1] && i < array->count - 2)
//         ++i;
//     if (i == (array->count - 1))
//         return (1);
//     if ((array->data)[i + 1] > (array->data)[i + 2])
//         return (0);
//     return (swappable_increasing(array, i + 2));
// }

// int		sortable_by_rotation(t_int_array array, int ascending)
// {
// 	int	i;
// 	int	breaks;

// 	if (array.count <= 2)
// 		return (1);
	
// 	i = 0;
// 	breaks = 0;
// 	while (i < array.count - 1)
// 	{
// 		if ((ascending && array.data[i] > array.data[i + 1])
// 			|| (!ascending && array.data[i] < array.data[i + 1]))
// 			breaks++;
// 		++i;
// 	}
// 	return (breaks < 2);
// }

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