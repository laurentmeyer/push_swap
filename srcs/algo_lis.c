#include "push_swap.h"
#include "int_array.h"

// int         swappable_increasing(t_int_array *array, int start)
// {
//     int i;

//     i = start;
//     if (i >= array->count - 2)
//         return (1);
//     while ((array->data)[i] <= (array->data)[i + 1] && i < array->count - 2)
//         ++i;
//     if (i == (array->count - 1))
//         return (1);
//     if ((array->data)[i + 1] > (array->data)[i + 2])
//         return (0);
//     return (swappable_increasing(array, i + 2));
// }

static int get_new_l(t_int_array *array, t_int_array *m, int l, int i)
{
    int lo;
    int hi;
    int mid;

    lo = 1;
    hi = l;
    while (lo <= hi)
    {
        mid = (lo + hi) / 2;
        if ((array->data)[(m->data)[mid]] < (array->data)[i])
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return (lo);
}

static int sub_lis(t_int_array *array, t_int_array *m, t_int_array *p)
{
    int         l;
    int         newl;
    int         i;

    l = 0;
    i = 0;
    while (i < array->count)
    {
        newl = get_new_l(array, m, l, i);
        int_set(p, i, (m->data)[newl - 1]);
        int_set(m, newl, i);
        if (newl > l)
            l = newl;
        ++i;
    }
    return (l);
}

t_int_array *lis(t_int_array *array)
{
    t_int_array *res;
    t_int_array *m;
    t_int_array *p;
    int         l;
    int         k;

    if (NULL == (res = new_int_array(array->count + 1))
        || NULL == (m = new_int_array(array->count + 1))
        || NULL == (p = new_int_array(array->count)))
        return (NULL);
    int_set(m, 0, 0);
    if (0 == (l = sub_lis(array, m, p)))
        return (NULL);
    k = (m->data)[l];
    while (l > 0)
    {
        int_set(res, l - 1, (array->data)[k]);
        k = (p->data)[k];
        --l;
    }
    free_int_array(m);
    free_int_array(p);
    return (res);
}

int	algo_lis(t_stacks *stacks)
{
    static int          busy = 0;
    static t_int_array  *longest;
    int                 top;
    int                 index;
    
	if (is_sorted(stacks->a))
        return (1);
    if (!busy)
    {
        if (NULL == (longest = lis(&(stacks->a))))
            exit_message(0, "couldn't do lis\n");
        busy = 1;
    }
    else
    {
        if (longest->count > 0)
        {
            top = (stacks->a.data)[stacks->a.count - 1];
            if ((index = int_index(longest, top)) >= 0)
            {
                do_op(stacks, "pb");
                int_remove(longest, index);
            }
            else
                do_op(stacks, "ra");
        }
        else
        {
            busy = 0;
            free_int_array(longest);
        }
    }
    return (0);
}