/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 10:16:15 by lmeyer            #+#    #+#             */
/*   Updated: 2018/08/25 10:16:16 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	del(void *content, size_t size)
{
	free(content);
	size = 0;
}

void		free_stack(t_stacks *stack)
{
	free_int_array(stack->a);
	free_int_array(stack->b);
	if (NULL != stack->instructions)
		ft_lstdel(&(stack->instructions), &del);
	if (NULL != stack->display)
	{
		mlx_destroy_image(stack->display->mlx_ptr, stack->display->img_ptr);
		mlx_destroy_window(stack->display->mlx_ptr, stack->display->window);
		free(stack->display);
	}
	free(stack);
}

void		free_push_swap(t_stacks **stacks)
{
	int	i;

	i = 0;
	while (i < ALGO_COUNT)
		free_stack(stacks[i++]);
	free(stacks);
}
