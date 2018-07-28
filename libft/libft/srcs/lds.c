#include "lds.h"
#include <stdlib.h>

t_lds		*init_lds(t_int_array *array)
{
	t_lds	*lds;

	if (NULL == (lds = (t_lds *)malloc(sizeof(t_lds))))
		return (NULL);
	lds->n = array->count;
	lds->i = 0;
	lds->l = 0;
	lds->x = array->data;
	if (NULL == (lds->m = (int *)malloc((lds->n + 1) * sizeof(int)))
		|| NULL == (lds->p = (int *)malloc(lds->n * sizeof(int))))
		return (NULL);
	(lds->m)[0] = 0;
	return (lds);
}

void		free_lds(t_lds *lds)
{
	free(lds->m);
	free(lds->p);
	free(lds);
}

t_int_array *build_lds(t_lds *lds)
{
	t_int_array *s;
	int			k;
	int			l;

	l = lds->l;
	if (NULL == (s = new_int_array(l)))
		// exit_message(0, "couldn't build LDS\n");
		return (NULL);
	k = (lds->m)[l];
	while (l > 0)
	{
		int_set(s, l - 1, (lds->x)[k]);
		k = (lds->p)[k];
		--l;
	}
	return (s);
}

// void print_lds(t_lds *lds)
// {
// 	int			ind;
// 	t_int_array *s;

// 	ft_printf("X[%d] = %d\n", lds->i, (lds->x)[lds->i]);
// 	ft_printf("L = %d", lds->l);
// 	ft_putstr("\nnew M: ");
// 	ind = 1;
// 	while (ind <= lds->l)
// 		ft_printf("%d ", (lds->m)[ind++]);
// 	ft_putstr("\nnew P: ");
// 	ind = 0;
// 	while (ind < lds->i)
// 		ft_printf("%d ", (lds->p)[ind++]);
// 	ft_putstr("\nnew LIS: ");
// 	s = build_lds(lds);
// 	ind = 0;
// 	while (ind < s->count)
// 		ft_printf("%d ", (s->data)[ind++]);
// 	free_int_array(s);
// 	ft_putstr("\n\n\n");
// }

static int get_new_l(t_lds *lds)
{
	int lo;
	int hi;
	int mid;

	lo = 1;
	hi = lds->l;
	while (lo <= hi)
	{
		mid = (lo + hi) / 2;
		if ((lds->x)[(lds->m)[mid]] > (lds->x)[lds->i])
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	return (lo);
}

t_int_array *get_lds(t_int_array *array)
{
	t_lds *lds;
	t_int_array *s;
	int newl;

	if (NULL == (lds = init_lds(array)))
		// exit_message(0, "couldn't find LDS\n");
		return (NULL);
	while (lds->i < lds->n)
	{
		newl = get_new_l(lds);
		(lds->p)[lds->i] = (lds->m)[newl - 1];
		(lds->m)[newl] = lds->i;
		if (newl > lds->l)
			lds->l = newl;
		++(lds->i);
	}
	s = build_lds(lds);
	free_lds(lds);
	return (s);
}