#!/usr/bin/env sh
set -eu

cd "$(dirname "$(readlink -f -- "$0")")"

for dir in "src" "test"; do
    find "$dir" -type f -name '*.c' -exec clang-format -i {} +
    find "$dir" -type f -name '*.h' -exec clang-format -i {} +
done
