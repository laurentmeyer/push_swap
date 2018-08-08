#include "int_array.h"
#include "libft.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static void		reallocate(t_int_array *array)
{
	int	i;
	int	*data;

	if (array->capacity < array->count)
		array->capacity = array->count;
	i = 1;
	while (i <= array->capacity)
		i *= 2;
	if (NULL == (data = (int *)malloc(i * sizeof(int))))
	{
		ft_putstr_fd("could not reallocate array\n", STDERR_FILENO);
		exit(0);
	}
	i = 0;
	while (i < array->count)
	{
		data[i] = (array->data)[i];
		i++;
	}
	free(array->data);
	array->data = data;
}

int				int_first(t_int_array *array)
{
	return ((array->data)[0]);
}

int				int_last(t_int_array *array)
{
	return ((array->data)[array->count - 1]);
}

int				int_min(t_int_array *array)
{
	int	i;
	int min;
	int	cur;

	i = 0;
	min = INT_MAX;
	while (i < array->count)
	{
		if ((cur = (array->data)[i]) < min)
			min = cur;
		i++;
	}
	return (min);
}

int				int_max(t_int_array *array)
{
	int	i;
	int max;
	int	cur;

	i = 0;
	max = INT_MIN;
	while (i < array->count)
	{
		if ((cur = (array->data)[i]) > max)
			max = cur;
		i++;
	}
	return (max);
}

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
	if (array->count >= array->capacity)
		reallocate(array);
	(array->data)[array->count] = i;
	array->count += 1;
}

void			int_unshift(t_int_array *array, int value)
{
	int	i;

	if (array->count >= array->capacity)
		reallocate(array);
	i = array->count;
	while (i > 0)
	{
		(array->data)[i] = (array->data)[i - 1];
		--i;
	}
	(array->data)[0] = value;
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

void	int_insert(t_int_array *array, int index, int value)
{
	int	i;

	if (index < 0 || index >= array->count)
		return ;
	if (array->count >= array->capacity)
		reallocate(array);
	array->count += 1;
	i = array->count - 1;
	while (i > index)
	{
		(array->data)[i] = (array->data)[i - 1];
		i--;
	}
	(array->data)[index] = value;
}

int int_remove(t_int_array *array, int index)
{
	int i;
	int res;

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

t_int_array *new_int_array(int capacity)
{
	t_int_array *res;
	int i;

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
t_int_array *copy_int_array(t_int_array *src)
{
	t_int_array *res;

	if (NULL == (res = (t_int_array *)malloc(sizeof(t_int_array))))
		return (NULL);
	if (NULL == (res->data = (int *)malloc(src->capacity * sizeof(int))))
		return (NULL);
	res->capacity = src->capacity;
	res->count = src->count;
	ft_memcpy(res->data, src->data, res->count * sizeof(int));
	return (res);
}

int int_min_index(t_int_array *array)
{
	int index;
	int i;
	int min;

	i = 0;
	index = 0;
	min = INT_MAX;
	while (i < array->count)
	{
		if ((array->data)[i] < min)
		{
			min = (array->data)[i];
			index = i;
		}
		i++;
	}
	return (index);
}

t_int_array *upper_percentile(t_int_array *src, int percent)
{
	t_int_array *res;
	int keep;

	if (NULL == (res = copy_int_array(src)))
		return (NULL);
	keep = percent * (res->count) / 100;
	if (keep <= 0)
		keep = 1; // discutable
	while (res->count > keep)
		int_remove(res, int_min_index(res));
	return (res);
}

t_int_array *int_values_to_ranks(t_int_array *array)
{
	t_int_array *tmp;
	t_int_array *res;
	int min;
	int cur;

	if (!(tmp = copy_int_array(array)) || !(res = copy_int_array(array)))
		return (NULL);
	cur = 0;
	while (tmp->count > 0)
	{
		min = int_index(array, int_remove(tmp, int_min_index(tmp)));
		(res->data)[min] = cur++;
	}
	free(tmp);
	return (res);
}

t_int_array	*int_not_in(t_int_array *src, t_int_array *exclude)
{
	t_int_array	*res;
	int			i;
	int			index;

	if (NULL == (res = copy_int_array(res = copy_int_array(src))))
		return (NULL);
	i = 0;
	while (i < exclude->count)
	{
		if ((index = int_index(res, (exclude->data)[i])) >= 0)
			int_remove(res, index);
		++i;
	}
	return (res);
}
