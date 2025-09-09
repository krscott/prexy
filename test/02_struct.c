#include "02_struct_prexy.h"
#include "prexy.h"
#include <assert.h>

prexy struct simples
{
    // Comments
    int i;
    // things
    char const *str;
};

prexy struct arrays
{
    int arr[5];
    char const *strings[80];
};

prexy enum nums {
    ONE,
    TWO,
};
static_assert(nums_x_count == 2, "");

prexy struct enums
{
    enum nums a_num;
    enum nums nums[3];
};

prexy struct nested
{
    struct simples head;
    struct simples tail[11];
};

#define manual_struct_x_fields(F)                                              \
    F(simple, float, f)                                                        \
    F(simple_array, char, str, 10)                                             \
    F(enum, nums, n)                                                           \
    F(enum_array, nums, nn, 2)                                                 \
    F(struct, simples, some)                                                   \
    F(struct_array, nested, others, 3)
prexy_struct(manual_struct);

int main(void)
{
    //
    return 0;
}
