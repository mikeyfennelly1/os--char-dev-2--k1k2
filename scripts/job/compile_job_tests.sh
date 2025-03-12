#!/bin/bash

test_build_dir="./build/test"
test_src="./test/job/test_job.c"
mkdir -p ${test_dir}

gcc -Wall -Wextra ${test_src} -o ${test_build_dir}/test_job -lcunit -ljson-c -I./${test_build_dir}