#include "push_swap.h"

int		pop(t_stack *stack)
{
	return ((stack->data)[--(stack->count)]);
}
