#include "libft.h"
#include "int_array.h"
#include <stdlib.h>

static int partition(int *array, size_t low, size_t high)
{
    int pivot;
    size_t i;
    size_t j;

    pivot = array[low];
    i = low;
    j = high;
    while (42)
    {
        while (array[i] < pivot)
            ++i;
        while (array[j] > pivot)
            --j;
        if (i >= j)
            return (j);
        ft_swap_int(&(array[i]), &(array[j]));
    }
}

static void quicksort(int *array, size_t low, size_t high)
{
    int pivot;

    if (low < high)
    {
        pivot = partition(array, low, high);
        quicksort(array, low, pivot - 1);
        quicksort(array, pivot + 1, high);
    }
}

void		sort_int_array(t_int_array *array)
{
    quicksort(array->data, 0, array->count - 1);
}