CC=tcc
CFLAGS=-I./src
TESTDIR=tests
DEPS=
BUILD_DIR := build
SRC_DIR=src
TESTS_DIR=testc
LINTER=clang-tidy-16
FORMATTER=clang-format-16
 
PROGRAM := advent

SRCS := $(shell find $(SRC_DIR) -name *.c -exec basename {} \;)
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

build/%.o: src/%.c
	@echo "Creating object: $@"
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROGRAM): $(OBJS)
	@echo "Making executable"
	@echo $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) -o build/advent $(OBJS) $(CFLAGS)
	@rm $(BUILD_DIR)/*.o

test: test/%.c
	@$(CC) $(CFLAGS) -lcunit -o $(BIN_DIR)/$(NAME)_test $(TESTS_DIR)/*.c
	@$(BIN_DIR)/$(NAME)_test

lint:
	@echo "Linting..."
	@$(LINTER) $(SRC_DIR)/*  -- $(CFLAGS)

format:
	@echo "Formatting..."
	@$(FORMATTER) --style=Google -i $(SRC_DIR)/*

.PHONY: clean

clean:
	@echo "Cleaning directory: $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)/*.o

run: $(PROGRAM)
	./$(BUILD_DIR)/$(PROGRAM) 
