#ifndef QS_PARALLEL_H
#define QS_PARALLEL_H

#include <stdlib.h>

void qsort_parallel(void *base, size_t nel, size_t width, 
                    int (*compar)(const void *, const void *));
         
#endif /* QS_PARALLEL_H */