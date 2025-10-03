#define PTL_SLICE_IMPLEMENTATION
#include "test_slice.h"

#ifndef PREXY_EXPAND
#include <stdio.h>
#include <string.h>
#endif

static void test_sort(void)
{
    char a_[] = "dgcebfa";

    struct str a = (struct str){.ptr = a_, .len = strlen(a_)};

    str_sort(a);

    printf("%s\n", a_);
    assert(0 == strcmp(a_, "abcdefg"));
}

int main(void)
{
    test_sort();
    return 0;
}
