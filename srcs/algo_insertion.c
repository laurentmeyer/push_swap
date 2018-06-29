#include "push_swap.h"

t_list	*insertion(t_stack a, t_stack b)
{
	t_list	*ret;
	char	content[] = "toto";

	(void)a;
	(void)b;
	ret = ft_lstnew(&content, sizeof(int));
	return (ret);
}
