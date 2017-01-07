/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:22:15 by lmeyer            #+#    #+#             */
/*   Updated: 2017/01/05 20:05:52 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP
# define FT_PUSH_SWAP
# include <stdlib.h>

//enum			e_weights
//{
//	sa = 1,
//	sb = 1,
//	pa = 1,
//	pb = 1,
//	ra = 1,
//	rb = 1,
//	rra = 1,
//	rrb = 1,
//	ss = 2,
//	rr = 2,
//	rrr = 2
//};

enum			e_instructs
{
	sa,
	sb,
	ss,
	pa,
	pb,
	ra,
	rb,
	rr,
	rra,
	rrb,
	rrr
};

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
int				push(t_stack *stack, int i);
void			print_data(t_data *data, int visual_on);

#endif
