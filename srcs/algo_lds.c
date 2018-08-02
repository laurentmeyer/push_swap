#include "push_swap.h"
#include "int_array.h"

#define SORT_A_IN_B 0
#define SORT_B_IN_A 1
#define B_IN_A_QS 2

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

void  a_unsorted_in_b_sorted(t_stacks *stacks, t_lds_algo *algo)
{
  static t_int_array  *lds = NULL;
  int          index;
 
  if (NULL == lds && NULL == (lds = get_lds_int_array(stacks->a)))
      exit_message(0, "algo_LDS failed\n");
  else if (0 == lds->count)
  {
    if (is_sorted(stacks->a))
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
 
void  b_unsorted_in_a_sorted(t_stacks *stacks, t_lds_algo *algo)
{
  static t_int_array  *lds = NULL;
 
  if (NULL == lds && NULL == (lds = get_lds_int_array(stacks->b)))
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

// void	a_unsorted_in_b_sorted(t_stacks *stacks, t_lds_algo *algo)
// {
// 	static t_int_array	*lds = NULL;
// 	static int			sorted = 0;
// 	int					index;

// 	if (NULL == lds && NULL == (lds = get_lds_int_ptr(stacks->a->data + sorted,
// 												  stacks->a->count - sorted)))
// 		exit_message(0, "algo_LDS failed\n");
// 	else if (stacks->a->count == sorted)
// 	{
// 		algo->step = SORT_B_IN_A;
// 		free_int_array(lds);
// 		lds = NULL;
// 	}
// 	else if ((index = int_index(lds, int_last(stacks->a))) >= 0)
// 	{
// 		do_op(stacks, "ra");
// 		int_push(algo->sorted, int_remove(lds, index));
// 		sorted++;
// 	}
// 	else
// 		do_op(stacks, "pb");
// }

// void b_unsorted_in_a_sorted(t_stacks *stacks, t_lds_algo *algo)
// {
// 	static t_int_array	*lds = NULL;
// 	static int			sorted = 0;
// 	int					index;

// 	if (NULL == lds && NULL == (lds = get_lds_int_ptr(stacks->b->data + sorted,
// 												  stacks->b->count - sorted)))
// 		exit_message(0, "algo_LDS failed\n");
// 	else if (stacks->b->count == sorted)
// 	{
// 		algo->step = SORT_A_IN_B;
// 		free_int_array(lds);
// 		lds = NULL;
// 	}
// 	else if ((index = int_index(lds, int_last(stacks->b))) >= 0)
// 	{
// 		do_op(stacks, "rb");
// 		int_push(algo->sorted, int_remove(lds, index));
// 		sorted++;
// 	}
// 	else
// 		do_op(stacks, "pa");
// }

void b_in_a_qs(t_stacks *stacks, t_lds_algo *algo)
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
		if (NULL == (algo = (t_lds_algo *)malloc(sizeof(t_lds_algo))) || NULL == (algo->sorted = new_int_array(stacks->a->capacity)))
			exit_message(0, "algo_LDS failed\n");
		algo->step = SORT_A_IN_B;
	}
	// if (0 == stacks->b->count && is_sorted(stacks->a))
	if (algo->sorted->count == (stacks->a->count + stacks->b->count))
	{
		free_int_array(algo->sorted);
		free(algo);
		return (1);
	}
	else if (SORT_A_IN_B == algo->step)
		a_unsorted_in_b_sorted(stacks, algo);
	else if (SORT_B_IN_A == algo->step)
		b_unsorted_in_a_sorted(stacks, algo);
	else if (B_IN_A_QS == algo->step)
		b_in_a_qs(stacks, algo);
	return (0);
}