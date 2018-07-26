#ifndef INT_ARRAY
# define INT_ARRAY

typedef struct	s_int_array
{
	int			capacity;
	int			count;
	int			*data;
}				t_int_array;


void			int_set(t_int_array *array, int position, int value);
void			int_push(t_int_array *array, int i);
int				int_pop(t_int_array *array);
int				int_index(t_int_array *array, int i);
int				int_remove(t_int_array *array, int index);
void			free_int_array(t_int_array *array);
t_int_array		*new_int_array(int capacity);
t_int_array		*copy_int_array(t_int_array *src);

#endif