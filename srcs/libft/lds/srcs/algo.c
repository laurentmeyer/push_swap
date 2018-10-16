/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:22:18 by lmeyer            #+#    #+#             */
/*   Updated: 2018/09/28 20:25:14 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lds.h"
#include <stdlib.h>

t_int_array		*build_lds(t_lds *lds)
{
	t_int_array	*s;
	int			k;
	int			l;

	l = lds->l;
	if (NULL == (s = new_int_array(l)))
		return (NULL);
	k = (lds->m)[l];
	while (l > 0)
	{
		int_set(s, l - 1, (lds->x)[k]);
		k = (lds->p)[k];
		--l;
	}
	return (s);
}

static int		get_new_l(t_lds *lds)
{
	int	lo;
	int	hi;
	int	mid;

	lo = 1;
	hi = lds->l;
	while (lo <= hi)
	{
		mid = (lo + hi) / 2;
		if ((lds->x)[(lds->m)[mid]] > (lds->x)[lds->i])
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	return (lo);
}

t_int_array		*get_lds_int_array(t_int_array *array)
{
	t_lds		*lds;
	t_int_array	*s;
	int			newl;

	if (NULL == (lds = init_lds(array)))
		return (NULL);
	while (lds->i < lds->n)
	{
		newl = get_new_l(lds);
		(lds->p)[lds->i] = (lds->m)[newl - 1];
		(lds->m)[newl] = lds->i;
		if (newl > lds->l)
			lds->l = newl;
		++(lds->i);
	}
	s = build_lds(lds);
	free_lds(lds);
	return (s);
}

t_int_array		*get_lds_int_ptr(int *src, int len)
{
	t_int_array	array;

	array.capacity = len;
	array.count = len;
	array.data = src;
	return (get_lds_int_array(&array));
}
