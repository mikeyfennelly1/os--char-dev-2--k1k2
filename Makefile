PWD := $(shell pwd)
SRCS := $(wildcard ./src/*.c)
OBJS := $(patsubst ./src/%.c, ./build/%.o, $(SRCS))

CC := gcc
CFLAGS := -Wall -Wextra

BUILD_DIR := $(PWD)/build
TEST_BIN_DIR := ./build/test
INCLUDES := -I./src -I/usr/include

all: job

job.o: $(BUILD_DIR)
	$(CC) $(CFLAGS) -c ./src/job.c -o $(BUILD_DIR)/job.o -ljson-c
test_job: job.o $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TEST_BIN_DIR)/test_job ./test/test_job.c ./src/job.c -ljson-c -lcunit

$(TEST_BIN_DIR):
	mkdir -p $(TEST_BIN_DIR)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

test: test_job
	@for binary in $(shell find ./build/test -type f -executable); do \
        echo "Running $$binary..."; \
        $$binary; \
    done

# remove build dir
clean:
	@rm -rf $(BUILD_DIR)

install:
	sudo apt update
	sudo apt install libcunit1 libcunit1-doc libcunit1-dev
	sudo apt install libjson-c-dev
