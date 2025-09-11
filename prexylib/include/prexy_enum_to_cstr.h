#ifndef PREXY_ENUM_TO_CSTR_H_
#define PREXY_ENUM_TO_CSTR_H_

#include <assert.h>

#define PREXY_CASE_TO_CSTR(x)                                                  \
    case x:                                                                    \
        return #x;
#define prexy_enum_to_cstr_decl(name)                                          \
    char const *name##_to_cstr(enum name const val)
#define prexy_enum_to_cstr_impl(name)                                          \
    prexy_enum_to_cstr_decl(name)                                              \
    {                                                                          \
        switch (val)                                                           \
        {                                                                      \
            name##_x_variants(PREXY_CASE_TO_CSTR)                              \
                                                                               \
                default : assert(0 && "Invalid enum " #name " value");         \
            return "?";                                                        \
        }                                                                      \
    }                                                                          \
    static_assert(1, "")

#endif
