// Repeatable Trait - no header guards

#ifndef PREXY_EXPAND
#include "ptl_compiler_extensions.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#endif

#include "prexy.h"

#if !defined(ptl_vec) && !defined(ptl_slice)
// For local LSP support
struct develop_vec
{
    int *ptr;
    size_t len;
    size_t cap;
};
#define ptl_vec develop_vec
#define develop_vec_PTRTYPE_ptr int

struct develop_slice
{
    int *ptr;
    size_t len;
};
#define ptl_slice develop_slice
#define PTL_VEC_SLICE_IMPLEMENTATION
#endif

nodiscard struct ptl_slice
    prexy_methodname3(ptl_vec, as, ptl_slice)(struct ptl_vec const *vec);

#ifdef PTL_VEC_SLICE_IMPLEMENTATION
/******************
 * Implementation *
 ******************/

nodiscard struct ptl_slice prexy_methodname3(ptl_vec, as, ptl_slice)( //
    struct ptl_vec const *vec
)
{
    return (struct ptl_slice){
        .ptr = vec->ptr,
        .len = vec->len,
    };
}

#endif

#undef ptl_slice
#undef ptl_vec
