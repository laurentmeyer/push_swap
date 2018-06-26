#include "push_swap.h"
#include "libft.h"
#include <stdlib.h>

static void pixel_put(t_display *d, int x, int y, unsigned int color)
{
	ft_memcpy(d->data_addr + (d->pixels_per_line * y + x) * d->chars_per_pixel, (const void *)(&color), d->chars_per_pixel);
}

void	init_display(t_stacks *stacks)
{
    t_display   *d;

    if (NULL == (d = (t_display *)malloc(sizeof(t_display))))
		exit_message(ERR, "Error t_display alloc\n");
	if (!(d->mlx_ptr = mlx_init()))
		exit_message(ERR, "Error mlx_init\n");
	if (!(d->window = mlx_new_window(d->mlx_ptr, WIN_W, WIN_H, WIN_NAME)))
		exit_message(ERR, "Error mlx_new_window\n");
	if (!(d->img_ptr = mlx_new_image(d->mlx_ptr, WIN_W, WIN_H)))
		exit_message(ERR, "Error mlx_new_image\n");
	d->data_addr = mlx_get_data_addr(d->img_ptr, &(d->bits_per_pixel),
			&(d->size_line), &(d->endian));
	if (NULL == d->data_addr)
		exit_message(ERR, "Error mlx_data_address\n");
	d->chars_per_pixel = d->bits_per_pixel / 8;
	d->pixels_per_line = d->size_line / d->chars_per_pixel;
    d->pixels_per_col = WIN_W / stacks->a.count;
    stacks->display = d;
}

static void draw_col(t_display *d, int stack, int col, int height)
{
	const unsigned int	fill = mlx_get_color_value(d->mlx_ptr, 0xffffff);
    int                 x;
    int                 x_offset;
    int                 y;
    int                 y_offset;

    x_offset = col * d->pixels_per_col;
    y_offset = (stack + 1) * WIN_H / 2 - height;
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

static void draw_cols(t_display *d, t_stacks *stacks)
{
    int                 i;
    int                 count;
    int                 height;

    i = 0;
    count = stacks->a.count;
    while (i < count)
    {
        height = (int)((float)(stacks->a.elements[i] - stacks->min)
                / (stacks->max - stacks->min) * WIN_H / 2);
        draw_col(d, 0, i, height);
        ++i;
    }
    i = 0;
    count = stacks->b.count;
    while (i < count)
    {
        height = (int)((float)(stacks->b.elements[i] - stacks->min)
                / (stacks->max - stacks->min) * WIN_H / 2);
        draw_col(d, 1, i, height);
        ++i;
    }
}

void    refresh_display(t_display *d, t_stacks *stacks)
{
	const unsigned int	top = mlx_get_color_value(d->mlx_ptr, 0xff0000);
	const unsigned int	bottom = mlx_get_color_value(d->mlx_ptr, 0x00ff00);
	const size_t		len = d->pixels_per_line * WIN_H;
    size_t              i;

    i = 0;
    while (i < len / 2)
        ((unsigned int *)d->data_addr)[i++] = top;
    while (i < len)
        ((unsigned int *)d->data_addr)[i++] = bottom;
    draw_cols(d, stacks);
    mlx_put_image_to_window(d->mlx_ptr, d->window, d->img_ptr, 0, 0);
}