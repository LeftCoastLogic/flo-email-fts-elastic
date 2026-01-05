#!/bin/sh
# Simple compile script for Linux/macOS (no autotools needed)

echo "Compiling test-settings.c..."

# Try gcc
if command -v gcc >/dev/null 2>&1; then
    echo "Using gcc..."
    gcc -Wall -Wextra -std=c99 -o test-settings test-settings.c
    if [ $? -eq 0 ]; then
        echo ""
        echo "Compilation successful!"
        echo "Run: ./test-settings"
        exit 0
    fi
fi

# Try clang
if command -v clang >/dev/null 2>&1; then
    echo "Using clang..."
    clang -Wall -Wextra -std=c99 -o test-settings test-settings.c
    if [ $? -eq 0 ]; then
        echo ""
        echo "Compilation successful!"
        echo "Run: ./test-settings"
        exit 0
    fi
fi

echo ""
echo "ERROR: No C compiler found!"
echo "Please install gcc or clang"

exit 1

