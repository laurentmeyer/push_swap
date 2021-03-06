/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 10:17:38 by lmeyer            #+#    #+#             */
/*   Updated: 2018/08/25 10:17:39 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_duplicates(t_stacks *stacks)
{
	int i;
	int j;

	i = 0;
	while (i < stacks->a->count - 1)
	{
		j = i + 1;
		while (j < stacks->a->count)
		{
			if ((stacks->a->data)[i] == (stacks->a->data)[j])
				return (ERR);
			++j;
		}
		++i;
	}
	return (SUCCESS);
}
