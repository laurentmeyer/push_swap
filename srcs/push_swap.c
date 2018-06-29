#include "push_swap.h"
#include <fcntl.h>

static void		print_instructions(t_list *list)
{
	while (list)
	{
		ft_putstr((char *)(list->content));
		ft_putchar('\n');
		list = list->next;
	}
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
		cur = ft_lstlen(stacks->instructions[i]);
		if (cur > min)
		{
			shortest = stacks->instructions[i];
			min = cur;
		}
		++i;
	}
	return (shortest);
}

static void	init_algos(t_algorithm algos[])
{
	algos[0] = &insertion;
}

static void	run_algorithms(t_stacks *stacks)
{
	int				i;
	int				j;
	t_stack			cpy_a;
	t_stack			cpy_b;
	t_algorithm		algos[ALGO_COUNT];

	init_algos(algos);
	if (!(cpy_a.elements = (int *)malloc(stacks->a.count * sizeof(int)))
		|| !(cpy_b.elements = (int *)malloc(stacks->a.count * sizeof(int))))
		exit_message(ERR, "Could not allocate memory\n");
	i = 0;
	while (i < ALGO_COUNT)
	{
		cpy_a.count = 0;
		cpy_b.count = 0;
		j = 0;
		while (j < stacks->a.count)
			push(&cpy_a, stacks->a.elements[j++]);
		stacks->instructions[i] = (algos[i])(cpy_a, cpy_b);
		++i;
	}
	free(cpy_a.elements);
	free(cpy_b.elements);
}

int main(int ac, char **av)
{
	t_stacks	stacks;

	if (NULL == (av = ft_argsplit(&ac, av)))
		exit_message(ERR, "Error\n");
	if (0 == --ac || NULL == *(++av))
		exit_message(ERR, "Error\n");
	init_stacks(&stacks, ac, av);
	run_algorithms(&stacks);
	print_instructions(shortest_instructions(&stacks));
	return (SUCCESS);
}

// erreur en cas de doublon