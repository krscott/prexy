#include "04_struct_fprintf_prexy.h"
#include "prexy.h"
#include "prexy_struct_fprintf.h"
#include <stdbool.h>
#include <stdio.h>

prexy enum cheese_kind {
    CHEDDAR,
    SWISS,
    BRIE,
};
static prexy_enum_to_cstr_impl(cheese_kind);

prexy struct cheese
{
    enum cheese_kind kind;
    bool is_melty;
};
static prexy_struct_fprint_repr_impl(cheese);

prexy struct bagel
{
    char name[10];
    double price;
    struct cheese cheeses[3];
};
static prexy_struct_fprint_repr_impl(bagel);

int main(void)
{
    struct bagel bagel = {
        .name = "everything",
        .price = 5.99,
        .cheeses =
            {
                {.kind = CHEDDAR, .is_melty = true},
                {.kind = SWISS, .is_melty = false},
                {.kind = BRIE, .is_melty = false},
            },
    };

    bagel_fprint_repr(stderr, &bagel);
}
