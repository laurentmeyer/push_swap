#include "libft.h"
#include <stdlib.h>

void ft_free_strsplit(char ***to_free)
{
	char	**as;
	int		i;

	i = 0;
	while (*(as = *to_free + i++))
		ft_strdel(as);
	free(*to_free);
}