/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:19:18 by lmeyer            #+#    #+#             */
/*   Updated: 2017/01/07 16:13:11 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "ft_printf.h"

void	print_stacks(t_stacks stacks, int visual_on)
{
	int	i;
	int	max;

	if (!visual_on)
		return;
	max = stacks.a.count > stacks.b.count ? stacks.a.count : stacks.b.count;
	ft_printf("/---------------------------\\\n");
	ft_printf("|%10s   |%10s   |\n", "A", "B");
	ft_printf("|---------------------------|\n");
	i = max;
	while (--i >= 0)
	{
		if (i >= stacks.a.count)
			ft_printf("|%12s |%12d |\n", "", (stacks.b.elements)[i]);
		else if (i >= stacks.b.count)
			ft_printf("|%12d |%12s |\n", (stacks.a.elements)[i], "");
		else
			ft_printf("|%12d |%12d |\n", (stacks.a.elements)[i], (stacks.b.elements)[i]);
	}
	ft_printf("\\---------------------------/\n");
}
