#include "push_swap.h"

int		pop(t_stack *stack)
{
	stack->count -= 1;
	return ((stack->elements)[stack->count]);
}
