#include "libft.h"
#include <stdlib.h>

static char	**allocate_args(int *aac, char **av)
{
	int		ac;
	int 	i;
	char	**ret;

	ac = *aac;
	*aac = 0;
	i = 0;
	while (i < ac)
		*aac += ft_countwords(av[i++], ' ');
	ret = (char **)malloc((*aac + 1) * sizeof(char *));
	if (NULL != ret)
		ret[*aac] = NULL;
	return (ret);
}

static char **fill_args(char **dst, char *src, int *index)
{
	int i;
	char **tmp;

	if (NULL == (tmp = ft_strsplit(src, ' ')))
		return (NULL);
	i = 0;
	while (NULL != tmp[i])
	{
		dst[*index] = tmp[i++];
		*index += 1;
	}
	free(tmp[i]);
	free(tmp);
	return (dst);
}

char **ft_argsplit(int *aac, char **av)
{
	int i;
	int j;
	int ac;
	char **ret;

	ac = *aac;
	ret = NULL;
	if (NULL == (ret = allocate_args(aac, av)))
		return (NULL);
	i = 0;
	j = 0;
	while (i < ac)
	{
		if (!ft_strchr(av[i], ' '))
			ret[j++] = av[i];
		else if (NULL == fill_args(ret, av[i], &j))
			return (NULL);
		++i;
	}
	return (ret);
}