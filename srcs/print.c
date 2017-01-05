/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:19:18 by lmeyer            #+#    #+#             */
/*   Updated: 2017/01/05 16:23:16 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include "ft_printf.h"

void	print_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->a->count)
	{
		ft_printf("a[%zu] = %d\n", i, (data->a->data)[i]);
		++i;
	}
	i = 0;
	while (i < data->b->count)
	{
		ft_printf("b[%zu] = %d\n", i, (data->b->data)[i]);
		++i;
	}
}
