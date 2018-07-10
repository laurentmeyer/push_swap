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

int		op_swap(t_stack *stack)
{
	int	a;
	int	b;

	if (stack->count > 1)
	{
		a = pop(stack);
		b = pop(stack);
		push(stack, a);
		push(stack, b);
	}
	return (1);
}

int		op_push(t_stack *src, t_stack *dst)
{
	if (src->count > 0)
		push(dst, pop(src));
	return (1);
}

int		op_rotate(t_stack *stack)
{
	int		i;

	if (stack->count > 0)
	{
		i = (stack->elements)[stack->count - 1];
		ft_memmove(stack->elements + 1, stack->elements, (stack->count - 1) * sizeof(int));
		(stack->elements)[0] = i;
	}
	return (1);
}

int		op_reverse_rotate(t_stack *stack)
{
	int		i;

	if (stack->count > 0)
	{
		i = (stack->elements)[0];
		ft_memmove(stack->elements, stack->elements + 1, (stack->count - 1) * sizeof(int));
		(stack->elements)[stack->count - 1] = i;
	}
	return (1);
}

int do_op(t_stacks *stacks, char *s)
{
	char	instruction[4];

	refresh_display(stacks);//
	ft_strcpy(instruction, s);
	ft_lstappend(&(stacks->instructions), ft_lstnew(&instruction, sizeof(instruction)));
	if (ft_strequ(s, "sa"))
		return (op_swap(&(stacks->a)));
	else if (ft_strequ(s, "sb"))
		return (op_swap(&(stacks->b)));
	else if (ft_strequ(s, "ss"))
		return (op_swap(&(stacks->a)) && op_swap(&(stacks->b)));
	else if (ft_strequ(s, "pa"))
		return (op_push(&(stacks->b), &(stacks->a)));
	else if (ft_strequ(s, "pb"))
		return (op_push(&(stacks->a), &(stacks->b)));
	else if (ft_strequ(s, "ra"))
		return (op_rotate(&(stacks->a)));
	else if (ft_strequ(s, "rb"))
		return (op_rotate(&(stacks->b)));
	else if (ft_strequ(s, "rr"))
		return (op_rotate(&(stacks->a))) && op_rotate(&(stacks->b));
	else if (ft_strequ(s, "rra"))
		return (op_reverse_rotate(&(stacks->a)));
	else if (ft_strequ(s, "rrb"))
		return (op_reverse_rotate(&(stacks->b)));
	else if (ft_strequ(s, "rrr"))
		return (op_reverse_rotate(&(stacks->a)) && op_reverse_rotate(&(stacks->b)));
	else
		return (ERR);
}
