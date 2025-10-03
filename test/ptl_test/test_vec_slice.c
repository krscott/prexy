#ifndef PREXY_EXPAND
#include "ptl_util.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#endif

#define PTL_VEC_IMPLEMENTATION
#define PTL_VEC_SLICE_IMPLEMENTATION
#include "test_vec_slice.h"

static void test_vec_as_slice(void)
{
    struct intvec vec = {0};

    for (int i = 0; i < 100; ++i)
    {
        bool const ok = intvec_push(&vec, i + 100);
        assert(ok);
    }

    struct intslice slice = intvec_as_intslice(&vec);
    assert(slice.len == vec.len);
    for (int i = 0; i < 100; ++i)
    {
        assert(slice.ptr[i] == i + 100);
        slice.ptr[i] += 100;
    }

    for (int i = 0; i < 100; ++i)
    {
        assert(vec.ptr[i] == i + 200);
    }

    intvec_deinit(&vec);
}

static void test_vec_as_slice_const_ptr(void)
{
    struct intvec vec = {0};

    for (int i = 0; i < 100; ++i)
    {
        bool const ok = intvec_push(&vec, i + 100);
        assert(ok);
    }

    struct intview view = intvec_as_intview(&vec);
    assert(view.len == vec.len);
    for (int i = 0; i < 100; ++i)
    {
        assert(view.ptr[i] == i + 100);
    }

    intvec_deinit(&vec);
}

int main(void)
{
    test_vec_as_slice();
    test_vec_as_slice_const_ptr();
    return 0;
}
