#include "push_swap.h"
#include "int_array.h"

// int         swappable_increasing(t_int_array *array, int start)
// {
//     int i;

//     i = start;
//     if (i >= array->count - 2)
//         return (1);
//     while ((array->data)[i] <= (array->data)[i + 1] && i < array->count - 2)
//         ++i;
//     if (i == (array->count - 1))
//         return (1);
//     if ((array->data)[i + 1] > (array->data)[i + 2])
//         return (0);
//     return (swappable_increasing(array, i + 2));
// }


#define A_IN_B 0
#define B_IN_A 1
#define RROTATE 0
#define ROTATE 1

static int	max(int a, int b)
{
	return (a > b ? a : b);
}

int predecessor_index(t_int_array *array, int to_place)
{
	int	i;

	i = min_index(*array);
	if (to_place < (array->data)[i])
		return (i);
	i = max_index(*array);
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

int algo_lds(t_stacks *stacks)
{
	static t_int_array	*lds = NULL;
	static int			step = A_IN_B;
	int					index;

	if (NULL == lds && ((A_IN_B == step && !(lds = get_lds(&(stacks->a))))
		|| (B_IN_A == step && !(lds = get_lds(&(stacks->b))))))
		exit_message(0, "algo_LDS failed\n");
 	if (0 == stacks->b.count && is_sorted(stacks->a))
	{
		free_int_array(lds);
		return (1);
	}
	if (A_IN_B == step)
	{
		if (0 == lds->count && is_sorted(stacks->a))
		{
			step = B_IN_A;
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
	else if (B_IN_A == step)
	{
		if (0 == stacks->b.count)
			do_op(stacks, "ra"); // a faire + intelligemment
		else if (0 == lds->count)
		{
			free_int_array(lds);
			lds = NULL;
		}
		else
		{
			int b_to_place = int_last(*lds);
			int place_in_a = predecessor_index(&(stacks->a), b_to_place);
			int b_to_rotate = stacks->b.count - 1 - int_index(&(stacks->b), b_to_place);
			int a_to_rotate = stacks->a.count - 1 - place_in_a;
			int	direction;

			if (max(a_to_rotate, b_to_rotate) > max(int_index(&(stacks->b), b_to_place), place_in_a))
				direction = RROTATE;
			else
				direction = ROTATE;


			if (a_to_rotate > 0 && b_to_rotate > 0)
				do_op(stacks, direction == ROTATE ? "rr" : "rrr");
			else if (a_to_rotate > 0 && b_to_rotate == 0)
				do_op(stacks, direction == ROTATE ? "ra" : "rra");
			else if (a_to_rotate == 0 && b_to_rotate > 0)
				do_op(stacks, direction == ROTATE ? "rb" : "rrb");
			else if (a_to_rotate == 0 && b_to_rotate == 0)
			{
				do_op(stacks, "pa");
				int_remove(lds, lds->count - 1);
			}
		}
	}
	return (0);
}