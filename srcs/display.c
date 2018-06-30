#include "push_swap.h"
#include "libft.h"
#include <time.h>
#include <stdlib.h>

#define MILLISECONDS 100L


static void pixel_put(t_display *d, int x, int y, unsigned int color)
{
	ft_memcpy(d->data_addr + (d->pixels_per_line * y + x) * d->chars_per_pixel, (const void *)(&color), d->chars_per_pixel);
}

static void draw_col(t_display *d, int stack, int col, int height)
{
	const unsigned int	fill = mlx_get_color_value(d->mlx_ptr, 0xcbced6);
    int                 x;
    int                 x_offset;
    int                 y;
    int                 y_offset;

    x_offset = col * d->pixels_per_col;
    y_offset = (stack + 1) * d->win_h / 2 - height;
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
                / (stacks->max - stacks->min) * d->win_h / 2);
        draw_col(d, 0, i, height);
        ++i;
    }
    i = 0;
    count = stacks->b.count;
    while (i < count)
    {
        height = (int)((float)(stacks->b.elements[i] - stacks->min)
                / (stacks->max - stacks->min) * d->win_h / 2);
        draw_col(d, 1, i, height);
        ++i;
    }
}

void    refresh_display(t_display *d, t_stacks *stacks)
{
	const unsigned int	    top = mlx_get_color_value(d->mlx_ptr, 0x2e3d5a);
	const unsigned int	    bottom = mlx_get_color_value(d->mlx_ptr, 0x272a31);
	const size_t		    len = d->pixels_per_line * d->win_h;
    const struct timespec   req = {(time_t)0, 1000000 * MILLISECONDS};
    size_t                  i;

    i = 0;
    while (i < len / 2)
        ((unsigned int *)d->data_addr)[i++] = top;
    while (i < len)
        ((unsigned int *)d->data_addr)[i++] = bottom;
    draw_cols(d, stacks);
    mlx_put_image_to_window(d->mlx_ptr, d->window, d->img_ptr, 0, 0);
    nanosleep(&req, NULL);
}