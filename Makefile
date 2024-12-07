CC=tcc
CFLAGS=-I./src
TESTDIR=tests
DEPS=
BUILD_DIR := build
SRC_DIR := src
LINTER := clang-tidy-16
FORMATTER := clang-format-16
 
PROGRAM := advent

# SRCS := $(shell find $(SRC_DIR) -name *.с)
# SRCS = ./src/advent.c
# SRCS := $(shell find $(SRC_DIR) -name *.с -exec basename {} \;)
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
# OBJS := $(patsubst %.scm,$(BUILD_DIR)/%.o,$(SRCS))
# OBJS := day1.o
# OBJS = /src/helpers.o

OBJS = build/day1.o build/day2.o build/day3.o build/day4.o build/day5.o build/day6.o build/utils.o build/matrix_utils.o build/advent.o
# SRCS = 

# %.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

build/%.o: src/%.c
	@echo "Build objects"
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROGRAM): $(OBJS)
	@echo "Compile combined"
	@echo $(OBJS)
	mkdir -p $(BUILD_DIR)
# 	$(CC) -o $(BUILD_DIR)/$(PROGRAM) $(SRCS) 
	$(CC) -o build/advent $(OBJS) $(CFLAGS)
	@rm $(BUILD_DIR)/*.o

# $(BUILD_DIR):
# 	@echo "[infra] create build directory"

# $(PROGRAM): $(OBJS)
# 	@echo "LD     $(PROGRAM)"
# 	@$(CC) $(CFLAGS) $(OBJS) -o $(BUILD_DIR)/$(PROGRAM)
# 	@echo ""

lint:
# 	@$(LINTER) --config-file=.clang-tidy $(SRC_DIR)/*  -- $(CFLAGS)
	@$(LINTER) $(SRC_DIR)/*  -- $(CFLAGS)

format:
# 	@$(FORMATTER) -style=file -i $(SRC_DIR)/*
	@$(FORMATTER) --style=WebKit -i $(SRC_DIR)/*
	
.PHONY: clean

clean:
	@echo "RM     $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)/*.o


run: $(PROGRAM)
	./$(BUILD_DIR)/$(PROGRAM) 
