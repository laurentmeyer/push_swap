/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_lds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 10:14:56 by lmeyer            #+#    #+#             */
/*   Updated: 2018/08/25 10:14:58 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "int_array.h"

#define A_IN_B_LDS 0
#define B_IN_A_DISTANCE 1

void	a_in_b(t_stacks *stacks, t_lds_algo *algo)
{
	static t_int_array	*lds = NULL;
	int					index;

	if (NULL == lds && NULL == (lds = get_lds_int_array(stacks->a)))
		exit_message(0, "algo_LDS failed\n");
	else if (0 == lds->count)
	{
		if (swappable_decreasing(stacks->a->data, stacks->a->count))
			algo->step = B_IN_A_DISTANCE;
		free_int_array(lds);
		lds = NULL;
	}
	else if ((index = int_index(lds, int_last(stacks->a))) >= 0)
	{
		do_op(stacks, "ra");
		int_remove(lds, index);
	}
	else
		do_op(stacks, "pb");
}

void	b_in_a_distance(t_stacks *stacks)
{
	t_int_array *dst;
	int			to_push;

	dst = NULL;
	if (0 == stacks->b->count)
		rotate_value_on_top(stacks, stacks->a, int_min(stacks->a));
	else if (0 != swap_a_if_necessary(stacks))
		;
	else if (NULL == (dst = distance_array(stacks)))
		exit_message(0, "algo_LDS failed\n");
	else
	{
		to_push = (stacks->b->data)[int_index(dst, int_min(dst))];
		try_push_b_value_in_sorted_a(stacks, to_push);
	}
	if (NULL != dst)
		free_int_array(dst);
}

int		algo_lds(t_stacks *stacks)
{
	static t_lds_algo *algo = NULL;

	if (0 == stacks->b->count && is_sorted_descending(stacks->a))
	{
		if (NULL != algo)
			free(algo);
		return (1);
	}
	else if (NULL == algo)
	{
		if (NULL == (algo = (t_lds_algo *)malloc(sizeof(t_lds_algo))))
			exit_message(0, "algo_LDS failed\n");
		algo->step = A_IN_B_LDS;
	}
	else if (A_IN_B_LDS == algo->step)
		a_in_b(stacks, algo);
	else if (B_IN_A_DISTANCE == algo->step)
		b_in_a_distance(stacks);
	return (0);
}
