CC = gcc
PYTHON = python

LDFLAGS = -lm

# Set the level of logs to show (3 = INFO, 2 = WARN, 1 = ERROR, 0 = NONE)
LOG_LEVEL ?= 2

CUSTOM_FLAGS = -DLOG_LEVEL=$(LOG_LEVEL)

# Get all the subdirectories in include
INC_DIRS = $(shell find include -type d)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

CFLAGS = -Wall -Wextra -O3 $(INC_FLAGS) $(CUSTOM_FLAGS)

# Automatic generation of errors
ERROR_CSV = error_codes.csv
ERROR_H = include/common/error.h
GEN_SCRIPT = scripts/make_errors.py

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

all: prepare $(ERROR_H) $(CORE_OBJ) $(LOGIC_TEST_EXES) $(PERFORMANCE_TEST_EXES)

prepare:
	@mkdir -p $(BIN_DIR)
	@mkdir -p include/common

# Error header creation
$(ERROR_H): $(ERROR_CSV) $(GEN_SCRIPT)
	@echo ">>> GENERATING ERROR HEADER FROM CSV <<<"
	$(PYTHON) $(GEN_SCRIPT)

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