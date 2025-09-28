#include "07_trait_prexy.h"
#include "prexy.h"
#include "prexy_define_struct.h"

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
