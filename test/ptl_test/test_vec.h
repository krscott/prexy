#include "ptl_compiler_extensions.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct intvec
{
    int *ptr;
    size_t len;
    size_t cap;
};
void intvec_deinit(struct intvec *vec);
nodiscard bool intvec_reserve(struct intvec *const vec, size_t const n);
nodiscard bool
intvec_append(struct intvec *const vec, int const *arr, size_t const n);
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
intvec_append(struct intvec *const vec, int const *arr, size_t const n)
{
    bool const success = intvec_reserve(vec, n);
    if (success)
    {
        memmove(&vec->ptr[vec->len], arr, n);
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
