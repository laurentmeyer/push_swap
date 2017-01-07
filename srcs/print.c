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

void	print_data(t_data *data, int visual_on)
{
	int	i;
	int	max;

	if (!visual_on)
		return;
	max = data->a->count > data->b->count ? data->a->count : data->b->count;
	ft_printf("/---------------------------\\\n");
	ft_printf("|%10s   |%10s   |\n", "A", "B");
	ft_printf("|---------------------------|\n");
	i = max;
	while (--i >= 0)
	{
		if (i >= data->a->count)
			ft_printf("|%12s |%12d |\n", "", (data->b->data)[i]);
		else if (i >= data->b->count)
			ft_printf("|%12d |%12s |\n", (data->a->data)[i], "");
		else
			ft_printf("|%12d |%12d |\n", (data->a->data)[i], (data->b->data)[i]);
	}
	ft_printf("\\---------------------------/\n");
}
