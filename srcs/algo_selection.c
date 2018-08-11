#include "push_swap.h"

int	simple_selection(t_stacks *stacks)
{
	if (is_sorted_descending(stacks->a))
	{
		if (stacks->b->count == 0)
			return (1);
		else
			do_op(stacks, "pa");
	}
	else
	{
		if (int_min_index(stacks->a) == stacks->a->count - 1)
			do_op(stacks, "pb");
		else
			rotate_value_on_top(stacks, stacks->a, int_min(stacks->a));
	}
	return (0);
}