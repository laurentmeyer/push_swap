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

# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# define PUSH_SWAP
# define ERR -1
# define SUCCESS 0
# define WIN_H 400
# define WIN_W 400
# define WIN_NAME "checker"

typedef struct	s_display
{

	void		*mlx_ptr;
	void   		*window;
	void		*img_ptr;
	char		*data_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			chars_per_pixel;
	int			pixels_per_line;
	int			pixels_per_col;
}				t_display;

typedef struct	s_stack
{
	int			count;
	int			*elements;
}				t_stack;

typedef struct	s_stacks
{
	t_stack		a;
	t_stack		b;
	t_display	*display;
	int			min;
	int			max;
	int			visual;
}				t_stacks;

void			init_stacks(t_stacks *stacks, int ac, char **av);
int				exit_message(int exit_code, char *message);
int				do_op(t_stacks *data, char *s);
void			push(t_stack *stack, int i);
int				pop(t_stack *stack);
void			print_stacks(t_stacks stacks, int visual_on);
void			init_display(t_stacks *stacks);
void    		refresh_display(t_display *d, t_stacks *stacks);


#endif