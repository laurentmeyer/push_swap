#include "push_swap.h"
#include "int_array.h"

typedef struct	s_distance
{
	int			ra;
	int			rb;
	int			rra;
	int			rrb;
	int			rr;
	int			rrr;
	int			rarrb;
	int			rbrra;
	int			shortest;
	int			direction;
}				t_distance;

static int	max(int a, int b)
{
	return (a > b ? a : b);
}

static int	min(int a, int b)
{
	return (a > b ? b : a);
}

int predecessor_index(t_int_array *array, int to_place)
{
	int	i;

	i = int_min_index(array);
	if (to_place < (array->data)[i])
		return (i);
	i = int_index(array, int_max(array));
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

void			count_moves(t_stacks *stacks, int value, t_distance *dis)
{
	dis->rra = predecessor_index(stacks->a, value) + 1;
	dis->rrb = int_index(stacks->b, value) + 1;
	dis->ra = stacks->a->count - 1 - (dis->rra - 1);
	dis->rb = stacks->b->count - 1 - (dis->rrb - 1);
	dis->rr = max(dis->ra, dis->rb);
	dis->rrr = max(dis->rra, dis->rrb);
	dis->rarrb = dis->ra + dis->rrb;
	dis->rbrra = dis->rra + dis->rb;
	dis->shortest = min(min(dis->rr, dis->rrr), min(dis->rarrb, dis->rbrra));
	if (dis->rb == 0)
		dis->direction = dis->ra < dis->rra ? DIR_RA : DIR_REV_RA;
	else if (dis->ra == 0)
		dis->direction = dis->rb < dis->rrb ? DIR_RB : DIR_REV_RB;
	else if (dis->shortest == dis->rrr)
		dis->direction = DIR_REV_RR;
	else if (dis->shortest == dis->rr)
		dis->direction = DIR_RR;
	else if (dis->shortest == dis->rarrb)
		dis->direction = dis->ra > 0 ? DIR_RA : DIR_REV_RB;
	else if (dis->shortest == dis->rbrra)
		dis->direction = dis->rb > 0 ? DIR_RB : DIR_REV_RA;
}

t_int_array		*distance_array(t_stacks *stacks)
{
	t_int_array	*ret;
	t_distance	dis;
	int			i;

	if (NULL == (ret = copy_int_array(stacks->b)))
		return (NULL);
	i = 0;
	while (i < ret->count)
	{
		count_moves(stacks, (stacks->b->data)[i], &dis);
		(ret->data)[i] = dis.shortest;
		++i;
	}
	return (ret);
}


int try_push_b_value_in_sorted_a(t_stacks *stacks, int value)
{
	t_distance	dis;

	count_moves(stacks, value, &dis);
	if (0 == dis.shortest)
	{
		do_op(stacks, "pa");
		return (1);
	}
	if (DIR_RA == dis.direction)
		do_op(stacks, "ra");
	else if (DIR_RB == dis.direction)
		do_op(stacks, "rb");
	else if (DIR_RR == dis.direction)
		do_op(stacks, "rr");
	else if (DIR_REV_RA == dis.direction)
		do_op(stacks, "rra");
	else if (DIR_REV_RB == dis.direction)
		do_op(stacks, "rrb");
	else if (DIR_REV_RR == dis.direction)
		do_op(stacks, "rrr");
	return (0);
}