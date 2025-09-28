#!/usr/bin/env -S awk -f
BEGIN {
    level = 0
}

level > 0 && /^#if/ { level += 1 }
level > 0 && /^#endif/ { level -= 1 }

/^#ifndef PREXY_EXPAND$/ { level = 1 }

level == 0 && match($0, /^#include "(.*)"/, m) { print m[1] }


