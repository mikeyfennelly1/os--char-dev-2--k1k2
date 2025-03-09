obj-m += main.o

CC := gcc
CFLAGS := -Wall -Wextra
TARGET := program
KERNEL_BUILD_DIR := /lib/modules/$(shell uname -r)/build


BUILD_DIR := ./build
DEVICE_SRC_DIR := ./src/device
DEVICE_SRC_FILES := $(wildcard $(DEVICE_SRC_DIR)/*.c)
DEVICE_OBJ_DIR := $(BUILD_DIR)/device
DEVICE_OBJS := $(patsubst $(DEVICE_SRC_DIR)/%.c, $(DEVICE_OBJ_DIR)/%.o, $(DEVICE_SRC_FILES))

all: $(DEVICE_OBJS)

# rule to compile .c files in ./src/device to ./obj/device .o files
$(DEVICE_OBJ_DIR)/%.o: $(DEVICE_SRC_DIR)/%.c | $(DEVICE_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ensure ./build/device exists
$(DEVICE_OBJ_DIR): $(BUILD_DIR)
	mkdir -p $(DEVICE_OBJ_DIR)

# ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)