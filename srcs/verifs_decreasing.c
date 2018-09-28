/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs_decreasing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 10:17:52 by lmeyer            #+#    #+#             */
/*   Updated: 2018/08/25 10:17:53 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "int_array.h"

int					is_sorted_descending(t_int_array *array)
{
	int i;

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

int					swappable_decreasing(int *array, int len)
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

int					descending_by_rotation(t_int_array *array)
{
	t_int_array	*copy;
	int			max_ind;
	int			i;

	if (NULL == (copy = copy_int_array(array)))
		return (ERR);
	max_ind = int_index(array, int_max(array));
	i = 0;
	while (i < array->count)
	{
		(copy->data)[i] = (array->data)[(i + max_ind) % array->count];
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
		if (!(int_min(a) == (copy->data)[i]) && (a->data)[i] < (a->data)[j])
		{
			ft_swap_int(copy->data + i++, copy->data + j);
			int_push(ret, j);
		}
	}
	i = descending_by_rotation(copy);
	free_int_array(copy);
	if (0 == i)
		free_int_array(ret);
	return (0 == i ? NULL : ret);
}

int					move_a_if_swap_rot_decreasing(t_stacks *stacks)
{
	t_int_array	*indices;
	int			rot;
	int			rev;
	char		*to_do;

	if (stacks->a->count <= 1 || NULL == (indices = swaps_indices(stacks->a)))
		return (0);
	if (indices->count > 0)
	{
		rot = 0;
		rev = stacks->a->count - 1;
		to_do = int_index(indices, stacks->a->count - 1) >= 0 ? "sa" : NULL;
		while (NULL == to_do && rot <= rev)
		{
			if (int_index(indices, stacks->a->count - 1 - rev--) >= 0)
				to_do = "rra";
			else if (int_index(indices, stacks->a->count - 1 - rot++) >= 0)
				to_do = "ra";
		}
		do_op(stacks, to_do);
	}
	free_int_array(indices);
	return (indices->count > 0);
}
