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
#define ptl_vec intvec
#include "ptl_vec.inc.h"

#endif
