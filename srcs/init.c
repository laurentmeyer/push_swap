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

static void	init_min_max(t_stacks *stacks)
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
		current = stacks->a.elements[i];
		if (current > max)
			max = current;
		if (current < min)
			min = current;
		--i;
	}
	stacks->min = min;
	stacks->max = max;
}

static void allocate_stacks(t_stacks *stacks, int ac, char **av)
{
	int 	i;
	int		count;

	i = 0;
	count = 0;
	while (i < ac)
		count += ft_countwords(av[i++], ' ');
	stacks->a.count = 0;
	stacks->b.count = 0;
	if (NULL == (stacks->a.elements = (int *)malloc(ac * sizeof(int)))
		|| NULL == (stacks->b.elements = (int *)malloc(ac * sizeof(int))))
		exit_message(ERR, "Allocation of stacks failed\n");
}

void fill_stacks(t_stacks *stacks, int ac, char **av)
{
  int   i;
  char  *current;
 
  i = 0;
  while (i < ac)
  {
    current = av[ac - 1 - i];
    if (!ft_valid_int_str(current))
      exit_message(ERR, "Error\n");
	push(&(stacks->a), ft_atoi(current));
	++i;
  }
  init_min_max(stacks);
}


void init_stacks(t_stacks *stacks, int ac, char **av)
{
	int		count;
	char	**curargs;

	if (0 == ac)
		exit_message(ERR, "Error\n");
	allocate_stacks(stacks, ac, av);
	count = ft_countwords(av[0], ' ');
	if (1 != count)
	{
		curargs = ft_strsplit(av[0], ' ');
		fill_stacks(stacks, count, curargs);
		ft_free_strsplit(&curargs);
	}
	else
		fill_stacks(stacks, ac, av);
}