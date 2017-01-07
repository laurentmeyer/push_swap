/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 16:12:49 by lmeyer            #+#    #+#             */
/*   Updated: 2017/01/07 16:34:17 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP
# define PUSH_SWAP
# include <stdlib.h>

typedef struct	s_stack
{
	int			count;
	int			*data;
}				t_stack;

typedef struct	s_data
{
	t_stack		*a;
	t_stack		*b;
}				t_data;

t_data			*init_data(size_t max);
int				do_op(t_data *data, char *s);
int				push(t_stack *stack, int i);
int				pop(t_stack *stack);
void			print_data(t_data *data, int visual_on);

#endif
