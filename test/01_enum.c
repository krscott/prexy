#include "01_enum_prexy.h"
#include "prexy.h"

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

#define manual_x_variants(X)                                                   \
    X(MANUAL_A)                                                                \
    X(MANUAL_B)

prexy_enum(manual);

int main(void)
{
    static_assert(MANUAL_B == 1, "");
    static_assert(FileNotFound + 1 == Bool_x_count, "");
    return (int)MANUAL_A;
}
