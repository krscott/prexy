#!/usr/bin/env sh
set -eu

PROG="$1"
[ -e "$PROG" ]
OUT_DIR="$2"
[ -d "$OUT_DIR" ]

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
