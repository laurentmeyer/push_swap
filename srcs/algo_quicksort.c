#include "push_swap.h"

#define STEP_SPLIT 0
#define STEP_MERGE 1

int	median_index(t_int_array *array)
{
	t_int_array	*sorted;
	int			median;

	if (NULL == (sorted = copy_int_array(array)))
		exit_message(0, "Couldn't find median\n");
	sort_int_array(sorted);
	median = (sorted->data)[sorted->count / 2];
	free_int_array(sorted);
	return (median);
}

int	algo_quicksort(t_stacks *stacks)
{
	static int	step = 0;

	if (is_sorted(stacks->a) && stacks->b.count == 0)
		return (1);
	if (0 == (step % 2))
	{
		if (0 == stacks->a.count)
			step++;
	}
	return (0);
}

// on a une connaissance totale de ce qui est deja ttié ou pas, pas besoin de trier ce qui l'est déjà
// extraire la suite la plus croissante possible