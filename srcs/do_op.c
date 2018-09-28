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

static int		op_swap(t_int_array *array)
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

static int		op_push(t_int_array *src, t_int_array *dst)
{
	if (src->count > 0)
		int_push(dst, int_pop(src));
	return (1);
}

static int		op_r(t_int_array *array)
{
	int		i;

	if (array->count > 0)
	{
		i = (array->data)[array->count - 1];
		ft_memmove(array->data + 1,
			array->data, (array->count - 1) * sizeof(int));
		(array->data)[0] = i;
	}
	return (1);
}

static int		op_rr(t_int_array *array)
{
	int		i;

	if (array->count > 0)
	{
		i = (array->data)[0];
		ft_memmove(array->data, array->data + 1,
			(array->count - 1) * sizeof(int));
		(array->data)[array->count - 1] = i;
	}
	return (1);
}

int				do_op(t_stacks *st, char *s)
{
	char	instruction[4];
	int		r;

	ft_strcpy(instruction, s);
	ft_lstappend(&(st->instructions),
		ft_lstnew(&instruction, sizeof(instruction)));
	r = ERR;
	if (ft_strequ(s, "sa") || ft_strequ(s, "sb"))
		r = ft_strequ(s, "sa") ? op_swap(st->a) : op_swap(st->b);
	else if (ft_strequ(s, "ss"))
		r = op_swap(st->a) && op_swap(st->b);
	else if (ft_strequ(s, "pa") || ft_strequ(s, "pb"))
		r = ft_strequ(s, "pa") ? op_push(st->b, st->a) : op_push(st->a, st->b);
	else if (ft_strequ(s, "ra") || ft_strequ(s, "rb"))
		r = ft_strequ(s, "ra") ? op_r(st->a) : op_r(st->b);
	else if (ft_strequ(s, "rr") || ft_strequ(s, "rrr"))
		r = ft_strequ(s, "rr") ? op_r(st->a) && op_r(st->b)
			: op_rr(st->a) && op_rr(st->b);
	else if (ft_strequ(s, "rra") || ft_strequ(s, "rrb"))
		r = ft_strequ(s, "rra") ? op_rr(st->a) : op_rr(st->b);
	if (st->visual)
		refresh_display(st);
	return (r);
}
