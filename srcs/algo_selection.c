#include "push_swap.h"
#include <limits.h>


int	simple_selection(t_stacks *stacks)
{
	if (is_sorted(stacks->a))
	{
		if (stacks->b.count == 0)
			return (1);
		else
			do_op(stacks, "pa");
	}
	else
	{
		if (min_index(stacks->a) == stacks->a.count - 1)
			do_op(stacks, "pb");
		else
			rotate_min_a_on_top(stacks);
	}
	return (0);
}