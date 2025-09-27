#include "02_struct_prexy.h"
#include <assert.h>

#define X_DEF_STRUCT_FIELD_simple(type, varname) type varname
// #define X_DEF_STRUCT_FIELD_simple_attr(type, varname, ...) type varname
#define X_DEF_STRUCT_FIELD_simple_array(type, varname, len) type varname[len]
#define X_DEF_STRUCT_FIELD_struct(type, varname) struct type varname
#define X_DEF_STRUCT_FIELD_struct_array(type, varname, len)                    \
    struct type varname[len]
#define X_DEF_STRUCT_FIELD_enum(type, varname) enum type varname
#define X_DEF_STRUCT_FIELD_enum_array(type, varname, len) enum type varname[len]

#define X_DEF_STRUCT_FIELD(fkind, ...) X_DEF_STRUCT_FIELD_##fkind(__VA_ARGS__);

#define def_struct(name)                                                       \
    struct name                                                                \
    {                                                                          \
        name##_x_fields(X_DEF_STRUCT_FIELD)                                    \
    }

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
    struct simples *simple_ref;
};

#define manual_struct_x_fields(F)                                              \
    F(simple, float, f)                                                        \
    F(simple_array, char, str, 10)                                             \
    F(enum, nums, n)                                                           \
    F(enum_array, nums, nn, 2)                                                 \
    F(struct, simples, some)                                                   \
    F(struct_array, nested, others, 3)
def_struct(manual_struct);

int main(void)
{
    //
    return 0;
}
