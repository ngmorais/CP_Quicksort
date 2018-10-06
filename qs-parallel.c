#include "qs-parallel.h"
#include "pthread.h"
#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>
#define TYPE double

/*void qsort_parallel(void *base, size_t nel, size_t width, 
                    int (*compar)(const void *, const void *)){
*/
/* Do your own parallel (Cilk+) implementation of Quick Sort */
                        
//}

void swap(TYPE* a, TYPE* b)
{
    TYPE t = *a;
    *a = *b;
    *b = t;
}

int partition (TYPE* arr, int l, int h, int (*compar)(const void *, const void *))
{
    TYPE x = arr[h];
    int i = (l - 1);

    #pragma simd
    for (int j = l; j <= h- 1; j++)
    {
        if (compar(&arr[j],&x)<0)
        {
            i++;
            swap (&arr[i], &arr[j]);
        }
    }
    swap (&arr[i + 1], &arr[h]);
    return (i + 1);
}

void qsort_parallel_rec(TYPE* arr, int low, int high, int (*compar)(const void *, const void *))
{
    //CILK_C_REDUCER_OPADD(pi, int, 0);
    //CILK_C_REGISTER_REDUCER(pi);
    if (low < high)
    {

        int pi = partition(arr, low, high, compar);

        // Separately sort elements before
        // partition and after partition
        cilk_spawn qsort_parallel_rec(arr, low, pi - 1, compar);
        cilk_spawn qsort_parallel_rec(arr, pi + 1, high, compar);
	cilk_sync;
    }
}

void qsort_parallel(TYPE* arr, size_t nel, size_t width, int (*compar)(const void *, const void *))
{
    int low = 0;
    int high = nel-1;

    qsort_parallel_rec(arr, low, high, compar);
}
