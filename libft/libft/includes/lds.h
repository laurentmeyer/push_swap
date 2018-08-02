#ifndef LDS_H
# define LDS_H

# include "int_array.h"

typedef struct	s_lds
{
	int			n;
	int			l;
	int			i;
	int			*x;
	int			*m;
	int			*p;
}				t_lds;

t_int_array		*get_lds_int_array(t_int_array *array);
t_int_array		*get_lds_int_ptr(int *src, int len);

#endif