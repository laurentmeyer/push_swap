/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 10:17:10 by lmeyer            #+#    #+#             */
/*   Updated: 2018/08/25 10:17:12 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>
#include <fcntl.h>

static void		print_instructions(t_list *list)
{
	while (list)
	{
		ft_putstr((char *)(list->content));
		ft_putchar('\n');
		list = list->next;
	}
}

static int		shortest_instructions(t_stacks **stacks)
{
	int			i;
	int			cur;
	int			min;
	int			shortest;

	i = 0;
	min = INT_MAX;
	while (i < ALGO_COUNT)
	{
		cur = ft_lstlen(stacks[i]->instructions);
		if (cur > 0 && cur < min)
		{
			shortest = i;
			min = cur;
		}
		++i;
	}
	return (min > 0 ? shortest : -1);
}

static int		main_loop(t_stacks **stacks)
{
	static int	current = -1;
	int			short_stack;

	if (-1 == current)
		current = (stacks[0]->a->count <= 8);
	if (ALGO_COUNT == current)
	{
		if ((short_stack = shortest_instructions(stacks)) >= 0)
			print_instructions(stacks[short_stack]->instructions);
		free_push_swap(stacks);
		exit(0);
	}
	else if ((0 == current && 1 == algo_lds(stacks[current]))
		|| (1 == current && 1 == algo_small(stacks[current])))
		current++;
	return (SUCCESS);
}

static t_stacks	**init_push_swap(int ac, char **av)
{
	int			i;
	t_stacks	**ret;

	if (NULL == (ret = (t_stacks **)malloc(ALGO_COUNT * sizeof(t_stacks *))))
		return (NULL);
	i = 0;
	while (i < ALGO_COUNT)
	{
		if (NULL == (ret[i] = init_stacks(ac, av)))
			return (NULL);
		ret[i]->visual = 0;
		if (ERR == check_duplicates(ret[i]))
			exit_message(ERR, "Error\n");
		normalize_stacks(ret[i]);
		++i;
	}
	return (ret);
}

int				main(int ac, char **av)
{
	t_stacks	**stacks;

	if (NULL == (av = ft_argsplit(&ac, av)))
		exit_message(ERR, "Error\n");
	if (0 == --ac || NULL == *(++av))
		exit_message(ERR, "Error\n");
	if (NULL == (stacks = init_push_swap(ac, av)))
		exit_message(ERR, "Could not allocate stacks\n");
	while (42)
		main_loop(stacks);
	return (SUCCESS);
}
