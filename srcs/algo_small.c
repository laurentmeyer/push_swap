#include "push_swap.h"

int	algo_small(t_stacks *stacks)
{
	t_int_array *dst;

	dst = NULL;
	if (0 == stacks->b->count && is_sorted_descending(stacks->a))
		return (1);
	else if (0 == stacks->b->count && descending_by_rotation(stacks->a))
		rotate_value_on_top(stacks, stacks->a, int_min(stacks->a));
	else if (move_a_if_swap_rot_decreasing(stacks)
		|| move_b_if_swap_rot_increasing(stacks))
		return (0);
	else if (descending_by_rotation(stacks->a))
	{
		if (NULL == (dst = distance_array(stacks)))
			exit_message(0, "algo_simple failed\n");
		try_push_b_value_in_sorted_a(stacks, (stacks->b->data)[int_index(dst, int_min(dst))]);
	}
	else
		do_op(stacks, "pb");
	if (NULL != dst)
		free_int_array(dst);
	return (0);
}