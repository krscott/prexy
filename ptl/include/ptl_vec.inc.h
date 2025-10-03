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

#ifndef ptl_vec
// For local LSP support
struct develop_vec
{
    int *ptr;
    size_t len;
    size_t cap;
};
#define ptl_vec develop_vec
#define develop_vec_PTRTYPE_ptr int
#define PTL_VEC_IMPLEMENTATION
// #define PTL_VEC_INFALLIBLE
#endif

#ifndef ptl_vec_realloc
#ifndef PREXY_EXPAND
#include <stdlib.h>
#endif
#define ptl_vec_realloc(vec, p, size) realloc(p, size)
#define ptl_vec_free(vec, p) free(p)
#endif

#ifdef PTL_VEC_INFALLIBLE
#define alloc_fn void
#else
#define alloc_fn nodiscard bool
#endif

void prexy_methodname(ptl_vec, deinit)(struct ptl_vec *vec);
alloc_fn prexy_methodname(ptl_vec, reserve)( //
    struct ptl_vec *vec,
    size_t const n
);
alloc_fn prexy_methodname(ptl_vec, append)(
    struct ptl_vec *vec,
    prexy_ptr_typeof(ptl_vec, ptr) const *arr,
    size_t const n
);
alloc_fn prexy_methodname(ptl_vec, push)(
    struct ptl_vec *vec, prexy_ptr_typeof(ptl_vec, ptr) elem
);
nodiscard bool prexy_methodname(ptl_vec, pop)(
    struct ptl_vec *vec, prexy_ptr_typeof(ptl_vec, ptr) * out
);

#ifdef PTL_VEC_IMPLEMENTATION

#ifndef GROW_NUMERATOR
#ifdef GROW_DENOMINATOR
#error "Define both GROW_NUMERATOR and GROW_DENOMINATOR"
#endif
#define GROW_NUMERATOR 3
#define GROW_DENOMINATOR 2
#endif

#define MIN_CAP 8
#define GROW_CAP(cap) ((cap) / GROW_DENOMINATOR * GROW_NUMERATOR)
#define CAP_LIMIT (SIZE_MAX / GROW_NUMERATOR * GROW_DENOMINATOR)

void prexy_methodname(ptl_vec, deinit)(struct ptl_vec *const vec)
{
    ptl_vec_free(vec, vec->ptr);
}

alloc_fn prexy_methodname(ptl_vec, reserve)( //
    struct ptl_vec *const vec,
    size_t const n
)
{
    assert(vec->ptr || (vec->len == 0 && vec->cap == 0));

    bool success;

    size_t const target_len = vec->len + n;

    if (target_len <= vec->cap)
    {
        success = true;
    }
    else if (vec->cap >= CAP_LIMIT)
    {
        success = false;
    }
    else
    {
        size_t new_cap = vec->cap < MIN_CAP ? MIN_CAP : GROW_CAP(vec->cap);
        while (new_cap < target_len)
        {
            new_cap = GROW_CAP(new_cap);
        }

        void *const new_ptr =
            ptl_vec_realloc(vec, vec->ptr, new_cap * sizeof(vec->ptr[0]));

        if (new_ptr)
        {
            success = true;
            vec->ptr = new_ptr;
            vec->cap = new_cap;
        }
        else
        {
            success = false;
        }
    }

#ifdef PTL_VEC_INFALLIBLE
    if (!success)
    {
        assert(success && "vec reserve failed");
        exit(1);
    }
#else
    return success;
#endif
}

alloc_fn prexy_methodname(ptl_vec, append)(
    struct ptl_vec *const vec,
    prexy_ptr_typeof(ptl_vec, ptr) const *const arr,
    size_t const n
)
{
#ifdef PTL_VEC_INFALLIBLE

    prexy_methodname(ptl_vec, reserve)(vec, n);
    memmove(&vec->ptr[vec->len], arr, sizeof(vec->ptr[0]) * n);
    vec->len += n;

#else

    bool const success = prexy_methodname(ptl_vec, reserve)(vec, n);

    if (success)
    {
        memmove(&vec->ptr[vec->len], arr, sizeof(vec->ptr[0]) * n);
        vec->len += n;
    }

    return success;

#endif
}

alloc_fn prexy_methodname(ptl_vec, push)(
    struct ptl_vec *const vec, prexy_ptr_typeof(ptl_vec, ptr) const elem
)
{
#ifdef PTL_VEC_INFALLIBLE
    prexy_methodname(ptl_vec, reserve)(vec, 1);
    vec->ptr[vec->len++] = elem;
#else
    bool const success = prexy_methodname(ptl_vec, reserve)(vec, 1);
    if (success)
    {
        vec->ptr[vec->len++] = elem;
    }
    return success;
#endif
}

nodiscard bool prexy_methodname(ptl_vec, pop)(
    struct ptl_vec *const vec, prexy_ptr_typeof(ptl_vec, ptr) *const out
)
{
    bool const success = vec->len > 0;
    if (success)
    {
        *out = vec->ptr[--vec->len];
    }
    return success;
}

#endif

#undef ptl_vec_free
#undef ptl_vec_realloc
#undef ptl_vec
