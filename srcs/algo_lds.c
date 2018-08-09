#include "push_swap.h"
#include "int_array.h"

#define SORT_A_IN_B 0
#define SORT_B_IN_A 1
#define B_IN_A_SELECT 2

void a_in_b(t_stacks *stacks, t_lds_algo *algo)
{
	static t_int_array *lds = NULL;
	int index;

	if (NULL == lds)
	{
		if (NULL == (lds = get_lds_int_array(stacks->a)))
			exit_message(0, "algo_LDS failed\n");
	}
	else if (0 == lds->count)
	{
		if (swappable_decreasing(stacks->a->data, stacks->a->count))
			algo->step = SORT_B_IN_A;
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

void b_in_a_lds(t_stacks *stacks, t_lds_algo *algo)
{
	static t_int_array *lds = NULL;

	if (NULL == lds)
	{
		if (NULL == (lds = get_lds_int_array(stacks->b)))
			exit_message(0, "algo_LDS failed\n");
	}
	else if (0 != swap_a_if_necessary(stacks))
		;
	else if (0 == lds->count)
	{
		if (stacks->b->count <= (stacks->a->count + stacks->b->count) * 5 / 10)
			algo->step = B_IN_A_SELECT;
		free_int_array(lds);
		lds = NULL;
	}
	else
	{
		if (should_pa(stacks, lds))
			do_op(stacks, "pa");
		else if (should_rrb(stacks, lds))
			do_op(stacks, "rrb");
		else if (1 == try_push_b_value_in_sorted_a(stacks, int_last(lds)))
			int_remove(lds, lds->count - 1);
	}
}

void b_in_a_select(t_stacks *stacks)
{
	if (0 == stacks->b->count)
		rotate_value_on_top(stacks, stacks->a, int_min(stacks->a));
	else if (0 != swap_a_if_necessary(stacks))
		;
	else if (should_pa(stacks, NULL))
		do_op(stacks, "pa");
	else if (should_rrb(stacks, NULL))
		do_op(stacks, "rrb");
	else
		try_push_b_value_in_sorted_a(stacks, int_max(stacks->b));
}

int algo_lds(t_stacks *stacks)
{
	static t_lds_algo *algo = NULL;

	if (NULL == algo)
	{
		if (NULL == (algo = (t_lds_algo *)malloc(sizeof(t_lds_algo))))
			exit_message(0, "algo_LDS failed\n");
		algo->step = SORT_A_IN_B;
		algo->selection_count = 0;
	}
	if (0 == stacks->b->count && is_sorted(stacks->a))
	{
		free(algo);
		return (1);
	}
	if (0 != swapped_if_opportunity(stacks))
		;
	else if (SORT_A_IN_B == algo->step)
		a_in_b(stacks, algo);
	else if (SORT_B_IN_A == algo->step)
		b_in_a_lds(stacks, algo);
	else if (B_IN_A_SELECT == algo->step)
		b_in_a_select(stacks);
	return (0);
}