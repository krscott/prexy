#include "prexy.h"

prexy enum error {
    // Ok
    OK = 0,
    // bad
    ERR,
};

enum prexy_not
{
    FOO,
};

#define manual_x_variants(X)                                                   \
    X(MANUAL_A)                                                                \
    X(MANUAL_B)

prexy_enum(manual);

int main(void)
{
    static_assert(MANUAL_B == 1, "");
    return (int)MANUAL_A;
}
