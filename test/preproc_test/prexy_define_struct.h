#ifndef PREXY_DEFINE_STRUCT_H_
#define PREXY_DEFINE_STRUCT_H_

#include "prexy.h"

#define PREXY_DEFINE_STRUCT_simple(type, varname) type varname
#define PREXY_DEFINE_STRUCT_simple_array(type, varname, len) type varname[len]
#define PREXY_DEFINE_STRUCT_struct(type, varname) struct type varname
#define PREXY_DEFINE_STRUCT_struct_array(type, varname, len)                   \
    struct type varname[len]
#define PREXY_DEFINE_STRUCT_enum(type, varname) enum type varname
#define PREXY_DEFINE_STRUCT_enum_array(type, varname, len)                     \
    enum type varname[len]

#define PREXY_DEFINE_STRUCT_SELECT(fkind, ...)                                 \
    PREXY_DEFINE_STRUCT_##fkind(__VA_ARGS__);

#define prexy_define_struct(name)                                              \
    struct name                                                                \
    {                                                                          \
        PREXY_CONCAT(name, _X)(PREXY_DEFINE_STRUCT_SELECT)                     \
    }

#endif
