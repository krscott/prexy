#include "05_tag_prexy.h"
#include "prexy_struct_fprintf.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define PREXY_STRUCT_FPRINT_REPR_format_as_str(type, varname)                  \
    {                                                                          \
        fprintf(stream, "." #varname " = \"%s\", ", (x)->varname);             \
    }

prexy_tag(format_as_str);

prexy struct cstr
{
    px_tag(format_as_str);
    char const *buf;

    size_t len;
};
static prexy_impl_tag(cstr, prexy_struct_fprint_repr, format_as_str);

prexy struct messages
{
    struct cstr buf[5];
};
static prexy_impl(messages, prexy_struct_fprint_repr);

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
                make_cstr("quack"),
                make_cstr("like"),
                make_cstr("a"),
                make_cstr("duck"),
            },
    };
    messages_fprint_repr(stdout, &msgs);
    return 0;
}
