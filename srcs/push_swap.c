#include "push_swap.h"
#include <fcntl.h>

static void		print_instructions_exit(t_list *list)
{
	while (list)
	{
		ft_putstr((char *)(list->content));
		ft_putchar('\n');
		list = list->next;
	}
	exit(0);
}

static t_list	*shortest_instructions(t_stacks *stacks)
{
	int			i;
	int			cur;
	int			min;
	t_list		*shortest;

	i = 0;
	min = 0;
	shortest = NULL;
	while (i < ALGO_COUNT)
	{
		cur = ft_lstlen(stacks[i].instructions);
		if (cur > min)
		{
			shortest = stacks[i].instructions;
			min = cur;
		}
		++i;
	}
	return (shortest);
}

static int main_loop(t_stacks *copies)
{
	static int	current = 1; //

	if (ALGO_COUNT == current)
		print_instructions_exit(shortest_instructions(copies));
	else if ((0 == current && 1 == simple_selection(&(copies[current])))
		|| (1 == current && 1 == algo_small(&(copies[current]))))
		// || (1 == current && 1 == algo_lds(&(copies[current]))))
		// || (1 == current && 1 == algo_quicksort(&(copies[current]))))
		current++;
	return (SUCCESS);
}

int main(int ac, char **av)
{
	t_stacks	original;
	t_stacks	copies[ALGO_COUNT];
	int			i;

	if (NULL == (av = ft_argsplit(&ac, av)))
		exit_message(ERR, "Error\n");
	if (0 == --ac || NULL == *(++av))
		exit_message(ERR, "Error\n");
	init_stacks(&original, ac, av);
	normalize_stacks(&original);
	if (ERR == check_duplicates(&original))
		exit_message(ERR, "Error\n");
	if (original.visual)
	{
		refresh_display(&(copies[0]));
		init_display(&original);
	}
	i = 0;
	while (i < ALGO_COUNT)
		copy_stacks(&(copies[i++]), &original);
	if (original.visual)
	{
		refresh_display(&(copies[0]));
		mlx_loop_hook(original.display->mlx_ptr, &main_loop, copies);
		mlx_loop(original.display->mlx_ptr);
	}
	while (42)
		main_loop(copies);
	return (SUCCESS);
}

// erreur en cas de doublon