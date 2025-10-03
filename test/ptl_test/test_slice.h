#ifndef TEST_SLICE_H_
#define TEST_SLICE_H_

#ifndef PREXY_EXPAND
#include <stddef.h>
#endif

#include "prexy.h"
#include "test_slice_prexy.h"

prexy struct str
{
    char *ptr;
    size_t len;
};
#define ptl_slice str
static int char_cmp(char a, char b) { return (int)a - (int)b; }
#define ptl_slice_cmp char_cmp
#include "ptl_slice.inc.h"

#endif
