#ifndef PREXY_TEMPLATE_H_
#define PREXY_TEMPLATE_H_

// Field implementations

#define PREXY_FN_simple(type, varname)                                         \
    {                                                                          \
        (x)->varname;                                                          \
    }

#define PREXY_FN_simple_array(type, varname, len)                              \
    {                                                                          \
        for (int i = 0; i < len; ++i)                                          \
        {                                                                      \
            (x)->varname[i];                                                   \
        }                                                                      \
    }

#define PREXY_FN_struct(type, varname)                                         \
    {                                                                          \
        (x)->varname;                                                          \
    }

#define PREXY_FN_struct_array(type, varname, len)                              \
    {                                                                          \
        for (int i = 0; i < len; ++i)                                          \
        {                                                                      \
            (x)->varname[i];                                                   \
        }                                                                      \
    }

#define PREXY_FN_enum(type, varname)                                           \
    {                                                                          \
        (x)->varname;                                                          \
    }

#define PREXY_FN_enum_array(type, varname, len)                                \
    {                                                                          \
        for (int i = 0; i < len; ++i)                                          \
        {                                                                      \
            (x)->varname[i];                                                   \
        }                                                                      \
    }

// Field selector
#define PREXY_FN_FIELD_SELECT(fkind, ...) PREXY_FN_##fkind(__VA_ARGS__)

// Function prototype
#define prexy_fn_decl(name) void name##_fn(FILE *stream, struct name const *x)

// Implement with explicit XMacro
#define prexy_fn_impl(name, FIELDS_X)                                          \
    prexy_fn_decl(name) { FIELDS_X(PREXY_FN_FIELD_SELECT) }                    \
    static_assert(1, "")

#endif
