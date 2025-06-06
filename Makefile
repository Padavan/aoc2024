CC=clang-16
LINTER=clang-tidy-16
FORMATTER=clang-format-16
# -pedantic

BUILD_DIR := build
BIN_DIR := bin
TESTS_DIR := tests
BUILD_TEST_DIR := build
SRC_DIR := src
INCLUDE_DIR := include
TESTS_DIR=tests

CFLAGS=-g -O0 -Wall -Wextra -I./$(INCLUDE_DIR)

PROGRAM := advent
TEST_PROGRAM := test

SRCS := $(shell find $(SRC_DIR) -name *.c -not -name "advent.c" -exec basename {} \;)
TSTS := $(shell find $(TESTS_DIR) -name *.c -exec basename {} \;)

EXE_OBJS = $(BUILD_DIR)/advent.o
EXE_FILES = $(SRC_DIR)/advent.c
SHARED_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
SHARED_FILES = $(patsubst %.c,$(SRC_DIR)/%.o,$(SRCS))
TEST_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(TSTS))
TEST_FILES = $(patsubst %.c,$(TESTS_DIR)/%.o,$(TSTS))

### TARGETS ###

all: init build/$(PROGRAM)

build/%_test.o: tests/%_test.c
	$(CC) -c -o $@ $< $(CFLAGS)

build/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)


build/$(PROGRAM): $(EXE_OBJS) $(SHARED_OBJS)
	@echo "Making executable"
	$(CC) $(CFLAGS) -o $@ $^

build/test: init $(SHARED_OBJS) $(TEST_OBJS)
	@$(CC) $(CFLAGS) $(SHARED_OBJS) $(TEST_OBJS) -lcheck -pthread -lrt -lm -lsubunit -o $(BUILD_DIR)/test

lint:
	@echo "Linting..."
	@$(LINTER) $(SRC_DIR)/*  -- $(CFLAGS)

format:
	@echo "Formatting..."
	@$(FORMATTER) --style=Webkit -i $(SRC_DIR)/*

init:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)


clean:
	@echo "Cleaning directory: $(BUILD_DIR) $(BIN_DIR)"
	@rm -rf $(BUILD_DIR) $(BIN_DIR) $(BUILD_TEST_DIR)

run: init build/$(PROGRAM)
	./$(BUILD_DIR)/$(PROGRAM)

test: build/$(TEST_PROGRAM)
	./$(BUILD_TEST_DIR)/$(TEST_PROGRAM)

memcheck: init build/$(PROGRAM)
	valgrind --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./build/$(PROGRAM)

.PHONY: clean lint format test memcheck init all
