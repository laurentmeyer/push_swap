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
#include <fcntl.h>

static int		main_loop(t_stacks *stacks)
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
		free_stack(stacks);
		exit(0);
	}
	else if (ERR == gnl || ERR == do_op(stacks, s))
		exit_message(ERR, "Error\n");
	if (stacks->visual)
		refresh_display(stacks);
	free(s);
	return (SUCCESS);
}

static t_stacks	*init_checker(int ac, char **av)
{
	int			visual;
	t_stacks	*ret;

	if ((visual = ft_strequ("-v", av[0])) == 1)
	{
		--ac;
		++av;
	}
	if (NULL == (ret = init_stacks(ac, av)))
		return (NULL);
	ret->visual = visual;
	if (ERR == check_duplicates(ret))
		exit_message(ERR, "Error\n");
	normalize_stacks(ret);
	if (ret->visual)
	{
		init_display(ret);
		refresh_display(ret);
		mlx_loop_hook(ret->display->mlx_ptr, &main_loop, ret);
	}
	return (ret);
}

int				main(int ac, char **av)
{
	t_stacks *stack;

	if (NULL == (av = ft_argsplit(&ac, av)))
		exit_message(ERR, "Error\n");
	if (0 == --ac || NULL == *(++av))
		return (SUCCESS);
	if (NULL == (stack = init_checker(ac, av)))
		exit_message(ERR, "Could not allocate stacks\n");
	if (stack->visual)
		mlx_loop(stack->display->mlx_ptr);
	else
		while (42)
			main_loop(stack);
	return (SUCCESS);
}
