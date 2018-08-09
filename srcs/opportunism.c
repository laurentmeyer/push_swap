#include "push_swap.h"
#include "int_array.h"

int should_pa(t_stacks *stacks, t_int_array *lds)
{
	int	last_a;
	int	penult_a;
	int	last_b;
	int	first_a;

	if (stacks->a->count <= 0 || stacks->b->count <= 0)
		return (0);
	last_a = int_last(stacks->a);
	last_b = int_last(stacks->b);
	first_a = int_first(stacks->a);
	if (lds != NULL && int_index(lds, last_b) >= 0)
		return (0);
	if ((last_b > int_max(stacks->a) && first_a == int_max(stacks->a))
		|| (last_b < int_min(stacks->a) && last_a == int_min(stacks->a))
		|| (last_b < last_a && last_b > first_a
			&& (stacks->a->count <= 2 || last_b < (stacks->a->data)[stacks->a->count - 2])))
		return (1);
	if (stacks->a->count < 2)
		return (0);
	penult_a = (stacks->a->data)[stacks->a->count - 2];
	if (last_b > last_a && last_b < penult_a && last_a < penult_a)
		return (1);
	return (0);
}

int should_rrb(t_stacks *stacks, t_int_array *lds)
{
	int	last_a;
	int	penult_a;
	int	first_b;
	int	first_a;

	if (stacks->a->count <= 0 || stacks->b->count <= 0)
		return (0);
	last_a = int_last(stacks->a);
	first_b = int_first(stacks->b);
	first_a = int_first(stacks->a);
	if (lds != NULL && int_index(lds, first_b) >= 0)
		return (0);
	if ((first_b > int_max(stacks->a) && first_a == int_max(stacks->a))
		|| (first_b < int_min(stacks->a) && last_a == int_min(stacks->a))
		|| (first_b < last_a && first_b > first_a))
		return (1);
	if (stacks->a->count < 2)
		return (0);
	penult_a = (stacks->a->data)[stacks->a->count - 2];
	if (first_b > last_a && first_b < penult_a && last_a < penult_a)
		return (1);
	return (0);
}

int swapped_if_opportunity(t_stacks *stacks)
{
	int should_a;
	int should_b;
	int might_b;

	should_a = stacks->a->count >= 2 && ((stacks->a->data)[stacks->a->count - 1] == (stacks->a->data)[stacks->a->count - 2] + 1);
	should_b = stacks->b->count >= 2 && ((stacks->b->data)[stacks->b->count - 1] == (stacks->b->data)[stacks->b->count - 2] - 1);
	might_b = stacks->b->count >= 2 && ((stacks->b->data)[stacks->b->count - 1] < (stacks->b->data)[stacks->b->count - 2]);
	if (!should_a && !should_b)
		return (0);
	else if (should_a && (should_b || might_b))
		do_op(stacks, "ss");
	else if (should_a)
		do_op(stacks, "sa");
	else if (should_b)
		do_op(stacks, "sb");
	return (1);
}

int swap_a_if_necessary(t_stacks *stacks)
{
	t_int_array	*a;

	a = stacks->a;
	if (a->count < 2
		|| (a->data)[a->count - 1] < (a->data)[a->count - 2]
		|| int_last(a) == int_max(a))
		return (0);
	if (stacks->b->count >= 2 && ((stacks->b->data)[stacks->b->count - 1]
		< (stacks->b->data)[stacks->b->count - 2]))
		do_op(stacks, "ss");
	else
		do_op(stacks, "sa");
	return (1);
}