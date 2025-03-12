PWD := $(shell pwd)
CC := gcc
CFLAGS := -Wall -Wextra -g -I./src
DEPFLAGS := -MMD -MF $(@:.o=.d)

JOB_SRCS := $(wildcard ./src/device/job/*.c)
JOB_OBJS := $(patsubst %.c, %.o, $(JOB_SRCS))

all: job

job: $(JOB_SRCS:.c=.o)

# pattern rule for source to object compilation
%.o: %.c build_dir_exists
	$(CC) $(CFLAGS) -c $< -o $(PWD)/build/$(notdir $@)

%.d: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

build_dir_exists:
	@mkdir -p $(PWD)/build

# remove build dir
clean:
	@rm -rf ./build

test:
	./scripts/build.sh

install:
	sudo apt update
	sudo apt install libcunit1 libcunit1-doc libcunit1-dev
	sudo apt install libjson-c-dev