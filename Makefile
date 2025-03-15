PROJ_ROOT:=$(shell pwd)
SRCS:=$(PROJ_ROOT)/src
SCRIPTS:=$(PROJ_ROOT)/scripts
BUILD:=$(PROJ_ROOT)/build

all: $(BUILD)
	make -C /lib/modules/$(shell uname -r)/build M=$(SRCS) modules
	cd $(SRCS) && $(SCRIPTS)/post_build_cleanup.sh

$(TEST_BIN_DIR):
	mkdir -p $(TEST_BIN_DIR)

$(BUILD):
	@mkdir -p ./build

test: test_job
	@for binary in $(shell find ./build/test -type f -executable); do \
        echo "Running $$binary..."; \
        $$binary; \
    done

clean:
	@rm -rf ./build

install:
	sudo apt update
	sudo apt install libcunit1 libcunit1-doc libcunit1-dev
	sudo apt install libjson-c-dev