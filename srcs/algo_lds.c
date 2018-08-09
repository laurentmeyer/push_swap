/*
- enlever tout ce qui a trait a algo->sorted??
*/
#include "push_swap.h"
#include "int_array.h"

#define SORT_A_IN_B 0
#define SORT_B_IN_A 1
#define B_IN_A_SELECT 2
#define A_BACK_TO_B 3
#define B_IN_A_QS 4
#define ALGO_QUIT 5

t_int_array	*int_not_in(t_int_array *src, t_int_array *exclude)
{
	t_int_array	*res;
	int			i;
	int			index;

	if (NULL == (res = copy_int_array(res = copy_int_array(src))))
		return (NULL);
	i = 0;
	while (i < exclude->count)
	{
		if ((index = int_index(res, (exclude->data)[i])) >= 0)
			int_remove(res, index);
		++i;
	}
	return (res);
}

t_int_array	*supplement_lds(t_int_array *a, t_int_array *lds)
{
	int			pos_lds;
	int			pos_a;

	pos_lds = lds->count - 1;
	pos_a = a->count - 1;
	while (pos_lds >= 0 && pos_a >= 0)
	{
		if ((a->data)[pos_a] == (lds->data)[pos_lds])
		{
			pos_lds--;
			pos_a--;
			continue;
		}
		int_insert(lds, pos_lds + 1, (a->data)[pos_a]);
		if (swappable_decreasing(lds->data, lds->count))
			pos_a = int_index(a, (lds->data)[pos_lds]);
		else
		{
			int_remove(lds, pos_lds + 1);
			pos_a--;
		}
	}
	return (lds);
}

void a_in_b(t_stacks *stacks, t_lds_algo *algo)
{
	static t_int_array *lds = NULL;
	int index;

	if (NULL == lds)
	{
		if (NULL == (lds = get_lds_int_array(stacks->a)))
			exit_message(0, "algo_LDS failed\n");
		if (NULL == supplement_lds(stacks->a, lds))
			exit_message(0, "algo_LDS failed\n");
	}
	else if (0 == lds->count)
	{
		// if (is_sorted(stacks->a))
		if (swappable_decreasing(stacks->a->data, stacks->a->count))
			algo->step = SORT_B_IN_A;
		free_int_array(lds);
		lds = NULL;
	}
	else if ((index = int_index(lds, int_last(stacks->a))) >= 0)
	{
		do_op(stacks, "ra");
		int_push(algo->sorted, int_remove(lds, index));
	}
	else
		do_op(stacks, "pb");
}

int should_pa(t_stacks *stacks, t_int_array *lds)
{
	int	last_a;
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
		|| (last_b < last_a && last_b > first_a))
		return (1);
	// if (stacks->a->count < 2)
	// 	return (0);
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
		// if (stacks->b->count <= 0)
		if (stacks->b->count <= (stacks->a->count + stacks->b->count) * 3 / 10)
			// algo->step = B_IN_A_SELECT;
			// algo->step = ALGO_QUIT;
			algo->step = B_IN_A_QS;
		free_int_array(lds);
		lds = NULL;
	}
	else
	{
		if (should_pa(stacks, lds))
			do_op(stacks, "pa");
		else if (1 == try_push_b_value_in_sorted_a(stacks, int_last(lds)))
			int_push(algo->sorted, int_remove(lds, lds->count - 1));
	}
}

void b_in_a_select(t_stacks *stacks, t_lds_algo *algo)
{
	if (stacks->b->count <= 1)
		algo->step = A_BACK_TO_B;
	else if (int_max(stacks->b) == int_last(stacks->b))
	{
		algo->selection_count++;
		do_op(stacks, "pa");
	}
	else
		rotate_max_b_on_top(stacks);
}

void a_back_in_b(t_stacks *stacks, t_lds_algo *algo)
{
	if (algo->selection_count > 0)
	{
		algo->selection_count--;
		do_op(stacks, "pb");
	}
	else
		algo->step = B_IN_A_QS;
}

// void b_in_a_qs(t_stacks *stacks, t_lds_algo *algo)
// {
// 	static t_int_array *lds = NULL;

// 	if (0 == stacks->b->count)
// 		rotate_min_a_on_top(stacks);
// 	else if (NULL == lds && NULL == (lds = upper_percentile(stacks->b, 15))) // voir comment adapter
// 		exit_message(0, "algo_LDS failed\n");
// 	else if (0 != swap_a_if_necessary(stacks))
// 		;
// 	else if (0 == lds->count)
// 	{
// 		free_int_array(lds);
// 		lds = NULL;
// 	}
// 	// a améliorer avec rr et rrr
// 	else if (int_index(lds, int_last(stacks->b)) < 0)
// 		do_op(stacks, "rb"); // a faire + intelligemment
// 	else
// 	{
// 		if (1 == try_push_b_value_in_sorted_a(stacks, int_last(lds)))
// 			int_push(algo->sorted, int_remove(lds, lds->count - 1));
// 	}
// }
// else if (should_pa(stacks, NULL))
// 		do_op(stacks, "pa");

void b_in_a_qs(t_stacks *stacks, t_lds_algo *algo)
{
	if (0 == stacks->b->count)
		rotate_min_a_on_top(stacks);
	else if (0 != swap_a_if_necessary(stacks))
		;
	else if (should_pa(stacks, NULL))
		do_op(stacks, "pa");
	else
		try_push_b_value_in_sorted_a(stacks, int_max(stacks->b));
	algo = NULL;
}

int algo_lds(t_stacks *stacks)
{
	static t_lds_algo *algo = NULL;

	if (NULL == algo)
	{
		if (NULL == (algo = (t_lds_algo *)malloc(sizeof(t_lds_algo))) || NULL == (algo->sorted = new_int_array(stacks->a->capacity)))
			exit_message(0, "algo_LDS failed\n");
		algo->step = SORT_A_IN_B;
		algo->selection_count = 0;
	}
	if (0 == stacks->b->count && is_sorted(stacks->a))
	// if (algo->sorted->count == (stacks->a->count + stacks->b->count))
	{
		free_int_array(algo->sorted);
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
		b_in_a_select(stacks, algo);
	else if (A_BACK_TO_B == algo->step)
		a_back_in_b(stacks, algo);
	else if (B_IN_A_QS == algo->step)
		b_in_a_qs(stacks, algo);
	else if (ALGO_QUIT == algo->step)
		return (1);
	return (0);
}