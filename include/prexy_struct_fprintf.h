#ifndef PREXY_STRUCT_FPRINTF_H_
#define PREXY_STRUCT_FPRINTF_H_

#include <assert.h>
#include <stdio.h>

// Get printf format string for a type.
// Does *not* assume a `char *` is a `%s`.
#define PREXY_UTIL_SIMPLE_TYPE_FORMAT(x)                                       \
    (_Generic(                                                                 \
        (x),                                                                   \
         _Bool: "%d",                                                          \
         short: "%hd",                                                         \
         unsigned short: "%hu",                                                \
         int: "%d",                                                            \
         unsigned int: "%u",                                                   \
         long: "%ld",                                                          \
         unsigned long: "%lu",                                                 \
         long long: "%lld",                                                    \
         unsigned long long: "%llu",                                           \
         float: "%f",                                                          \
         double: "%f",                                                         \
         char: "'%c'",                                                         \
         void *: "%p"                                                          \
    ))

#define PREXY_STRUCT_FPRINT_REPR_simple(type, varname)                         \
    {                                                                          \
        fprintf(stream, "." #varname " = ");                                   \
        fprintf(                                                               \
            stream,                                                            \
            PREXY_UTIL_SIMPLE_TYPE_FORMAT((x)->varname),                       \
            (x)->varname                                                       \
        );                                                                     \
        fprintf(stream, ", ");                                                 \
    }

#define PREXY_STRUCT_FPRINT_REPR_simple_array(type, varname, len)              \
    {                                                                          \
        fprintf(stream, "." #varname " = { ");                                 \
        for (int i = 0; i < len; ++i)                                          \
        {                                                                      \
            fprintf(                                                           \
                stream,                                                        \
                PREXY_UTIL_SIMPLE_TYPE_FORMAT((x)->varname[i]),                \
                (x)->varname[i]                                                \
            );                                                                 \
            fprintf(stream, ", ");                                             \
        }                                                                      \
        fprintf(stream, "}, ");                                                \
    }

#define PREXY_STRUCT_FPRINT_REPR_struct(type, varname)                         \
    {                                                                          \
        fprintf(stream, "." #varname " = ");                                   \
        type##_fprint_repr(stream, &(x)->varname);                             \
        fprintf(stream, ", ");                                                 \
    }

#define PREXY_STRUCT_FPRINT_REPR_struct_array(type, varname, len)              \
    {                                                                          \
        fprintf(stream, "." #varname " = { ");                                 \
        for (int i = 0; i < len; ++i)                                          \
        {                                                                      \
            type##_fprint_repr(stream, &(x)->varname[i]);                      \
            fprintf(stream, ", ");                                             \
        }                                                                      \
        fprintf(stream, "}, ");                                                \
    }

#define PREXY_STRUCT_FPRINT_REPR_enum(type, varname)                           \
    {                                                                          \
        fprintf(stream, "." #varname " = ");                                   \
        fprintf(stream, "%s", type##_to_cstr((x)->varname));                   \
        fprintf(stream, ", ");                                                 \
    }

#define PREXY_STRUCT_FPRINT_REPR_enum_array(type, varname, len)                \
    {                                                                          \
        fprintf(stream, "." #varname " = { ");                                 \
        for (int i = 0; i < len; ++i)                                          \
        {                                                                      \
            fprintf(stream, "%s, ", type##_to_cstr((x)->varname[i]));          \
        }                                                                      \
        fprintf(stream, "}, ");                                                \
    }

#define PREXY_STRUCT_FPRINT_REPR(fkind, ...)                                   \
    PREXY_STRUCT_FPRINT_REPR_##fkind(__VA_ARGS__)

#define prexy_struct_fprint_repr_decl(name)                                    \
    void name##_fprint_repr(FILE *stream, struct name const *x)
#define prexy_struct_fprint_repr_impl_x(name, FIELDS_X)                        \
    prexy_struct_fprint_repr_decl(name)                                        \
    {                                                                          \
        fprintf(stream, "(struct " #name "){ ");                               \
        FIELDS_X(PREXY_STRUCT_FPRINT_REPR)                                     \
        fprintf(stream, "}");                                                  \
    }                                                                          \
    static_assert(1, "")
#define prexy_struct_fprint_repr_impl(name)                                    \
    prexy_struct_fprint_repr_impl_x(name, name##_x_fields)
#define prexy_struct_fprint_repr_impl_attr(name, attr)                         \
    prexy_struct_fprint_repr_impl_x(name, name##_x_fields_##attr);             \
    static_assert(sizeof(*(struct attr *)0), "")

#endif
