#include "push_swap.h"

void rotate_value_on_top(t_stacks *stacks, t_int_array *stack, int value)
{
	int i;

	i = int_index(stack, value);
	if (i < stack->count / 2)
		do_op(stacks, stack == stacks->a ? "rra" : "rrb");
	else
		do_op(stacks, stack == stacks->a ? "ra" : "rb");
}