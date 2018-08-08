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
	t_int_array	*sorted;
	int			step;
	int			selection_count;
}				t_lds_algo;

void			init_stacks(t_stacks *stacks, int ac, char **av);
void			copy_stacks(t_stacks *dst, t_stacks *src);
int				exit_message(int exit_code, char *message);
int				do_op(t_stacks *stacks, char *s);
void			init_display(t_stacks *stacks);
void    		refresh_display(t_stacks *stacks);
int  			is_sorted(t_int_array *array);
int				max_index(t_int_array *array); // a mettre dans libft
void    		rotate_min_a_on_top(t_stacks *stacks);
void 			rotate_max_b_on_top(t_stacks *stacks);
int				simple_selection(t_stacks *stacks);
int				algo_quicksort(t_stacks *stacks);
int				advanced_selection(t_stacks *stacks);
t_int_array 	*get_lds(t_int_array *array);
int				algo_lds(t_stacks *stacks);
int				sortable_by_rotation(t_int_array *array, int ascending);
int				try_push_b_value_in_sorted_a(t_stacks *stacks, int value);
int 			swappable_increasing(int *array, int len);
int				swappable_decreasing(int *array, int len);


#endif