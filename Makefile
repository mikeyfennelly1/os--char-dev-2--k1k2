obj-m += main.o

CC := gcc
CFLAGS := -Wall -Wextra
TARGET := program
KERNEL_BUILD_DIR := /lib/modules/$(shell uname -r)/build

BUILD_DIR := ./build
TEST_DIR := ./test

# variables for job module
JOB_SRC_DIR := ./src/job
JOB_SRCS := $(wildcard $(JOB_SRC_DIR)/*.c)
JOB_BUILD_DIR := ./build/job
JOB_OBJS := $(patsubst $(JOB_SRC_DIR)/%.c, $(JOB_BUILD_DIR)/%.o, $(JOB_SRCS))

JOB_TEST_SRCS := $(patsubst $(JOB_SRC_DIR)/%.c, $(TEST_DIR)/job/test_%.c, $(JOB_SRCS))

# Default rule
all: create_job_build_directory $(JOB_OBJS)
	@echo "---\n"
	@echo "JOB_SRCS: $(JOB_SRCS)"
	@echo "JOB_TEST_SRCS: $(JOB_TEST_SRCS)"
	@echo "JOB_OBJS: $(JOB_OBJS)"
	@echo "\n---"

# compile job rule
$(JOB_BUILD_DIR)/%.o: $(JOB_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# ensure ./build/job exists
create_job_build_directory: $(BUILD_DIR)
	@mkdir -p $(JOB_BUILD_DIR)

# ensure ./build exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)
