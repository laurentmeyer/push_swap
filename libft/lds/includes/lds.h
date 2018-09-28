/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lds.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 17:50:46 by lmeyer            #+#    #+#             */
/*   Updated: 2018/09/28 19:56:09 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LDS_H
# define LDS_H

# include "int_array.h"

typedef struct	s_lds
{
	int			n;
	int			l;
	int			i;
	int			*x;
	int			*m;
	int			*p;
}				t_lds;

t_int_array		*get_lds_int_array(t_int_array *array);
t_int_array		*get_lds_int_ptr(int *src, int len);
t_lds			*init_lds(t_int_array *array);
void			free_lds(t_lds *lds);

#endif
