CC = gcc
LDFLAGS = -lm

# Set the level of logs to show (3 = INFO, 2 = WARN, 1 = ERROR, 0 = NONE)
LOG_LEVEL ?= 2

CUSTOM_FLAGS = -DLOG_LEVEL=$(LOG_LEVEL)
CFLAGS = -Wall -Wextra -O3 -Iinclude $(CUSTOM_FLAGS)

CORE_DIR = core
BIN_DIR = bin
TEST_DIR = test
LOGIC_TEST_DIR = logic
PERFORMANCE_TEST_DIR = performance
CORE_OBJ = $(BIN_DIR)/vector.o
CORE_SRC = $(CORE_DIR)/vector.c

LOGIC_TEST_SOURCES = $(wildcard $(TEST_DIR)/$(LOGIC_TEST_DIR)/*.c)
PERFORMANCE_TEST_SOURCES = $(wildcard $(TEST_DIR)/$(PERFORMANCE_TEST_DIR)/*.c)

# Get the list of the executables in bin/ from test files
LOGIC_TEST_EXES = $(patsubst $(TEST_DIR)/$(LOGIC_TEST_DIR)/%.c, $(BIN_DIR)/%, $(LOGIC_TEST_SOURCES))
PERFORMANCE_TEST_EXES = $(patsubst $(TEST_DIR)/$(PERFORMANCE_TEST_DIR)/%.c, $(BIN_DIR)/%, $(PERFORMANCE_TEST_SOURCES))

all: prepare $(CORE_OBJ) $(LOGIC_TEST_EXES) $(PERFORMANCE_TEST_EXES)

prepare:
	@mkdir -p $(BIN_DIR)

# CORE files compilation
$(CORE_OBJ): $(CORE_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Test files compilation
$(BIN_DIR)/%: $(TEST_DIR)/$(LOGIC_TEST_DIR)/%.c $(CORE_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Performance files compilation
$(BIN_DIR)/%: $(TEST_DIR)/$(PERFORMANCE_TEST_DIR)/%.c $(CORE_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Run tests
run-tests:
	@echo ">>> EXECUTING AUTOMATIC TESTS <<<"
	@for exe in $(LOGIC_TEST_EXES); do \
		./$$exe || exit 1; \
	done
	@echo "\n--- END OF AUTOMATIC TEST ---"

run-performance:
	@echo "\n>>> EXECUTING PERFORMANCE ANALYSIS <<<"
	@for exe in $(PERFORMANCE_TEST_EXES); do \
		./$$exe; \
	done
	@echo "\n--- END OF PERFORMANCE ANALYSIS ---"

# Run tests and perfomances
check: all run-tests run-performance
	@echo "\n>>> G.O.M. CHECK ENDED <<<"

clean:
	rm -rf $(BIN_DIR)

.PHONY: all prepare clean check