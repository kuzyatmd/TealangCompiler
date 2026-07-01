#!/bin/bash
#: source ./environment.sh

export TEALANG_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"


#: Basic debug run
tea() {
    BINARY="./build/debug/bin/tea"
    PARAMS=$(cat "params")

    if [ ! -f "$BINARY" ]; then
        echo "$BINARY not found. "
        exit 1
    fi

    "${TEALANG_ROOT}/build/debug/bin/tea" "$PARAMS" "$@"
}

tea-rebuild() {
    rm -rf build/
    cmake --preset debug-clang
    cmake --build --preset debug-clang
}

echo "Environment set. Commands: tea, tea-rebuild"