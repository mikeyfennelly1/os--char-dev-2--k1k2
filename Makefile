obj-m += main.o

CC := gcc
CFLAGS := -Wall -Wextra
TARGET := program
KERNEL_BUILD_DIR := /lib/modules/$(shell uname -r)/build


BUILD_DIR := ./build
JOB_SRC_DIR := ./src/job
JOB_SRC_FILES := $(wildcard $(JOB_SRC_DIR)/*.c)
JOB_OBJ_DIR := $(BUILD_DIR)/job
JOB_OBJS := $(patsubst $(JOB_SRC_DIR)/%.c, $(JOB_OBJ_DIR)/%.o, $(JOB_SRC_FILES))

all: $(JOB_OBJS)

# rule to compile .c files in ./src/job to ./obj/job .o files
$(JOB_OBJ_DIR)/%.o: $(JOB_SRC_DIR)/%.c | $(JOB_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ensure ./build/job exists
$(JOB_OBJ_DIR): $(BUILD_DIR)
	mkdir -p $(JOB_OBJ_DIR)

# ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)