obj-m += main.o

CC := gcc
CFLAGS := -Wall -Wextra
TARGET := program
KERNEL_BUILD_DIR := /lib/modules/$(shell uname -r)/build

BUILD_DIR := ./build
TEST_BUILD_DIR := ./build/tests  # Directory for test binaries
JOB_SRC_DIR := ./src/job
JOB_SRCS := $(wildcard $(JOB_SRC_DIR)/*.c)
JOB_BUILD_DIR := ./build/job
JOB_OBJS := $(patsubst $(JOB_SRC_DIR)/%.c, $(JOB_BUILD_DIR)/%.o, $(JOB_SRCS))

JOB_TEST_SRC_DIR := ./test/job
JOB_TEST_SRCS := $(wildcard $(JOB_TEST_SRC_DIR)/*.c)
JOB_TEST_OBJS := $(patsubst $(JOB_TEST_SRC_DIR)/%.c, $(TEST_BUILD_DIR)/%.o, $(TEST_SRCS))
TEST_BINARIES := $(patsubst $(JOB_TEST_SRC_DIR)/%.c, $(TEST_BUILD_DIR)/%, $(TEST_SRCS))

JOB_BUILD_OBJECTS := $(JOB_BUILD_DIR)/%.o

# Default rule
all: create_job_build_directory create_test_build_directory build_test_srcs_to_test_objs $(JOB_OBJS) $(TEST_BINARIES)
	@echo "---\n"
	@echo "JOB_SRCS: $(JOB_SRCS)"
	@echo "JOB_OBJS: $(JOB_OBJS)"
	@echo "TEST_SRCS: $(TEST_SRCS)"
	@echo "TEST_BINARIES: $(TEST_BINARIES)"
	@echo "\n---"

# compile job.o rule
$(JOB_BUILD_DIR)/%.o: $(JOB_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# pattern rule for object file creation from source
$(TEST_BUILD_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# link test binaries with job.o
$(TEST_BUILD_DIR)/%: $(TEST_BUILD_DIR)/%.o $(JOB_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# ensure ./build/job exists
create_job_build_directory:
	@mkdir -p $(JOB_BUILD_DIR)

# ensure ./build/tests exists
create_test_build_directory:
	@mkdir -p $(TEST_BUILD_DIR)

# clean rule
clean:
	@rm -rf $(BUILD_DIR)
