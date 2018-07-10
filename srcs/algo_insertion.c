#include "push_swap.h"
#include <limits.h>


int	insertion(t_stacks *stacks)
{
	static int	min_on_top = 0;

	if (is_sorted(stacks->a))
	{
		if (stacks->b.count == 0)
			return (1);
		else
			do_op(stacks, "pa");
	}
	else
	{
		if (min_on_top)
			do_op(stacks, "pb");
		else
			rotate_min_a_on_top(stacks);
		min_on_top = !min_on_top;
	}
	return (0);
}
