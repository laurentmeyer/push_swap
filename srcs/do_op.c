/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 16:14:58 by lmeyer            #+#    #+#             */
/*   Updated: 2017/01/07 16:47:29 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
#define ERR -1

#include "ft_printf.h"

int		op_swap(t_int_array *array)
{
	int	a;
	int	b;

	if (array->count > 1)
	{
		a = int_pop(array);
		b = int_pop(array);
		int_push(array, a);
		int_push(array, b);
	}
	return (1);
}

int		op_push(t_int_array *src, t_int_array *dst)
{
	if (src->count > 0)
		int_push(dst, int_pop(src));
	return (1);
}

int		op_rotate(t_int_array *array)
{
	int		i;

	if (array->count > 0)
	{
		i = (array->data)[array->count - 1];
		ft_memmove(array->data + 1, array->data, (array->count - 1) * sizeof(int));
		(array->data)[0] = i;
	}
	return (1);
}

int		op_reverse_rotate(t_int_array *array)
{
	int		i;

	if (array->count > 0)
	{
		i = (array->data)[0];
		ft_memmove(array->data, array->data + 1, (array->count - 1) * sizeof(int));
		(array->data)[array->count - 1] = i;
	}
	return (1);
}

int do_op(t_stacks *stacks, char *s)
{
	char	instruction[4];
	int		ret;

	ft_strcpy(instruction, s);
	ft_lstappend(&(stacks->instructions), ft_lstnew(&instruction, sizeof(instruction)));
	if (ft_strequ(s, "sa"))
		ret = op_swap(stacks->a);
	else if (ft_strequ(s, "sb"))
		ret = op_swap(stacks->b);
	else if (ft_strequ(s, "ss"))
		ret = op_swap(stacks->a) && op_swap(stacks->b);
	else if (ft_strequ(s, "pa"))
		ret = op_push(stacks->b, stacks->a);
	else if (ft_strequ(s, "pb"))
		ret = op_push(stacks->a, stacks->b);
	else if (ft_strequ(s, "ra"))
		ret = op_rotate(stacks->a);
	else if (ft_strequ(s, "rb"))
		ret = op_rotate(stacks->b);
	else if (ft_strequ(s, "rr"))
		ret = op_rotate(stacks->a) && op_rotate(stacks->b);
	else if (ft_strequ(s, "rra"))
		ret = op_reverse_rotate(stacks->a);
	else if (ft_strequ(s, "rrb"))
		ret = op_reverse_rotate(stacks->b);
	else if (ft_strequ(s, "rrr"))
		ret = op_reverse_rotate(stacks->a) && op_reverse_rotate(stacks->b);
	else
		ret = ERR;
	if (stacks->visual)
		refresh_display(stacks);//
	return (ret);
}
