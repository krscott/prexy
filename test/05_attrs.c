#include "05_attrs_prexy.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define PREXY_STRUCT_FPRINT_REPR_strattr(type, varname, ...)                   \
    {                                                                          \
        fprintf(stream, "." #varname " = \"%s\", ", (x)->varname);             \
    }

struct strattr
{
    bool is_cstr;
};

prexy struct cstr
{
    px_attr(strattr, .is_cstr = true);
    char const *buf;

    size_t len;
};
static prexy_struct_fprint_repr_impl_attr(cstr, strattr);

static struct cstr make_cstr(char const *s)
{
    return (struct cstr){
        .buf = s,
        .len = strlen(s),
    };
}

int main(void)
{
    struct cstr s = make_cstr("Hello, World!");

    cstr_fprint_repr(stdout, &s);
    return 0;
}
