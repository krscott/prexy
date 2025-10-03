#ifndef TEST_VEC_SLICE_H_
#define TEST_VEC_SLICE_H_

#ifndef PREXY_EXPAND
#include <stddef.h>
#endif

#include "prexy.h"
#include "test_vec_slice_prexy.h"

prexy struct intvec
{
    int *ptr;
    size_t len;
    size_t cap;
};
#define ptl_vec intvec
#include "ptl_vec.inc.h"

prexy struct intslice
{
    int *ptr;
    size_t len;
};
#define ptl_vec intvec
#define ptl_slice intslice
#include "ptl_vec_slice.inc.h"

prexy struct intview
{
    int const *ptr;
    size_t len;
};
#define ptl_vec intvec
#define ptl_slice intview
#include "ptl_vec_slice.inc.h"

#endif
