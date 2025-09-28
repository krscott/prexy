#!/usr/bin/env -S awk -f
BEGIN {
    level = 0
}

level > 0 && /^#if/ { level += 1 }
level > 0 && /^#endif/ { level -= 1 }

level > 0 { print }

/^#ifndef PREXY_EXPAND$/ { level = 1 }


