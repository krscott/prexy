#ifndef TEST_VEC_H_
#define TEST_VEC_H_

#ifndef PREXY_EXPAND
#include <stddef.h>
#endif

#include "prexy.h"
#include "test_vec_prexy.h"

prexy struct intvec
{
    int *ptr;
    size_t len;
    size_t cap;
};
prexy struct intslice
{
    int *ptr;
    size_t len;
};
prexy struct intview
{
    int const *ptr;
    size_t len;
};
#define ptl_vec intvec
#define ptl_vec_slice intslice
#define ptl_vec_view intview
#include "ptl_vec.inc.h"

#endif
