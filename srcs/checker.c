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

#include "libft.h"
#include "ft_printf.h"
#include "push_swap.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#define ERR -1

static int	fill_stack(t_stack *a, char **av, int ac)
{
	while (ac > 0)
	{
		if (!ft_valid_int_str(av[ac]))
			return(0);
		else
			push(a, ft_atoi(av[ac]));
		--ac;
	}
	return (1);
}

static int	is_sorted(t_data *data)
{
	int	i;

	if (data->b->count != 0)
		return (0);
	if (data->a->count == 1)
		return (1);
	i = -1;
	while (++i < data->a->count - 1)
		if ((data->a->data)[i] <= (data->a->data)[i + 1])
			return (0);
	return (1);
}

int			main(int ac, char **av)
{
	t_data	*data;
	char *s;
	int gnl;
	int visual;

	if (ac-- < 2)
		return (ft_dprintf(STDERR_FILENO, "%s\n", "Error"));
	if ((visual = ft_strequ("-v", av[1]) ? 1 : 0) && ++av)
		--ac;
	if (!(data = init_data(ac)) || !fill_stack(data->a, av, ac))
		return (ft_dprintf(STDERR_FILENO, "%s\n", "Error"));
	print_data(data, visual);
	while ((gnl = gnlite(STDIN_FILENO, &s)))
	{
		if (gnl == ERR || do_op(data, s) == ERR)
			return (ft_dprintf(STDERR_FILENO, "%s\n", "Error"));
		print_data(data, visual);
		free(s);
	}
	ft_printf("%s\n", is_sorted(data) ? "OK" : "KO");
	return (0);
}
