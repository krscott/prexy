#include "03_enum_to_cstr_prexy.h"
#include "prexy_enum_to_cstr.h"
#include <assert.h>
#include <string.h>

prexy enum tst3 {
    FOO,
    BAR,
    BAZ,
};
static prexy_enum_impl(tst3, prexy_enum_to_cstr);

int main(void)
{
    assert(0 == strcmp("FOO", tst3_to_cstr(FOO)));
    assert(0 == strcmp("BAR", tst3_to_cstr(BAR)));
    assert(0 == strcmp("BAZ", tst3_to_cstr(BAZ)));
    return 0;
}
