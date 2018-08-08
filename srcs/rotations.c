#include "push_swap.h"

void rotate_max_b_on_top(t_stacks *stacks)
{
	int i;
	char *operation;

	i = int_index(stacks->b, int_max(stacks->b));
	if (i < stacks->b->count / 2)
	{
		operation = "rrb";
		i++;
	}
	else
	{
		i = stacks->b->count - 1 - i;
		operation = "rb";
	}
	do_op(stacks, operation);
}

void rotate_min_a_on_top(t_stacks *stacks)
{
	int i;
	char *operation;

	i = int_min_index(stacks->a);
	if (i < stacks->a->count / 2)
	{
		operation = "rra";
		i++;
	}
	else
	{
		i = stacks->a->count - 1 - i;
		operation = "ra";
	}
	do_op(stacks, operation);
}