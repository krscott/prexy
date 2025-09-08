#ifndef PREXY_H_
#define PREXY_H_

#include <assert.h>

#define PREXY_ENUM_VARIANTS(x) x,

#define prexy_enum(name)                                                       \
    enum name                                                                  \
    {                                                                          \
        name##_x_variants(PREXY_ENUM_VARIANTS)                                 \
    }

// Markers
#define prexy

#endif
