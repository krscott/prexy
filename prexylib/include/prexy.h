#ifndef PREXY_H_
#define PREXY_H_

#include <assert.h>

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

#define prexy_decl(name, macro_name)                                           \
    macro_name##_decl(name);                                                   \
    PREXY_ASSERT_IS_TAG(macro_name)

// clang-format off
// NOTE: _impl macros do not end with semicolon

#define prexy_enum_impl(name, macro_name)                                      \
    macro_name##_impl(name, name##_x_variants)                                 \
    PREXY_ASSERT_IS_TAG(macro_name)

#define prexy_impl(name, macro_name)                                           \
    macro_name##_impl(name, name##_x_fields)                                   \
    PREXY_ASSERT_IS_TAG(macro_name)

#define prexy_impl_attr(name, macro_name, attr)                                \
    macro_name##_impl(name, name##_x_fields_##attr)                            \
    static_assert(sizeof(*(struct attr *)0), "")

#define prexy_impl_tag(name, macro_name, tag)                                  \
    macro_name##_impl(name, name##_x_fields_##tag)                             \
    PREXY_ASSERT_IS_TAG(tag)

// clang-format on

#endif
