#include "libft.h"
#include "ft_printf.h"
#include "push_swap.h"

void            init_display(t_stacks *stacks)
{
    t_display   *d;

    if (NULL == (d = (t_display *)malloc(sizeof(t_display))))
		exit_message(ERR, "Error t_display alloc\n");
	if (!(d->mlx_ptr = mlx_init()))
		exit_message(ERR, "Error mlx_init\n");
    d->win_h = MIN_WIN_H;
    d->win_w = stacks->a.count < MIN_WIN_W ? MIN_WIN_W : stacks->a.count;
	if (!(d->window = mlx_new_window(d->mlx_ptr, d->win_w, d->win_h, WIN_NAME)))
		exit_message(ERR, "Error mlx_new_window\n");
	if (!(d->img_ptr = mlx_new_image(d->mlx_ptr, d->win_w, d->win_h)))
		exit_message(ERR, "Error mlx_new_image\n");
	d->data_addr = mlx_get_data_addr(d->img_ptr, &(d->bits_per_pixel),
			&(d->size_line), &(d->endian));
	if (NULL == d->data_addr)
		exit_message(ERR, "Error mlx_data_address\n");
	d->chars_per_pixel = d->bits_per_pixel / 8;
	d->pixels_per_line = d->size_line / d->chars_per_pixel;
    d->pixels_per_col = d->win_w / stacks->a.count;
    stacks->display = d;
}