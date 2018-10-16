/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:22:26 by lmeyer            #+#    #+#             */
/*   Updated: 2018/09/28 20:22:28 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lds.h"
#include <stdlib.h>

t_lds		*init_lds(t_int_array *array)
{
	t_lds	*lds;

	if (NULL == (lds = (t_lds *)malloc(sizeof(t_lds))))
		return (NULL);
	lds->n = array->count;
	lds->i = 0;
	lds->l = 0;
	lds->x = array->data;
	if (NULL == (lds->m = (int *)malloc((lds->n + 1) * sizeof(int)))
		|| NULL == (lds->p = (int *)malloc(lds->n * sizeof(int))))
		return (NULL);
	(lds->m)[0] = 0;
	return (lds);
}

void		free_lds(t_lds *lds)
{
	free(lds->m);
	free(lds->p);
	free(lds);
}
