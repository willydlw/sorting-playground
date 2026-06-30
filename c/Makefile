# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -I$(INC_DIR) -fsanitize=address

# Directory Structure
SRC_DIR = lib/src
INC_DIR = lib/include
OBJ_DIR = lib/obj
LIB_DIR = lib
TEST_DIR = tests
BENCH_DIR = benchmarks
BENCH_OBJ_DIR = $(BENCH_DIR)/obj

# Output Artifacts
LIB_TARGET = $(LIB_DIR)/libsorting.a
TEST_TARGET = $(TEST_DIR)/run_tests
BENCH_TARGET = $(BENCH_DIR)/run_benchmarks

# File Discovery
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)

# Benchmark Specific Files (Fixed 'wildcard' typo here)
BENCH_SRCS = $(wildcard $(BENCH_DIR)/*.c)
BENCH_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BENCH_OBJ_DIR)/%.o, $(SRCS))

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

# Run the cross-platform test script
test: all
	@echo "Running tests with AddressSanitizer diagnostic checks..."
	ASAN_OPTIONS=detect_leaks=1 ./$(TEST_TARGET)

# ===============================
# Benchmarking Infrastructure
# ===============================

# Rule to compile algorithm source files into separate benchmark object files
$(BENCH_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BENCH_OBJ_DIR)
	$(CC) $(CFLAGS) -DBENCHMARK -c $< -o $@

# Target to compile and build the Benchmark runner executable
$(BENCH_TARGET): $(BENCH_OBJS) $(BENCH_SRCS)
	@mkdir -p $(BENCH_DIR)
	$(CC) $(CFLAGS) -DBENCHMARK $(BENCH_SRCS) $(BENCH_OBJS) -o $@

# Target to compile and immediately execute the benchmarks
bench: $(BENCH_TARGET)
	@echo "Running operation-counting benchmarks..."
	./$(BENCH_TARGET)

# Clean up all build artifacts, object files, and test binaries
clean:
	rm -rf $(OBJ_DIR) $(BENCH_OBJ_DIR) $(LIB_TARGET) $(TEST_TARGET) $(BENCH_TARGET)

.PHONY: all clean test bench
