PWD := $(shell pwd)

all: job

job.o:
	./scripts/job/compile_job.sh

test_job: job.o	
	./scripts/job/compile_job_tests.sh	

build_dir_exists:
	@mkdir -p $(PWD)/build

# remove build dir
clean:
	@rm -rf ./build

install:
	sudo apt update
	sudo apt install libcunit1 libcunit1-doc libcunit1-dev
	sudo apt install libjson-c-dev
