/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 15:53:33 by lmeyer            #+#    #+#             */
/*   Updated: 2017/01/05 16:16:26 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_push_swap.h"

static t_stack	*init_stack(size_t max)
{
	t_stack	*res;

	if ((res = (t_stack *)malloc(sizeof(t_stack))))
	{
		res->count = 0;
		if (!(res->data = (int *)ft_memalloc((max + 1) * sizeof(int))))
		{
			free(res);
			return (NULL);
		}
	}
	return (res);
}

t_data			*init_data(size_t max)
{
	t_data	*res;

	if ((res = (t_data *)malloc(sizeof(t_data))))
	{
		if (!(res->a = init_stack(max)))
		{
			free(res);
			return (NULL);
		}
		if (!(res->b = init_stack(max)))
		{
			free(res->a);
			free(res);
			return (NULL);
		}
	}
	return (res);
}
