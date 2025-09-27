#ifndef X_FN_H_
#define X_FN_H_

// Field implementations

#define X_FN_simple(type, varname)                                             \
    {                                                                          \
        (x)->varname;                                                          \
    }

#define X_FN_simple_array(type, varname, len)                                  \
    {                                                                          \
        for (int i = 0; i < len; ++i)                                          \
        {                                                                      \
            (x)->varname[i];                                                   \
        }                                                                      \
    }

#define X_FN_struct(type, varname)                                             \
    {                                                                          \
        (x)->varname;                                                          \
    }

#define X_FN_struct_array(type, varname, len)                                  \
    {                                                                          \
        for (int i = 0; i < len; ++i)                                          \
        {                                                                      \
            (x)->varname[i];                                                   \
        }                                                                      \
    }

#define X_FN_enum(type, varname)                                               \
    {                                                                          \
        (x)->varname;                                                          \
    }

#define X_FN_enum_array(type, varname, len)                                    \
    {                                                                          \
        for (int i = 0; i < len; ++i)                                          \
        {                                                                      \
            (x)->varname[i];                                                   \
        }                                                                      \
    }

// Field selector
#define X_FN_FIELD_SELECT(fkind, ...) X_FN_##fkind(__VA_ARGS__)

// Function prototype
#define fn_decl(name) void name##_fn(FILE *stream, struct name const *x)

// Implement with explicit XMacro
#define fn_impl(name, FIELDS_X)                                                \
    fn_decl(name) { FIELDS_X(X_FN_FIELD_SELECT) }                              \
    static_assert(1, "")

#endif
