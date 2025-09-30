
#include <stdio.h>

#include "08_codegen.h"

int main(void)
{
    {
        char buf[80] = "Mutable string";
        struct str s = str_from_cstr(buf);

        char test;

        assert(!str_get(s, 80, &test));
        assert(!str_get(s, 15, &test));

        assert(str_get(s, 0, &test));
        assert(test == 'M');
        assert(str_get(s, 13, &test));
        assert(test == 'g');

        assert(str_set(&s, 0, 'F'));
        assert(buf[0] == 'F');
        assert(str_set(&s, 5, '!'));
        assert(buf[5] == '!');

        printf("%s\n", buf);
    }

    {
        struct strview sv = strview_from_cstr("Immutable string");

        char test;

        assert(!strview_get(sv, 80, &test));
        assert(!strview_get(sv, 16, &test));

        assert(strview_get(sv, 0, &test));
        assert(test == 'I');
        assert(strview_get(sv, 15, &test));
        assert(test == 'g');

        // strview_set() not defined

        printf("%s\n", sv.ptr);
    }

    {
        struct cstr cstr = {"Null-terminated string"};

        printf("cstr: ");
        cstr_fprint_repr(stdout, &cstr);
        printf("\n");
    }

    return 0;
}
