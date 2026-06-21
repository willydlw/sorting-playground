# Compiler and Flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -pedantic -std=c99 -I$(INC_DIR)

# Directory Structure
SRC_DIR   = lib/src
INC_DIR   = lib/include
OBJ_DIR   = lib/obj
LIB_DIR   = lib
TEST_DIR  = tests

# Output Artifacts
LIB_TARGET  = $(LIB_DIR)/libsorting.a
TEST_TARGET = $(TEST_DIR)/run_tests

# File Discovery
SRCS      = $(wildcard $(SRC_DIR)/*.c)
OBJS      = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)

# Default Target: Builds library and then builds tests
all: $(LIB_TARGET) $(TEST_TARGET)

# Rule to create the Static Library archive (libsorting.a)
$(LIB_TARGET): $(OBJS)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

# Rule to compile algorithm source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile and link the Test Runner executable
$(TEST_TARGET): $(TEST_SRCS) $(LIB_TARGET)
	$(CC) $(CFLAGS) $(TEST_SRCS) -L$(LIB_DIR) -lsorting -o $@

# Clean up all build artifacts, object files, and test binaries
clean:
	rm -rf $(OBJ_DIR) $(LIB_TARGET) $(TEST_TARGET)

.PHONY: all clean
