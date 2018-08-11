/*
description de l'algo actuel

- on cherche à toujours avoir un groupe non trié en haut d'une des deux piles
=> quand on trie un groupe, on fait en même temps une rotation sur l'autre si la pile en haut de l'autre est triée
- on trie tous les groupes en essayant d'avoir un nombre d'entiers triés égaux sur les 2 piles
*/

#include "push_swap.h"
#include "libft.h"
#include "int_array.h"
#include <limits.h>

#define qs_step_split 0
#define qs_step_merge 1
#define STACK_A 0
#define STACK_B 1
#define DONE 0
#define CONTINUE 1

typedef struct	s_group
{
	int			min;
	int			max;
	int			dont_split;
	int			stack;
}				t_group;

typedef struct	s_algo_qs
{
	t_group		*groups;
	t_group 	*cur_group;
	t_group 	*next_group;
	int 		groups_len;
	int			dist_next_a;
	int			dist_next_b;
	int			next_group_max;
	int 		cd_group;
}				t_algo_qs;

t_algo_qs *new_algo_qs(t_stacks *stacks)
{
	t_algo_qs	*algo;
	int			l;

	l = stacks->a->count;
	if (NULL == (algo = (t_algo_qs *)malloc(sizeof(t_algo_qs)))
		|| NULL == (algo->groups = (t_group *)malloc(l * sizeof(t_group))))
		return (NULL);
	algo->cur_group = NULL;
	algo->next_group = NULL;
	algo->groups_len = 0;
	(algo->groups)[(algo->groups_len)++] = (t_group){0, l - 1, 0, STACK_A};
	algo->cd_group = 0;
	return (algo);
}

void free_algo_qs(t_algo_qs *algo)
{
	if (NULL != algo->groups)
		free(algo->groups);
	free(algo);
}

t_group	*find_group(t_algo_qs *algo, int value)
{
	int		i;
	t_group	*group;

	i = 0;
	while (i < algo->groups_len)
	{
		group = algo->groups + i;
		if (value >= group->min && value <= group->max)
			return (group);
		i++;
	}
	return (NULL);
}

int	dist_unsorted_group(t_algo_qs *algo, t_int_array *stack)
{
	int		i;
	t_group	*group;

	i = 0;
	while (i < stack->count)
	{
		group = find_group(algo, (stack->data)[stack->count - 1 - i]);
		if (0 == group->dont_split)
			return (i);
		i += (group->max - group->min + 1);
	}
	return (-1);
}

void	update_split_requirements(t_stacks *stacks, t_algo_qs *algo)
{
	t_int_array	*stack;
	int			look_for;
	int			*start;
	int			len;

	if (algo->cur_group)
	{
		stack = algo->cur_group->stack == STACK_A ? stacks->a : stacks->b;
		look_for = algo->cur_group->stack == STACK_A ?
			algo->cur_group->max : algo->cur_group->min;
		start = stack->data + int_index(stack, look_for);
		len = algo->cur_group->max - algo->cur_group->min + 1;
		algo->cur_group->dont_split = algo->cur_group->stack == STACK_A ?
			swappable_decreasing(start, len) : swappable_increasing(start, len);
	}
	if (algo->next_group)
	{
		stack = algo->next_group->stack == STACK_A ? stacks->a : stacks->b;
		look_for = algo->next_group->stack == STACK_A ?
			algo->next_group->max : algo->next_group->min;
		start = stack->data + int_index(stack, look_for);
		len = algo->next_group->max - algo->next_group->min + 1;
		algo->next_group->dont_split = algo->next_group->stack == STACK_A ?
			swappable_decreasing(start, len) : swappable_increasing(start, len);
	}
}

void	align_group_to_split(t_stacks *stacks, t_algo_qs *algo)
{
	algo->dist_next_a = dist_unsorted_group(algo, stacks->a);
	algo->dist_next_b = dist_unsorted_group(algo, stacks->b);
	if (0 == algo->dist_next_a)
		algo->cur_group = find_group(algo, int_last(stacks->a));
	else if (algo->dist_next_a > 0) 
		do_op(stacks, "ra");
	else if (0 == algo->dist_next_b)
		algo->cur_group = find_group(algo, int_last(stacks->b));
	else if (algo->dist_next_a < 0)
		do_op(stacks, "rb");
	if (0 == algo->dist_next_a || 0 == algo->dist_next_b)
		algo->cd_group = algo->cur_group->max - algo->cur_group->min + 1;
}

void 	set_next_group(t_algo_qs *algo)
{
	algo->next_group = algo->groups + algo->groups_len++;
	algo->next_group_max = (algo->cur_group->min + algo->cur_group->max) / 2;
	algo->next_group->min = algo->cur_group->min;
	algo->next_group->max = algo->next_group_max;
	algo->cur_group->min = algo->next_group_max + 1;
	algo->next_group->stack = (STACK_A == algo->cur_group->stack) ? STACK_B : STACK_A;
}

void split_current_stack(t_stacks *stacks, t_algo_qs *algo)
{
	t_int_array *stack;

	stack = algo->cur_group->stack == STACK_A ? stacks->a : stacks->b;
	if (int_last(stack) > algo->next_group_max)
		do_op(stacks, algo->cur_group->stack == STACK_A ? "ra" : "pa");
	else
		do_op(stacks, algo->cur_group->stack == STACK_A ? "pb" : "rb");
	(algo->cd_group)--;
}

void swap_if_necessary(t_stacks *stacks, t_algo_qs *algo)
{
	t_int_array *stack;

	if (NULL == algo->cur_group)
		return ;
	stack = algo->cur_group->stack == STACK_A ? stacks->a : stacks->b;
	if (stack->count >= 2 && stack == stacks->a && int_last(stack) == (stack->data)[stack->count - 2] + 1)
		do_op(stacks, "sa");
	else if (stack->count >= 2 && stack == stacks->b && int_last(stack) == (stack->data)[stack->count - 2] - 1)
		do_op(stacks, "sb");
}

int split_stacks(t_stacks *stacks, t_algo_qs *algo)
{
	if (algo->dist_next_a < 0 && algo->dist_next_b < 0)
		// return (1);
		while (1)
			;
	swap_if_necessary(stacks, algo);
	if (0 == algo->cd_group)
	{
		update_split_requirements(stacks, algo);
		align_group_to_split(stacks, algo);
		set_next_group(algo);
	}
	else split_current_stack(stacks, algo);
	return (0);
}

int algo_quicksort(t_stacks *stacks)
{
	static t_algo_qs *algo = NULL;

	if (NULL == algo && NULL == (algo = new_algo_qs(stacks)))
		exit_message(0, "QS algorithm failed\n");
	else if (is_sorted_descending(stacks->a) && stacks->b->count == 0)
	{
		free_algo_qs(algo);
		return (1);
	}
	return (split_stacks(stacks, algo));
}