# Kernel build system
KERNEL_SRC := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -g -I./src
LDFLAGS := -lrt -lpthread  # Adjust as needed

# Directories
SRC_DIR := src

# Object files
KERNEL_OBJS := $(KERNEL_SOURCES:.c=.o)

# Test sources
TESTS := $(JOB_DIR)/test_file_usage.c
TEST_OBJS := $(TESTS:.c=.o)
JOB_OBJ := $(JOB_DIR)/job.o

# Default target
all: module tests

# pattern rule for source to object compilation
%.o: %.c build_dir
	$(CC) $(CFLAGS) -c $< -o ./build/$(notdir $@)

build_dir:
	mkdir -p $(PWD)/build

# Clean build files
clean:
	@$(MAKE) -C $(KERNEL_SRC) M=$(PWD) clean
	@rm -f $(KERNEL_OBJS) $(TEST_OBJS) $(TESTS:.c=)
