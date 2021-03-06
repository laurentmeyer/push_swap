/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 10:15:42 by lmeyer            #+#    #+#             */
/*   Updated: 2018/09/28 17:33:06 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <time.h>
#include <stdlib.h>
#define C_TOP 0x2e3d5a
#define C_BOTTOM 0x272a31

static void	pixel_put(t_display *d, int x, int y, unsigned int color)
{
	ft_memcpy(d->data_addr + (d->pixels_per_line * y + x) * d->chars_per_pixel,
			(const void *)(&color), d->chars_per_pixel);
}

static void	draw_col(t_display *d, int array, int col, int height)
{
	unsigned int	fill;
	int				x;
	int				x_offset;
	int				y;
	int				y_offset;

	fill = mlx_get_color_value(d->mlx_ptr, 0xcbced6);
	x_offset = col * d->pixels_per_col;
	y_offset = (array + 1) * d->win_h / 2 - height;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < d->pixels_per_col)
		{
			pixel_put(d, x + x_offset, y + y_offset, fill);
			++x;
		}
		++y;
	}
}

static void	draw_cols(t_stacks *stacks)
{
	int			i;
	int			count;
	int			height;
	t_display	*d;

	i = 0;
	d = stacks->display;
	count = stacks->a->count;
	while (i < count)
	{
		height = (int)((float)((stacks->a->data)[i] + 1)
				/ (stacks->a->count + stacks->b->count + 1) * d->win_h / 2);
		draw_col(d, 0, i, height);
		++i;
	}
	i = 0;
	count = stacks->b->count;
	while (i < count)
	{
		height = (int)((float)((stacks->b->data)[i] + 1)
				/ (stacks->a->count + stacks->b->count + 1) * d->win_h / 2);
		draw_col(d, 1, i, height);
		++i;
	}
}

void		refresh_display(t_stacks *stacks)
{
	size_t			count;
	t_display		*d;
	size_t			i;

	i = 0;
	d = stacks->display;
	count = d->pixels_per_line * d->win_h;
	while (i < count / 2)
		((unsigned int *)d->data_addr)[i++] = C_TOP;
	while (i < count)
		((unsigned int *)d->data_addr)[i++] = C_BOTTOM;
	draw_cols(stacks);
	nanosleep(&((struct timespec){0, d->nanoseconds}), NULL);
	mlx_put_image_to_window(d->mlx_ptr, d->window, d->img_ptr, 0, 0);
}
