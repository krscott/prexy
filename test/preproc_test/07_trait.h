#include "07_trait_prexy.h"
#include "prexy.h"
#include "prexy_define_struct.h"
#include "prexy_struct_fprintf.h"

#ifndef PREXY_EXPAND
#include <stddef.h>
#endif

prexy struct str
{
    char *ptr;
    size_t len;
};
#define collection str
#include "07_collection.inc.h"

prexy struct strview
{
    char const *ptr;
    size_t len;
};
#define collection strview
#include "07_collection.inc.h"

prexy struct cstr
{
    px_tag(prexy_repr_cstr);
    char const *ptr;
};
static prexy_impl_tag(cstr, prexy_struct_fprint_repr, prexy_repr_cstr);
