/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations_swaps.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 10:17:28 by lmeyer            #+#    #+#             */
/*   Updated: 2018/08/25 10:17:29 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_value_on_top(t_stacks *stacks, t_int_array *stack, int value)
{
	int i;

	i = int_index(stack, value);
	if (i < stack->count / 2)
		do_op(stacks, stack == stacks->a ? "rra" : "rrb");
	else
		do_op(stacks, stack == stacks->a ? "ra" : "rb");
}

int		swap_a_if_necessary(t_stacks *stacks)
{
	t_int_array *a;

	a = stacks->a;
	if (a->count < 2 || (a->data)[a->count - 1] < (a->data)[a->count - 2]
		|| int_last(a) == int_max(a))
		return (0);
	if (stacks->b->count >= 2 && ((stacks->b->data)[stacks->b->count - 1]
		< (stacks->b->data)[stacks->b->count - 2]))
		do_op(stacks, "ss");
	else
		do_op(stacks, "sa");
	return (1);
}
