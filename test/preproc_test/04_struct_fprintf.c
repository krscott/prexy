#include "04_struct_fprintf_prexy.h"
#include "prexy.h"
#include "prexy_enum_to_cstr.h"
#include "prexy_struct_fprintf.h"
#include <stdbool.h>
#include <stdio.h>

prexy enum cheese_kind {
    CHEDDAR,
    SWISS,
    BRIE,
};
static prexy_impl(cheese_kind, prexy_enum_to_cstr);

prexy struct cheese
{
    enum cheese_kind kind;
    bool is_melty;
};
static prexy_impl(cheese, prexy_struct_fprint_repr);

prexy struct bagel
{
    char name[10];
    double price;
    struct cheese cheeses[3];
};
static prexy_impl(bagel, prexy_struct_fprint_repr);

int main(void)
{
    struct bagel bagel = {
        .name = "everything",
        .price = 1.99,
        .cheeses =
            {
                {.kind = CHEDDAR, .is_melty = true},
                {.kind = SWISS, .is_melty = false},
                {.kind = BRIE, .is_melty = false},
            },
    };

    bagel_fprint_repr(stdout, &bagel);
}
