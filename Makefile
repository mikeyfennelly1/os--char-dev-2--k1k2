PWD := $(shell pwd)
CC := gcc
CFLAGS := -Wall -Wextra -g -I./src

JOB_SRCS := $(wildcard ./src/device/job/*.c)
JOB_OBJS := $(patsubst %.c, %.o, $(JOB_SRCS))

all: job

job: $(JOB_SRCS:.c=.o)

# pattern rule for source to object compilation
%.o: %.c build_dir_exists
	$(CC) $(CFLAGS) -c $< -o ./build/$(notdir $@)

build_dir_exists:
	mkdir -p $(PWD)/build

# Clean build files
clean:
	@rm -rf ./build

install:
	sudo apt update
	sudo apt install libcunit1 libcunit1-doc libcunit1-dev