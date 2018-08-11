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
# include "libft.h"
# include "ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# define PUSH_SWAP
# define ERR -1
# define SUCCESS 0
# define DESCENDING 0
# define ASCENDING 1
# define ALGO_COUNT 2
# define DIR_NONE 0
# define DIR_RA 1
# define DIR_RB 2
# define DIR_RR 3
# define DIR_REV_RA 4
# define DIR_REV_RB 5
# define DIR_REV_RR 6

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
	int			win_h;
	int			win_w;
}				t_display;

typedef struct	s_stacks
{
	t_int_array	*a;
	t_int_array	*b;
	t_display	*display;
	t_list		*instructions;
	int			visual;
}				t_stacks;

typedef struct	s_lds_algo
{
	int			step;
	int			selection_count;
}				t_lds_algo;

void			init_stacks(t_stacks *stacks, int ac, char **av);
void			normalize_stacks(t_stacks *stacks);
int				check_duplicates(t_stacks *stacks);
void			copy_stacks(t_stacks *dst, t_stacks *src);
int				exit_message(int exit_code, char *message);
int				do_op(t_stacks *stacks, char *s);
void			init_display(t_stacks *stacks);
void    		refresh_display(t_stacks *stacks);
int				algo_small(t_stacks *stacks);
t_int_array		*distance_array(t_stacks *stacks);
int				algo_lds(t_stacks *stacks);
int  			is_sorted_descending(t_int_array *array);
int				descending_by_rotation(t_int_array *array);
int 			swappable_increasing(int *array, int len);
int				swappable_decreasing(int *array, int len);
void			rotate_value_on_top(t_stacks *stacks, t_int_array *stack, int value);
int				swap_a_if_necessary(t_stacks *stacks);
int				move_a_if_swap_rot_decreasing(t_stacks *stacks);
int		 		move_b_if_swap_rot_increasing(t_stacks *stacks);
int				try_push_b_value_in_sorted_a(t_stacks *stacks, int value);

#endif