stage1() {
    awk -f stage1/prexy.awk "$@"
}

cfg() {
    echo "PREXY=$PREXY"

    (
        set -eu

        rm -rf build/
        cmake -B build
    )
}

bld() {
    (
        set -eu

        if [ ! -d build ]; then
            cfg
        fi

        cmake --build build

        if [ "$CMAKE_BUILD_TYPE" = "Debug" ]; then
            mkdir -p .compile-db
            cp build/compile_commands.json .compile-db
        fi
    )
}

run() {
    (
        set -eu

        bld
        ./build/src/prexy "$@"
    )
}

crun() {
    (
        set -eu

        cfg
        run "$@"
    )
}

tst() {
    (
        set -eu

        cfg
        bld

        (
            cd build/test/preproc_test
            ctest --output-on-failure
        )
        (
            cd build/test/ptl_test
            ctest --output-on-failure
        )
    )
}

release() {
    unset DISABLE_OPTIMZATIONS
    unset CMAKE_BUILD_TYPE
}

debug() {
    release
    export CMAKE_BUILD_TYPE=Debug
}

o0() {
    debug
    export DISABLE_OPTIMIZATIONS=1
}

setup_vscode() {
    mkdir -p .vscode/
    cp dev/vscode/* .vscode/
}

format() {
    for dir in "src" "test" "include" "ptl"; do
        find "$dir" -type f -name '*.c' -exec clang-format -i {} +
        find "$dir" -type f -name '*.h' -exec clang-format -i {} +
    done
}

# Check "$1" is not a file because direnv will pass a profile when sourced
if [ $# -gt 0 ] && [ ! -e "$1" ]; then
    "$@"
    exit $?
fi

PREXY=$(realpath stage1/prexy)
export PREXY

export CC=clang
debug
