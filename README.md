

# PlusPlusLexer

A lexical analyzer for the Plus++ programming language.

## Project Structure

```
PlusPlusLexer/
├── Makefile          # Build script for Linux/Unix
├── build_windows.bat # Build script for Windows
├── src/              # Source code
│   ├── lexer.c       # Lexical analyzer implementation
│   ├── lexer.h       # Token definitions and function declarations
│   ├── main.c        # Program entry point
│   └── utils.c       # Utility functions
├── bin/              # Compiled executable
├── obj/              # Object files
├── outputs/          # Output files from tests
└── tests/            # Test files
    ├── simple.plus   # Simple test program
    ├── programs.plus # More complex test program
    └── invalid.plus  # Test program with invalid constructs
```

## Building and Running on Linux/Unix

### Prerequisites

- GCC compiler
- Make

### Build Instructions

1. Navigate to the PlusPlusLexer directory
```
cd PlusPlusLexer
```

2. Build the project
```
make
```

3. Run tests
```
make test         # Run on simple.plus
make test-invalid # Run on invalid.plus
make test-all     # Run all tests
```

### Running the Lexer

```
./bin/la tests/your_file
```

This will create a `.lx` file with the tokenized output.

## Building and Running on Windows

### Prerequisites

- GCC compiler for Windows (MinGW, TDM-GCC, or Windows Subsystem for Linux)

### Option 1: Using the batch file (CMD)

1. Navigate to the PlusPlusLexer directory
```
cd PlusPlusLexer
```

2. Build the project
```
build_windows.bat
```

3. Run tests
```
build_windows.bat test         # Run on simple.plus
build_windows.bat test-invalid # Run on invalid.plus
```

### Option 2: Using MinGW with Make

If you have MinGW installed with the make utility:

1. Navigate to the PlusPlusLexer directory
```
cd PlusPlusLexer
```

2. Build the project
```
mingw32-make
```

3. Run tests
```
mingw32-make test
mingw32-make test-invalid
```

### Option 3: Using Windows Subsystem for Linux (WSL)

1. Install WSL and a Linux distribution
2. Navigate to the project directory in WSL
3. Follow the Linux/Unix build instructions

### Running the Lexer

```
bin\la.exe tests\your_file
```

This will create a `.lx` file with the tokenized output.
# plusplus-
