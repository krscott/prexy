
#include "prexy.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#ifndef collection
// Default for IDE convenience
#include "07_trait_prexy.h"
#define collection str
struct str
{
    char *ptr;
    size_t len;
};
#endif

static inline struct collection prexy_methodname(collection, from_cstr)( //
    prexy_typeof(collection, ptr) cstr
)
{
    assert(cstr);
    return (struct collection){
        .ptr = cstr,
        .len = strlen(cstr),
    };
}

static inline bool prexy_methodname(collection, get)(
    struct collection self, size_t i, prexy_ptr_typeof(collection, ptr) * out
)
{
    bool const ok = i < self.len;

    if (ok)
    {
        assert(self.ptr);
        *out = self.ptr[i];
    }

    return ok;
}

#if prexy_is_mut_ptr(collection, ptr)

static inline bool prexy_methodname(collection, set)(
    struct collection *self, size_t i, prexy_ptr_typeof(collection, ptr) value
)
{
    bool const ok = i < self->len;

    if (ok)
    {
        assert(self->ptr);
        self->ptr[i] = value;
    }

    return ok;
}

#endif

#undef collection
