#ifndef PREXY_CORE_H_
#define PREXY_CORE_H_

#include <assert.h>

// Manual enum constructor

#define PREXY_ENUM_VARIANTS(x) x,

#define prexy_enum(name)                                                       \
    enum name                                                                  \
    {                                                                          \
        name##_x_variants(PREXY_ENUM_VARIANTS)                                 \
    }

// Manual struct constructor

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
#define prexy_tag(name)                                                        \
    struct name                                                                \
    {                                                                          \
        char prexy_tag__;                                                      \
    }

#define PREXY_ASSERT_IS_TAG(name)                                              \
    static_assert(sizeof(((struct name *)0)->prexy_tag__), "")

#define px_tag(name) static_assert(sizeof((struct name){'\0'}), "")
#define px_attr(name, ...) static_assert(sizeof((struct name){__VA_ARGS__}), "")

// Struct function decl/impl macros

#define PREXY_SELECT(macro_name, fkind, ...) macro_name##_##fkind(__VA_ARGS__)

#define prexy_decl(macro_name, name)                                           \
    macro_name##_decl(name);                                                   \
    PREXY_ASSERT_IS_TAG(macro_name)

// clang-format off
// NOTE: _impl macros do not end with semicolon

#define prexy_enum_impl(macro_name, name)                                      \
    macro_name##_impl(name, name##_x_variants)                                 \
    PREXY_ASSERT_IS_TAG(macro_name)

#define prexy_impl(macro_name, name)                                           \
    macro_name##_impl(name, name##_x_fields)                                   \
    PREXY_ASSERT_IS_TAG(macro_name)

#define prexy_impl_attr(macro_name, name, attr)                                \
    macro_name##_impl(name, name##_x_fields_##attr)                            \
    static_assert(sizeof(*(struct attr *)0), "")

#define prexy_impl_tag(macro_name, name, tag)                                  \
    macro_name##_impl(name, name##_x_fields_##tag)                             \
    PREXY_ASSERT_IS_TAG(tag)

// clang-format on

#endif
