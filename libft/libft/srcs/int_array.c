#include "int_array.h"
#include "libft.h"
#include <limits.h>
#include <stdlib.h>

int				int_first(t_int_array array)
{
	return ((array.data)[0]);
}

int				int_last(t_int_array array)
{
	return ((array.data)[array.count - 1]);
}

// int				int_max(t_int_array array)
// {
// 	int	i;
// 	int max;
// 	int	cur;

// 	i = 0;
// 	max = INT_MIN;
// 	while (i < array.count)
// 	{
// 		if ((cur = (array.data)[i]) > max)
// 			max = cur;
// 		i++;
// 	}
// 	return (max);
// }

void	free_int_array(t_int_array *array)
{
	free(array->data);
	free(array);
}

int		int_pop(t_int_array *array)
{
	array->count -= 1;
	return ((array->data)[array->count]);
}

void	int_push(t_int_array *array, int i)
{
	(array->data)[array->count] = i;
	array->count += 1;
}

void	int_set(t_int_array *array, int position, int value)
{
	(array->data)[position] = value;
	if (array->count < position + 1)
		array->count = position + 1;
}

int				int_index(t_int_array *array, int i)
{
	int	j;

	j = 0;
	while (j < array->count)
	{
		if ((array->data)[j] == i)
			return (j);
		j++;
	}
	return (-1);
}

int		int_remove(t_int_array *array, int index)
{
	int	i;
	int	res;

	i = index;
	array->count -= 1;
	res = (array->data)[index];
	while (i < array->count)
	{
		(array->data)[i] = (array->data)[i + 1];
		++i;
	}
	return (res);
}

t_int_array		*new_int_array(int capacity)
{
	t_int_array	*res;
	int			i;

	if (NULL == (res = (t_int_array *)malloc(sizeof(t_int_array))))
		return (NULL);
	i = 1;
	while (i < capacity)
		i *= 2;
	if (NULL == (res->data = (int *)malloc(i * sizeof(int))))
		return (NULL);
	res->capacity = i;
	res->count = 0;
	return (res);
}

t_int_array		*copy_int_array(t_int_array *src)
{
	t_int_array	*res;

	if (NULL == (res = (t_int_array *)malloc(sizeof(t_int_array))))
		return (NULL);
	if (NULL == (res->data = (int *)malloc(src->capacity * sizeof(int))))
		return (NULL);
	res->capacity = src->capacity;
	res->count = src->count;
	ft_memcpy(res->data, src->data, res->count * sizeof(int));
	return (res);
}