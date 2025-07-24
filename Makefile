# Makefile for PlusPlusLexer

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -D_POSIX_C_SOURCE=200809L

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
EXECUTABLE = $(BIN_DIR)/la

# Default target
all: directories $(EXECUTABLE)

# Create directories
directories:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Compile the executable
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run lexer on test files
test: $(EXECUTABLE)
	@echo "Running lexer on programs.plus..."
	./$(EXECUTABLE) tests/simple > outputs/output.txt

# Run lexer on invalid test file and capture errors
test-invalid: $(EXECUTABLE)
	@echo "Running lexer on invalid.plus..."
	./$(EXECUTABLE) tests/invalid 2> outputs/error_output.txt || true
	@echo "Error output written to outputs/error_output.txt"

# Run both valid and invalid tests
test-all: test test-invalid
	@echo "All tests completed."

# Clean up compiled files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Help message
help:
	@echo "Makefile for PlusPlusLexer"
	@echo "Targets:"
	@echo "  all          - Build the lexer"
	@echo "  test         - Run the lexer on programs.plus"
	@echo "  test-invalid - Run the lexer on invalid.plus and capture errors"
	@echo "  test-all     - Run both valid and invalid tests"
	@echo "  clean        - Remove object files and executable"
	@echo "  help         - Display this help message"

.PHONY: all directories test test-invalid test-all clean help
