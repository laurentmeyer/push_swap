#include "push_swap.h"
#include "int_array.h"
#define RROTATE 0
#define ROTATE 1

static int	max(int a, int b)
{
	return (a > b ? a : b);
}

int predecessor_index(t_int_array *array, int to_place)
{
	int	i;

	i = int_min_index(array);
	if (to_place < (array->data)[i])
		return (i);
	i = max_index(array);
	if (to_place > (array->data)[i])
		return (i > 0 ? i - 1 : array->count - 1);
	i = array->count - 1;
	if (to_place <= (array->data)[i] && to_place >= (array->data)[0])
		return (i);
	i--;
	while (i >= 0)
	{
		if (to_place <= (array->data)[i] && to_place >= (array->data)[i + 1])
			return (i);
		--i;
	}
	return (-1);
}

int try_push_b_value_in_sorted_a(t_stacks *stacks, int value)
{
	int place_in_a = predecessor_index(stacks->a, value);
	int b_to_rotate = stacks->b->count - 1 - int_index(stacks->b, value);
	int a_to_rotate = stacks->a->count - 1 - place_in_a;
	int direction;

	int v;
	v = value;
	if (a_to_rotate == 0 && b_to_rotate == 0)
	{
		do_op(stacks, "pa");
		return (1);
	}
	else if (max(a_to_rotate, b_to_rotate) > max(int_index(stacks->b, value), place_in_a))
		direction = RROTATE;
	else
		direction = ROTATE;
	if (a_to_rotate > 0 && b_to_rotate > 0)
		do_op(stacks, direction == ROTATE ? "rr" : "rrr");
	else if (a_to_rotate > 0 && b_to_rotate == 0)
		do_op(stacks, direction == ROTATE ? "ra" : "rra");
	else if (a_to_rotate == 0 && b_to_rotate > 0)
		do_op(stacks, direction == ROTATE ? "rb" : "rrb");
	return (0);
}