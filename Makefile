PROJ_ROOT:=$(shell pwd)				# pwd at beginning of make command
SRCS:=$(PROJ_ROOT)/src 				# directory containing sources
SCRIPTS:=$(PROJ_ROOT)/scripts		# directory containing scripts
BUILD:=$(PROJ_ROOT)/build			# directory containing build objects

# default target
#
# build the target .o and .ko files
all: $(BUILD)
	# build kernel module from sources in ./src directory
	make -C /lib/modules/$(shell uname -r)/build M=$(SRCS) modules
	
	# move targets out to build directory
	cd $(SRCS) && $(SCRIPTS)/post_build_cleanup.sh

	# remove any other generated files from source directory
	make -C /lib/modules/$(shell uname -r)/build M=$(SRCS) clean
	
# create ./test/bin directory if it doesn't exist
$(TEST_BIN_DIR):
	mkdir -p $(TEST_BIN_DIR)

# create ./build directory if it doesn't exist
$(BUILD):
	@mkdir -p ./build

# remove build directory recursively
clean:
	@rm -rf ./build

# install project dependencies
install:
	sudo apt update
	sudo apt install libcunit1 libcunit1-doc libcunit1-dev
	sudo apt install libjson-c-dev