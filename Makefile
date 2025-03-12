PWD := $(shell pwd)

all: job

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