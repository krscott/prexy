#ifndef PREXY_EXPAND
#include "ptl_util.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#endif

#define PTL_VEC_IMPLEMENTATION
#include "test_vec.h"

static void test_intvec_push(void)
{
    struct intvec vec = {0};
    bool ok;

    ok = intvec_push(&vec, 111);
    assert(ok);
    assert(vec.ptr[0] == 111);

    ok = intvec_push(&vec, 222);
    assert(ok);
    assert(vec.ptr[1] == 222);

    ok = intvec_push(&vec, 333);
    assert(ok);
    assert(vec.ptr[2] == 333);

    int expected[] = {111, 222, 333};
    assert(vec.len == ptl_countof(expected));
    assert(vec.cap >= ptl_countof(expected));
    assert(0 == memcmp(vec.ptr, expected, sizeof(expected)));

    intvec_deinit(&vec);
}

static void test_intvec_pop(void)
{
    struct intvec vec = {0};
    bool ok;
    int elem = 0;

    ok = intvec_push(&vec, 4);
    assert(ok);
    ok = intvec_push(&vec, 5);
    assert(ok);
    ok = intvec_push(&vec, 6);
    assert(ok);
    assert(vec.len == 3);

    ok = intvec_pop(&vec, &elem);
    assert(ok);
    assert(elem == 6);
    assert(vec.len == 2);
    ok = intvec_pop(&vec, &elem);
    assert(ok);
    assert(elem == 5);
    assert(vec.len == 1);

    ok = intvec_push(&vec, 7);
    assert(ok);
    assert(vec.len == 2);

    int expected[] = {4, 7};
    assert(vec.len == ptl_countof(expected));
    assert(vec.cap >= ptl_countof(expected));
    assert(0 == memcmp(vec.ptr, expected, sizeof(expected)));

    ok = intvec_pop(&vec, &elem);
    assert(ok);
    assert(elem == 7);
    assert(vec.len == 1);
    ok = intvec_pop(&vec, &elem);
    assert(ok);
    assert(elem == 4);
    assert(vec.len == 0);
    ok = intvec_pop(&vec, &elem);
    assert(!ok);
    assert(vec.len == 0);

    intvec_deinit(&vec);
}

static void test_intvec_append(void)
{
    struct intvec vec = {0};
    bool ok;

    {
        int arr1[] = {997, 998, 999};

        ok = intvec_append(&vec, arr1, ptl_countof(arr1));
        assert(ok);
        assert(vec.len == ptl_countof(arr1));
        assert(vec.cap >= ptl_countof(arr1));
        assert(0 == memcmp(vec.ptr, arr1, sizeof(arr1)));
    }

    {
        int arr2[] = {1000, 1001, 1002};
        int expected[] = {997, 998, 999, 1000, 1001, 1002};

        ok = intvec_append(&vec, arr2, ptl_countof(arr2));
        assert(ok);
        assert(vec.len == ptl_countof(expected));
        assert(vec.cap >= ptl_countof(expected));
        assert(0 == memcmp(vec.ptr, expected, sizeof(expected)));
    }

    intvec_deinit(&vec);
}

static void test_intvec_realloc(void)
{
    struct intvec vec = {0};

    int const SIZE = 10000;

    int i = 0;
    for (; i < SIZE; ++i)
    {
        bool const ok = intvec_push(&vec, i);
        assert(ok);
    }
    assert(vec.len == SIZE);
    for (; i > 0; --i)
    {
        int x = -1;
        bool const ok = intvec_pop(&vec, &x);
        assert(ok);
        assert(x == i - 1);
    }
    assert(vec.len == 0);

    intvec_deinit(&vec);
}

static void test_vec_as_slice(void)
{
    struct intvec vec = {0};

    for (int i = 0; i < 100; ++i)
    {
        bool const ok = intvec_push(&vec, i + 100);
        assert(ok);
    }

    struct intslice slice = intvec_as_slice(&vec);
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

static void test_vec_as_view(void)
{
    struct intvec vec = {0};

    for (int i = 0; i < 100; ++i)
    {
        bool const ok = intvec_push(&vec, i + 100);
        assert(ok);
    }

    struct intview view = intvec_as_view(&vec);
    assert(view.len == vec.len);
    for (int i = 0; i < 100; ++i)
    {
        assert(view.ptr[i] == i + 100);
    }

    intvec_deinit(&vec);
}

int main(void)
{
    test_intvec_push();
    test_intvec_pop();
    test_intvec_append();
    test_intvec_realloc();
    test_vec_as_slice();
    test_vec_as_view();
    return 0;
}
