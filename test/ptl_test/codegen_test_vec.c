#include "ptl_compiler_extensions.h"
#include "ptl_util.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct intvec
{
    int *ptr;
    size_t len;
    size_t cap;
};
void intvec_deinit(struct intvec *vec);
nodiscard bool intvec_reserve(struct intvec *vec, size_t const n);
nodiscard bool
intvec_append(struct intvec *vec, int const *arr, size_t const n);
nodiscard bool intvec_push(struct intvec *vec, int elem);
nodiscard bool intvec_pop(struct intvec *vec, int *out);
void intvec_deinit(struct intvec *const vec) { free(vec->ptr); }
nodiscard bool intvec_reserve(struct intvec *const vec, size_t const n)
{
    assert(vec->ptr || (vec->len == 0 && vec->cap == 0));
    bool success;
    size_t const target_len = vec->len + n;
    if (target_len <= vec->cap)
    {
        success = true;
    }
    else if (vec->cap >= (SIZE_MAX / 3 * 2))
    {
        success = false;
    }
    else
    {
        size_t new_cap = vec->cap < 8 ? 8 : ((vec->cap) / 2 * 3);
        while (new_cap < target_len)
        {
            new_cap = ((new_cap) / 2 * 3);
        }
        void *const new_ptr = realloc(vec->ptr, new_cap * sizeof(vec->ptr[0]));
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
    return success;
}
nodiscard bool
intvec_append(struct intvec *const vec, int const *const arr, size_t const n)
{
    bool const success = intvec_reserve(vec, n);
    if (success)
    {
        memmove(&vec->ptr[vec->len], arr, sizeof(vec->ptr[0]) * n);
        vec->len += n;
    }
    return success;
}
nodiscard bool intvec_push(struct intvec *const vec, int const elem)
{
    bool const success = intvec_reserve(vec, 1);
    if (success)
    {
        vec->ptr[vec->len++] = elem;
    }
    return success;
}
nodiscard bool intvec_pop(struct intvec *const vec, int *const out)
{
    bool const success = vec->len > 0;
    if (success)
    {
        *out = vec->ptr[--vec->len];
    }
    return success;
}

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
int main(void)
{
    test_intvec_push();
    test_intvec_pop();
    test_intvec_append();
    test_intvec_realloc();
    return 0;
}
