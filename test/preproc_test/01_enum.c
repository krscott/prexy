#include "01_enum_prexy.h"
#include <assert.h>

#define X_DEF_ENUM_VARIANT(x) x,

#define def_enum(name)                                                         \
    enum name                                                                  \
    {                                                                          \
        name##_x_variants(X_DEF_ENUM_VARIANT)                                  \
    }

prexy enum foo {
    bar,
    baz = 10,
};

prexy enum Bool {
    // False
    False,
    // True
    True,
    // What is Truth?
    FileNotFound
};

enum prexy_not
{
    WAT,
};

#define manual_enum_x_variants(X)                                              \
    X(MANUAL_A)                                                                \
    X(MANUAL_B)

def_enum(manual_enum);

int main(void)
{
    static_assert(MANUAL_B == 1, "");
    static_assert(FileNotFound + 1 == prexy_count(Bool), "");
    return (int)MANUAL_A;
}
