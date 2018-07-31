#include "push_swap.h"
#include "int_array.h"

#define A_IN_B 0
#define B_IN_A_LDS 1
#define B_IN_A_QS 2

void	a_unsorted_in_b_sorted(t_stacks *stacks, t_lds_algo *algo)
{
	static t_int_array	*lds = NULL;
	int					index;

	if (NULL == lds && NULL == (lds = get_lds(stacks->a)))
			exit_message(0, "algo_LDS failed\n");
	else if (0 == lds->count)
	{
		if (is_sorted(stacks->a))
			algo->step = B_IN_A_LDS;
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

void	b_unsorted_in_a_sorted(t_stacks *stacks, t_lds_algo *algo)
{
	static t_int_array	*lds = NULL;

	if (NULL == lds && NULL == (lds = get_lds(stacks->b)))
		exit_message(0, "algo_LDS failed\n");
	else if (0 == lds->count)
	{
		// if (stacks->b->count <= 0)
		if (stacks->b->count <= (stacks->a->count + stacks->b->count) * 1 / 2)
			algo->step = B_IN_A_QS;
		free_int_array(lds);
		lds = NULL;
	}
	else
	{
		if (1 == try_push_b_value_in_sorted_a(stacks, int_last(lds)))
			int_push(algo->sorted, int_remove(lds, lds->count - 1));
	}
}

void	b_in_a_qs(t_stacks *stacks, t_lds_algo *algo)
{
	static t_int_array *lds = NULL;

	if (0 == stacks->b->count)
		do_op(stacks, "ra"); // a faire + intelligemment
	else if (NULL == lds && NULL == (lds = upper_percentile(stacks->b, 25)))
		exit_message(0, "algo_LDS failed\n");
	else if (0 == lds->count)
	{
		free_int_array(lds);
		lds = NULL;
	}
	// a améliorer avec rr et rrr
	else if (int_index(lds, int_last(stacks->b)) < 0)
		do_op(stacks, "rb"); // a faire + intelligemment
	else
	{
		if (1 == try_push_b_value_in_sorted_a(stacks, int_last(lds)))
			int_push(algo->sorted, int_remove(lds, lds->count - 1));
	}
}

int algo_lds(t_stacks *stacks)
{
	static t_lds_algo *algo = NULL;

	if (NULL == algo)
	{
		if (NULL == (algo = (t_lds_algo *)malloc(sizeof(t_lds_algo)))
			|| NULL == (algo->sorted = new_int_array(stacks->a->capacity)))
			exit_message(0, "algo_LDS failed\n");
		algo->step = A_IN_B;
	}
	if (0 == stacks->b->count && is_sorted(stacks->a))
	{
		free_int_array(algo->sorted);
		free(algo);
		return (1);
	}
	else if (A_IN_B == algo->step)
		a_unsorted_in_b_sorted(stacks, algo);
	else if (B_IN_A_LDS == algo->step)
		b_unsorted_in_a_sorted(stacks, algo);
	else if (B_IN_A_QS == algo->step)
		b_in_a_qs(stacks, algo);
	return (0);
}