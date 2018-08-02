#include "push_swap.h"
#include "int_array.h"
#include <limits.h>

#define QS_STEP_SPLIT 0
#define QS_STEP_MERGE 1
#define ELT_IN_A 0
#define ELT_IN_B 1

typedef struct s_algo_qs
{
	t_int_array *split;
	t_int_array *groups;
	int			step;
	int 		group_count;
	int 		current_group;
	int 		current_group_count;
	int 		current_group_max;
	int			skip_splitting;
	int 		cd_revol;
	int 		cd_group;
}				t_algo_qs;

t_algo_qs *new_algo_qs(t_stacks *stacks)
{
	t_algo_qs *algo;
	int i;

	if (NULL == (algo = (t_algo_qs *)malloc(sizeof(t_algo_qs))))
		return (NULL);
	if (NULL == (algo->split = copy_int_array(stacks->a)) || NULL == (algo->groups = copy_int_array(stacks->a)))
		return (NULL);
	algo->step = QS_STEP_SPLIT;
	algo->group_count = 0;
	algo->cd_group = 0;
	algo->cd_revol = 0;
	i = 0;
	while (i < algo->split->count)
	{
		(algo->split->data)[i] = ELT_IN_A;
		(algo->groups->data)[i] = algo->group_count;
		++i;
	}
	return (algo);
}

void free_algo_qs(t_algo_qs *algo)
{
	if (NULL != algo->split)
		free_int_array(algo->split);
	if (NULL != algo->groups)
		free_int_array(algo->groups);
	free(algo);
}

void update_split(t_int_array *src)
{
	int i;
	int j;
	int cutoff;

	i = 0;
	while (i < src->count)
	{
		j = i;
		while (j < src->count && (src->data)[i] == (src->data)[j + 1])
			j++;
		cutoff = (i + j) / 2;
		while (i <= cutoff)
			(src->data)[i++] = ELT_IN_A;
		while (i <= j)
			(src->data)[i++] = ELT_IN_B;
	}
}

int int_count_occurences(t_int_array *array, int value)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	while (i < array->count)
	{
		if ((array->data)[i] == value)
			ret++;
		i++;
	}
	return (ret);
}

int		should_swap_a(t_algo_qs *algo, t_int_array *a)
{
	return ((algo->cd_group >= 2
		&& algo->skip_splitting
		&& (a->data)[a->count - 1] > (a->data)[a->count - 2]
		&& (a->data)[a->count - 1] < (a->data)[a->count - 3]));
}

void split_stacks(t_stacks *stacks, t_algo_qs *algo)
{
	if (0 == algo->cd_group)
		algo->step = QS_STEP_MERGE;
	else
	{
		if (should_swap_a(algo, stacks->a))
		;
			// do_op(stacks, "sa");
		else
		{
			if (algo->skip_splitting > 0)
				do_op(stacks, "ra");
			else if (ELT_IN_A == (algo->split->data)[int_last(stacks->a)])
			{
				(algo->groups->data)[int_last(stacks->a)] = algo->group_count;
				do_op(stacks, "ra");
			}
			else
				do_op(stacks, "pb");
			algo->cd_group--;
			algo->cd_revol--;
		}
	}
}

int swappable_decreasing(int *array, int len)
{
	int	*copy;
	int	i;

	if (NULL == (copy = (int *)malloc(len * sizeof(int))))
		return (ERR);
	ft_memcpy(copy, array, len * sizeof(int));
	i = 0;
	while (++i < len)
		if (copy[i - 1] < copy[i])
		{
			ft_swap_int(copy + i - 1, copy + i);
			++i;
		}
	i = 0;
	while (i < len - 1 && copy[i] < copy[i + 1])
		++i;
	free(copy);
	return (i == len);
}

int group_max(int *array, int len)
{
	int	max;
	int	i;

	max = INT_MIN;
	i = 0;
	while (i < len)
	{
		if (array[i] > max)
			max = array[i];
		i++;
	}
	return (max);
}

int	a_top_in_right_place(t_int_array *a, t_algo_qs *algo)
{
	int	theoretical_value;
	int	ret;

	theoretical_value = algo->current_group_max - algo->cd_group + 1;
	int d;
	d = int_last(a);
	ret = (theoretical_value == int_last(a));
	return (ret);
}

void merge_stacks(t_stacks *stacks, t_algo_qs *algo)
{
	int debug[4];

	// si on peut facilememt trier b, on le fait
	static int to_rotate_a = 0;

	if (to_rotate_a > 0)
	{
		do_op(stacks, "ra");
		to_rotate_a--;
	}
	else if (stacks->b->count > 0)
	{
		do_op(stacks, "pa");
		to_rotate_a++;
	}
	else if (0 == stacks->b->count)
	{
		if (0 == algo->cd_revol)
		{
			update_split(algo->split); // a ne pas faire tous les tours !!
			algo->cd_revol = stacks->a->count + stacks->b->count;
		}
		algo->current_group = (algo->groups->data)[int_last(stacks->a)];
		algo->current_group_count = int_count_occurences(algo->groups, algo->current_group);
		// algo->current_group_max = group_max(stacks->a->data + stacks->a->count - algo->current_group_count, algo->current_group_count);
		algo->cd_group = algo->current_group_count;

		if (algo->current_group_count <= 3)
		{
			int d = 0;
			int offset = stacks->a->count - algo->cd_group;
			while (d < algo->cd_group)
			{
				debug[d] = (stacks->a->data)[d + offset];
				d++;
			}
			while (d < 4)
			{
				debug[d] = -1;
				d++;
			}
			offset = d;
		}

		a_top_in_right_place(stacks->a, algo);
		algo->skip_splitting = swappable_decreasing(stacks->a->data + stacks->a->count - algo->current_group_count, algo->current_group_count);
		algo->group_count += 1;
		algo->step = QS_STEP_SPLIT;
	}
}

int algo_quicksort(t_stacks *stacks)
{
	static t_algo_qs *algo = NULL;

	if (NULL == algo && NULL == (algo = new_algo_qs(stacks)))
		exit_message(0, "QS algorithm failed\n");
	else if (is_sorted(stacks->a) && stacks->b->count == 0)
	{
		free_algo_qs(algo);
		return (1);
	}
	else if (QS_STEP_SPLIT == algo->step)
		split_stacks(stacks, algo);
	else if (QS_STEP_MERGE == algo->step)
		merge_stacks(stacks, algo);
	return (0);
}