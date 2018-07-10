#include "push_swap.h"

void rotate_min_a_on_top(t_stacks *stacks)
{
	int i;
	char *operation;

	i = min_index(stacks->a);
	if (i < stacks->a.count / 2)
	{
		operation = "rra";
		i++;
	}
	else
	{
		i = stacks->a.count - 1 - i;
		operation = "ra";
	}
	while (i-- > 0)
		do_op(stacks, operation);
}