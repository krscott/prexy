#include "prexy.h"
#include <stdio.h>

prexy enum error {
    // Ok
    OK = 0,
    // bad
    ERR,
};

enum prexy_not
{
    FOO,
};

int main(void)
{
    printf("Hello, World!\n");
    return (int)OK;
}
