#!/usr/bin/env bash
set -euo pipefail
shopt -s failglob

PREXY="$(realpath "$PREXY")"
PREXYLIB="../../prexylib"

cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")"

usage() {
    # NOTE: Don't forget to update OPTIONS/LONGOPTS below!
    cat <<EOF
Usage: $(basename "$0") [options]

Options:
    -h, --help          Display this help message.
    -v, --verbose       Enable debug messages
EOF
}

# NOTE: Use ':' suffix to specify opt has an arg
OPTIONS="hv"
LONGOPTS="help,verbose"

if ! PARSED=$(getopt --options="$OPTIONS" --longoptions="$LONGOPTS" --name "$0" -- "$@"); then
    usage
    exit 2
fi

eval set -- "$PARSED"

verbose=

while true; do
    opt="$1"
    shift

    # NOTE: shift again if taking an arg

    case "$opt" in
    -h | --help)
        usage
        exit 0
        ;;
    -v | --verbose)
        verbose=1
        ;;
    --)
        break
        ;;
    *)
        echo "Unknown option: $1"
        usage
        exit 2
        ;;
    esac
done

debug() {
    if [[ -n $verbose ]]; then
        echo "$@" >&2
    fi
}

verbose() {
    if [[ -n $verbose ]]; then
        set -x
    fi
}

test_dir="../build/test"

rm -rf "$test_dir"
mkdir -p "$test_dir"
cp ./*.c "$test_dir"

for file in *.c; do
    (
        test_name="${file%.c}"
        bin="$test_dir/$test_name"

        echo "Test: $test_name"

        verbose

        $PREXY "$file" | clang-format >"${test_name}_prexy.h"
        $CC -Wall -Wextra -pedantic -Werror -I"$PREXYLIB/include" "$file" -o "$bin"
        ./"$bin" >"$file.stdout"
    )
done

git diff --exit-code -- *.h *.stdout

echo ""
echo "Tests passed"
