@echo off
echo Compiling test-settings.c...
gcc -Wall -Wextra -std=c99 -o test-settings.exe test-settings.c
if %errorlevel% equ 0 (
    echo Compilation successful!
    echo Run: test-settings.exe
) else (
    echo Compilation failed!
    echo Make sure gcc is installed (MinGW/MSYS2)
)

