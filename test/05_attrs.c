#include "05_attrs_prexy.h"
#include "prexy_struct_fprintf.h"
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

prexy struct messages
{
    struct cstr buf[5];
};
static prexy_struct_fprint_repr_impl(messages);

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

    fprintf(stdout, "\n\n");

    struct messages msgs = {
        .buf =
            {
                make_cstr("never"),
                make_cstr("gonna"),
                make_cstr("give"),
                make_cstr("you"),
                make_cstr("up"),
            },
    };
    messages_fprint_repr(stdout, &msgs);
    return 0;
}
