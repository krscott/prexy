#include "test_vec.h"
#include "ptl_util.h"
#include <assert.h>
#include <string.h>

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

static void test_intvec_pushpop(void)
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

int main(void)
{
    test_intvec_push();
    test_intvec_pushpop();
    return 0;
}
