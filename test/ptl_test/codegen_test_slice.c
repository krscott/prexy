#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct str
{
    char *ptr;
    size_t len;
};
static int char_cmp(char a, char b) { return (int)a - (int)b; }
void str_sort(struct str slice);
static int str__qsort_cmp_(void const *a, void const *b)
{
    return char_cmp(*(char const *)a, *(char const *)b);
}
void str_sort(struct str slice)
{
    qsort(slice.ptr, slice.len, sizeof(slice.ptr[0]), str__qsort_cmp_);
}
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
