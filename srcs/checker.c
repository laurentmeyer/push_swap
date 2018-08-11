/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:57:50 by lmeyer            #+#    #+#             */
/*   Updated: 2017/01/07 16:54:17 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static int main_loop(t_stacks *stacks)
{
	int			gnl;
	char		*s;

	gnl = gnlite(STDIN_FILENO, &s);
	if (0 == gnl)
	{
		if (is_sorted_descending(stacks->a) && 0 == stacks->b->count)
			ft_putstr("OK\n");
		else
			ft_putstr("KO\n");
		exit(0);
	}
	else if (ERR == gnl || ERR == do_op(stacks, s))
		exit_message(ERR, "Error\n");
	if (stacks->visual)
		refresh_display(stacks);
	free(s);
	return (SUCCESS);
}

int main(int ac, char **av)
{
	t_stacks stacks;

	if (NULL == (av = ft_argsplit(&ac, av)))
		exit_message(ERR, "Error\n");
	if (0 == --ac || NULL == *(++av))
		return (SUCCESS);
	stacks.visual = ft_strequ("-v", av[0]);
	if (stacks.visual == 1)
	{
		--ac;
		++av;
	}
	init_stacks(&stacks, ac, av);
	normalize_stacks(&stacks);
	if (ERR == check_duplicates(&stacks))
		exit_message(ERR, "Error\n");
	if (stacks.visual)
	{
		init_display(&stacks);
		refresh_display(&stacks);
		mlx_loop_hook(stacks.display->mlx_ptr, &main_loop, &stacks);
		mlx_loop(stacks.display->mlx_ptr);
	}
	while (42)
		main_loop(&stacks);
	return (SUCCESS);
}

// bien penser à enlever le comment du Makefile