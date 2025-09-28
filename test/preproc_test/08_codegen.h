#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

struct str
{
    char *ptr;
    size_t len;
};
static inline struct str str_from_cstr(char *cstr)
{
    assert(cstr);
    return (struct str){
        .ptr = cstr,
        .len = strlen(cstr),
    };
}
static inline bool str_get(struct str self, size_t i, char *out)
{
    bool const ok = i < self.len;
    if (ok)
    {
        assert(self.ptr);
        *out = self.ptr[i];
    }
    return ok;
}
static inline bool str_set(struct str *self, size_t i, char value)
{
    bool const ok = i < self->len;
    if (ok)
    {
        assert(self->ptr);
        self->ptr[i] = value;
    }
    return ok;
}

struct strview
{
    char const *ptr;
    size_t len;
};
static inline struct strview strview_from_cstr(char const *cstr)
{
    assert(cstr);
    return (struct strview){
        .ptr = cstr,
        .len = strlen(cstr),
    };
}
static inline bool strview_get(struct strview self, size_t i, char *out)
{
    bool const ok = i < self.len;
    if (ok)
    {
        assert(self.ptr);
        *out = self.ptr[i];
    }
    return ok;
}
