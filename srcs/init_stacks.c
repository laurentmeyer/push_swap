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

#define STRICT 1

t_stacks	*init_stacks(int ac, char **av)
{
	t_stacks	*s;
	int			i;
	char		*current;

	if (0 == ac)
		exit_message(ERR, "Error\n");
	i = 0;
	if (!(s = (t_stacks *)malloc(sizeof(t_stacks)))
		|| !(s->a = new_int_array(ac))
		|| !(s->b = new_int_array(ac)))
		exit_message(ERR, "Allocation of stacks failed\n");
	i = 0;
	while (i < ac)
	{
		current = av[ac - 1 - i];
		if (!ft_valid_int_str(current, STRICT))
			exit_message(ERR, "Error\n");
		int_push(s->a, ft_atoi(current));
		++i;
	}
	s->display = NULL;
	s->instructions = NULL;
	return (s);
}

void		normalize_stacks(t_stacks *stacks)
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
