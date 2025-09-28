#ifndef PREXY_ENUM_TO_CSTR_H_
#define PREXY_ENUM_TO_CSTR_H_

#include "prexy.h"
#include <assert.h>

#define PREXY_ENUM_TO_CSTR_CASE(x)                                             \
    case x:                                                                    \
        return #x;

prexy_namespace(prexy_enum_to_cstr);

#define prexy_enum_to_cstr_decl(name)                                          \
    char const *name##_to_cstr(enum name const val)

#define prexy_enum_to_cstr_impl(name, VARIANTS_X)                              \
    prexy_enum_to_cstr_decl(name)                                              \
    {                                                                          \
        switch (val)                                                           \
        {                                                                      \
            VARIANTS_X(PREXY_ENUM_TO_CSTR_CASE)                                \
                                                                               \
        default:                                                               \
            assert(0 && "Invalid enum " #name " value");                       \
            return "?";                                                        \
        }                                                                      \
    }

#endif
