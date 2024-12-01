CC=tcc
CFLAGS=-I./src
DEPS=
 
PROGRAM := advent

BUILD_DIR := build
SRC_DIR := src

# SRCS := $(shell find $(SRC_DIR) -name *.с)
SRCS = ./src/day1.c
# SRCS := $(shell find $(SRC_DIR) -name *.с -exec basename {} \;)
# OBJS := $(patsubst %.scm,$(BUILD_DIR)/%.o,$(SRCS))
# OBJS := $(patsubst %.scm,$(BUILD_DIR)/%.o,$(SRCS))
OBJS := day1.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROGRAM): $(SRCS)
	@echo "Compile combined"
	mkdir -p $(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/$(PROGRAM) $(SRCS) 

# $(BUILD_DIR):
# 	@echo "[infra] create build directory"

# $(PROGRAM): $(OBJS)
# 	@echo "LD     $(PROGRAM)"
# 	@$(CC) $(CFLAGS) $(OBJS) -o $(BUILD_DIR)/$(PROGRAM)
# 	@echo ""

clean:
	@echo "RM     $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)


run: $(PROGRAM)
	./$(BUILD_DIR)/$(PROGRAM) 
