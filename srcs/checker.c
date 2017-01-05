/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:57:50 by lmeyer            #+#    #+#             */
/*   Updated: 2017/01/05 20:05:45 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ft_push_swap.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#define BUF_SIZE 1024

static int	error(void)
{
	ft_printf("Erreur\n");
	return (0);
}

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

//static char	*get_stdin(void)
//{
//	char	*res;
//	char	*tmp;
//	char	buf[BUF_SIZE + 1];
//
//	ft_bzero(buf, sizeof(buf));
//	if (!(res = ft_strdup("")))
//		return (NULL);
//	while (read(0, buf, BUF_SIZE))
//	{
//		tmp = res;
//		if (!(res = ft_strjoin(res, buf)))
//			return (NULL);
//		free(tmp);
//		ft_bzero(buf, sizeof(buf));
//	}
//	return (res);
//}

int			main(int ac, char **av)
{
	t_data	*data;
	char	*s;
	int		i;

	if (ac < 2 || !(data = init_data(--ac)) || !fill_stack(data->a, av, ac))
		return(error());
	print_data(data);
//	if (!(s = get_stdin()))
//		return (error());
	while (42)
	{
		ft_printf("debut boucle");
		if (!(i = get_next_line(STDIN_FILENO, &s)))
			return (ft_printf("fin de get next line \n"));
		ft_printf("gnl return = %d", i);
		ft_printf("s = %s\n", s);
		free(s);
	}
	return (0);
}
