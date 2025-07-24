@echo off
REM Windows build script for PlusPlusLexer
REM This script assumes that GCC is installed and available in PATH
REM You can install MinGW or TDM-GCC for Windows

REM Create directories if they don't exist
if not exist obj mkdir obj
if not exist bin mkdir bin
if not exist outputs mkdir outputs

REM Compile source files into object files
echo Compiling source files...
gcc -Wall -Wextra -std=c99 -g -c src\lexer.c -o obj\lexer.o
gcc -Wall -Wextra -std=c99 -g -c src\main.c -o obj\main.o
gcc -Wall -Wextra -std=c99 -g -c src\utils.c -o obj\utils.o

REM Link object files into executable
echo Linking executable...
gcc -Wall -Wextra -std=c99 -g -o bin\la.exe obj\lexer.o obj\main.o obj\utils.o

REM Check if build succeeded
if %ERRORLEVEL% EQU 0 (
    echo Build completed successfully.
    echo Executable is located at bin\la.exe
) else (
    echo Build failed with error code %ERRORLEVEL%.
    exit /b %ERRORLEVEL%
)

REM Run tests if requested
if "%1"=="test" (
    echo Running test on simple.plus...
    bin\la.exe tests\simple > outputs\output.txt
    echo Output written to outputs\output.txt
)

if "%1"=="test-invalid" (
    echo Running test on invalid.plus...
    bin\la.exe tests\invalid > outputs\error_output.txt 2>&1
    echo Error output written to outputs\error_output.txt
)

echo Done.
