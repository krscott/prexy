// Repeatable Trait - no header guards

#ifndef PREXY_EXPAND
#include <stddef.h>
#include <stdlib.h>
#endif

#include "prexy.h"

#ifndef ptl_slice
// For local LSP support
struct develop_slice
{
    int *ptr;
    size_t len;
};
#define ptl_slice develop_slice
#define develop_slice_PTRTYPE_ptr int

static int int_compare(int a, int b) { return a - b; }
#define ptl_slice_cmp int_compare

#define PTL_SLICE_IMPLEMENTATION
#endif

#ifdef ptl_slice_cmp
void prexy_methodname(ptl_slice, sort)(struct ptl_slice slice);
#endif

#ifdef PTL_SLICE_IMPLEMENTATION
/******************
 * Implementation *
 ******************/

#ifdef ptl_slice_cmp
static int prexy_methodname(ptl_slice, _qsort_cmp_)( //
    void const *a,
    void const *b
)
{
    return ptl_slice_cmp(
        *(prexy_ptr_typeof(ptl_slice, ptr) const *)a,
        *(prexy_ptr_typeof(ptl_slice, ptr) const *)b
    );
}

void prexy_methodname(ptl_slice, sort)(struct ptl_slice slice)
{
    qsort(
        slice.ptr,
        slice.len,
        sizeof(slice.ptr[0]),
        prexy_methodname(ptl_slice, _qsort_cmp_)
    );
}
#endif

#endif

#ifdef ptl_slice_cmp
#undef ptl_slice_cmp
#endif
#undef ptl_slice
