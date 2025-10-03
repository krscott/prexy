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

struct intslice
{
    int *ptr;
    size_t len;
};
nodiscard struct intslice intvec_as_intslice(struct intvec const *vec);
nodiscard struct intslice intvec_as_intslice(struct intvec const *vec)
{
    return (struct intslice){
        .ptr = vec->ptr,
        .len = vec->len,
    };
}

struct intview
{
    int const *ptr;
    size_t len;
};
nodiscard struct intview intvec_as_intview(struct intvec const *vec);
nodiscard struct intview intvec_as_intview(struct intvec const *vec)
{
    return (struct intview){
        .ptr = vec->ptr,
        .len = vec->len,
    };
}

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
static void test_vec_as_view(void)
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
    test_vec_as_view();
    return 0;
}
