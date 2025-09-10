#ifndef PREXY_CORE_H_
#define PREXY_CORE_H_

#include <assert.h>

#define PREXY_ENUM_VARIANTS(x) x,

#define prexy_enum(name)                                                       \
    enum name                                                                  \
    {                                                                          \
        name##_x_variants(PREXY_ENUM_VARIANTS)                                 \
    }

#define PREXY_STRUCT_FIELD_simple(type, varname) type varname
#define PREXY_STRUCT_FIELD_simple_attr(type, varname, ...) type varname
#define PREXY_STRUCT_FIELD_simple_array(type, varname, len) type varname[len]
#define PREXY_STRUCT_FIELD_struct(type, varname) struct type varname
#define PREXY_STRUCT_FIELD_struct_array(type, varname, len)                    \
    struct type varname[len]
#define PREXY_STRUCT_FIELD_enum(type, varname) enum type varname
#define PREXY_STRUCT_FIELD_enum_array(type, varname, len) enum type varname[len]

#define PREXY_STRUCT_FIELD(fkind, ...) PREXY_STRUCT_FIELD_##fkind(__VA_ARGS__);

#define prexy_struct(name)                                                     \
    struct name                                                                \
    {                                                                          \
        name##_x_fields(PREXY_STRUCT_FIELD)                                    \
    }

// Pre-processor marker macro

#define prexy
#define prexy_tag typedef int
#define px_tag(name) static_assert(sizeof(name), "")
#define px_attr(name, ...) static_assert(sizeof((struct name){__VA_ARGS__}), "")

#endif
