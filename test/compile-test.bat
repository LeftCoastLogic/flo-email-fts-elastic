@echo off
REM Simple compile script for Windows (no autotools needed)
REM Requires: gcc (MinGW/MSYS2)
REM Note: Run this in Command Prompt (cmd.exe), not PowerShell

echo Compiling test-settings.c...

if exist test-settings.exe del test-settings.exe

REM Try gcc
gcc -Wall -Wextra -std=c99 -o test-settings.exe test-settings.c
if %errorlevel% neq 0 (
    echo.
    echo ERROR: Compilation failed!
    echo gcc not found. Please install:
    echo   - MinGW/MSYS2: https://www.msys2.org/
    echo   - Or use WSL: wsl --install
    echo.
    echo Then run: gcc -Wall -Wextra -std=c99 -o test-settings.exe test-settings.c
    exit /b 1
)

echo.
echo Compilation successful!
echo Run: test-settings.exe
exit /b 0

