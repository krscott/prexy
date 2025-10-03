// Repeatable Trait - no header guards

#ifndef PREXY_EXPAND
#include "ptl_compiler_extensions.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#endif

#include "prexy.h"

#ifndef ptl_slice
// For local LSP support
struct develop_slice
{
    int *ptr;
    size_t len;
};
#define ptl_slice develop_slice
#define PTL_SLICE_IMPLEMENTATION
#endif

#ifdef PTL_SLICE_IMPLEMENTATION
/******************
 * Implementation *
 ******************/
#endif

#undef ptl_slice
