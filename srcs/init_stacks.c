/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 15:53:33 by lmeyer            #+#    #+#             */
/*   Updated: 2017/01/07 16:13:04 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "push_swap.h"
#include <stdlib.h>
#include <limits.h>

#define STRICT 0

static void	init_constants(t_stacks *stacks)
{
	int	i;
	int	current;
	int	min;
	int	max;

	min = INT_MAX;
	max = INT_MIN;
	i = stacks->a.count - 1;
	while (i >= 0)
	{
		current = stacks->a.data[i];
		if (current > max)
			max = current;
		if (current < min)
			min = current;
		--i;
	}
	stacks->min = min;
	stacks->max = max;
	stacks->count = stacks->a.count;
	stacks->instructions = NULL;
}

static void allocate_stacks(t_stacks *stacks, int count)
{
	stacks->a.count = 0;
	stacks->b.count = 0;
	if (NULL == (stacks->a.data = (int *)malloc(count * sizeof(int)))
		|| NULL == (stacks->b.data = (int *)malloc(count * sizeof(int))))
		exit_message(ERR, "Allocation of stacks failed\n");
}

static void	fill_stacks(t_stacks *stacks, int ac, char **av)
{
	int		i;
	char	*current;

	i = 0;
	while (i < ac)
	{
		current = av[ac - 1 - i];
		if (!ft_valid_int_str(current, STRICT))
			exit_message(ERR, "Error\n");
		int_push(&(stacks->a), ft_atoi(current));
		++i;
	}
}

void init_stacks(t_stacks *stacks, int ac, char **av)
{
	int		count;
	int		i;

	if (0 == ac)
		exit_message(ERR, "Error\n");
	i = 0;
	count = 0;
	while (i < ac)
		count += ft_countwords(av[i++], ' ');
	allocate_stacks(stacks, count);
	fill_stacks(stacks, ac, av);
	init_constants(stacks);
}

void	copy_stacks(t_stacks *dst, t_stacks *src)
{
	int	i;

	allocate_stacks(dst, src->count);
	i = 0;
	while (i < src->a.count)
		int_push(&(dst->a), src->a.data[i++]);
	dst->display = src->display;
	init_constants(dst);
}