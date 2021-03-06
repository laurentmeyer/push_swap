/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs_increasing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 10:17:59 by lmeyer            #+#    #+#             */
/*   Updated: 2018/08/25 10:18:01 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "int_array.h"

int					is_sorted_ascending(t_int_array *array)
{
	int i;

	if (array->count == 1)
		return (1);
	i = 0;
	while (i < array->count - 1)
	{
		if ((array->data)[i] >= (array->data)[i + 1])
			return (0);
		++i;
	}
	return (1);
}

int					swappable_increasing(int *array, int len)
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

int					ascending_by_rotation(t_int_array *array)
{
	t_int_array	*copy;
	int			min_ind;
	int			i;

	if (NULL == (copy = copy_int_array(array)))
		return (ERR);
	min_ind = int_index(array, int_min(array));
	i = 0;
	while (i < array->count)
	{
		(copy->data)[i] = (array->data)[(i + min_ind) % array->count];
		i++;
	}
	i = is_sorted_descending(copy);
	free_int_array(copy);
	return (i);
}

static t_int_array	*swaps_indices(t_int_array *a)
{
	t_int_array	*copy;
	t_int_array	*ret;
	int			i;
	int			j;

	if (!(copy = copy_int_array(a))
		|| !(ret = new_int_array(a->count)))
		return (NULL);
	i = -1;
	while (++i < a->count)
	{
		j = (i + 1) % a->count;
		if (!(int_max(a) == (copy->data)[i])
			&& (a->data)[i] > (a->data)[j])
		{
			ft_swap_int(copy->data + i++, copy->data + j);
			int_push(ret, j);
		}
	}
	i = ascending_by_rotation(copy);
	free_int_array(copy);
	if (0 == i)
		free_int_array(ret);
	return (0 == i ? NULL : ret);
}

int					move_b_if_swap_rot_increasing(t_stacks *stacks)
{
	t_int_array	*indices;
	int			rot;
	int			rev;
	char		*to_do;

	if (stacks->b->count <= 1 || NULL == (indices = swaps_indices(stacks->a)))
		return (0);
	if (indices->count > 0)
	{
		rot = 0;
		rev = stacks->a->count - 1;
		to_do = int_index(indices, stacks->a->count - 1) >= 0 ? "sb" : NULL;
		while (NULL == to_do && rot <= rev)
		{
			if (int_index(indices, stacks->a->count - 1 - rev--) >= 0)
				to_do = "rrb";
			else if (int_index(indices, stacks->a->count - 1 - rot++) >= 0)
				to_do = "rb";
		}
		do_op(stacks, to_do);
	}
	free_int_array(indices);
	return (indices->count > 0);
}
