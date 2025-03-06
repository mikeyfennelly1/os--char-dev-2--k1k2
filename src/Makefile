obj-m += main.o

PROJ_BUILD_DIR := ./build
KERNEL_BUILD_DIR := /lib/modules/$(shell uname -r)/build

all: build post_build_cleanup

build:
	make -C $(KERNEL_BUILD_DIR) M=$(shell pwd) modules

# remove redundant files that were created during compile
post_build_cleanup:
	rm -f .main.ko.cmd
	rm -f main.mod
	rm -f main.mod.c
	rm -f main.mod.o
	rm -f main.o
	rm -f modules.order
	rm -f Module.symvers
	rm -f .main.o.d
	find . -maxdepth 1 -type f -name ".*" -delete

clean:
	make -C $(KERNEL_BUILD_DIR) M=$(shell pwd) clean

# print local vars when debugging
print_vars:
	echo "PROJ_BUILD_DIR=$(PROJ_BUILD_DIR)"
	echo "KERNEL_BUILD_DIR=$(KERNEL_BUILD_DIR)"