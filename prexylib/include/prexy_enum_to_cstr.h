#ifndef PREXY_ENUM_TO_CSTR_H_
#define PREXY_ENUM_TO_CSTR_H_

#include "prexy_core.h"
#include <assert.h>

#define PREXY_CASE_TO_CSTR(x)                                                  \
    case x:                                                                    \
        return #x;

prexy_tag(prexy_enum_to_cstr);

#define prexy_enum_to_cstr_decl(name)                                          \
    char const *name##_to_cstr(enum name const val)

#define prexy_enum_to_cstr_impl(name, FIELDS_X)                                \
    prexy_enum_to_cstr_decl(name)                                              \
    {                                                                          \
        switch (val)                                                           \
        {                                                                      \
            FIELDS_X(PREXY_CASE_TO_CSTR)                                       \
                                                                               \
        default:                                                               \
            assert(0 && "Invalid enum " #name " value");                       \
            return "?";                                                        \
        }                                                                      \
    }

#endif
