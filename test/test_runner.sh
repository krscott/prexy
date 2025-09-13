#!/usr/bin/env sh
set -eu

OUT_DIR="$(dirname "$(readlink -f -- "$0")")/$2"
[ -d "$OUT_DIR" ]

PROG="$1"
ACTUAL_STDOUT="$PROG.stdout"
EXPECTED_STDOUT="$OUT_DIR/$PROG.stdout"

./"$PROG" >"$ACTUAL_STDOUT"

if [ -f "$EXPECTED_STDOUT" ]; then
    diff "$EXPECTED_STDOUT" "$ACTUAL_STDOUT"
else
    echo "No expected output for '$PROG'- creating $EXPECTED_STDOUT"
    mv "$ACTUAL_STDOUT" "$EXPECTED_STDOUT"
    exit 1
fi
