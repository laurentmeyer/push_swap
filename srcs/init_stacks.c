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

static void allocate_stacks(t_stacks *stacks, int count)
{
	if (NULL == (stacks->a = new_int_array(count))
		|| (NULL == (stacks->b = new_int_array(count))))
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
		int_push(stacks->a, ft_atoi(current));
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
	stacks->instructions = NULL;
}

void	copy_stacks(t_stacks *dst, t_stacks *src)
{
	int	i;

	allocate_stacks(dst, src->a->count + src->b->count);
	i = 0;
	while (i < src->a->count)
		int_push(dst->a, src->a->data[i++]);
	dst->display = src->display;
	dst->visual = src->visual;
	dst->instructions = NULL;
}

void	normalize_stacks(t_stacks *stacks)
{
	t_int_array	*normalized;
	int			i;

	if (NULL == (normalized = int_values_to_ranks(stacks->a)))
		exit_message(ERR, "could not normalize\n");
	i = 0;
	while (i < normalized->count)
	{
		(stacks->a->data)[i] = (normalized->data)[i];
		++i;
	}
	free_int_array(normalized);
}