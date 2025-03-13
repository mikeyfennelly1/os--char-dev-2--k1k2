#!/bin/bash

mkdir -p ../build

# 
#
#
function compile_to_object() {
    local file=$1
    local build_dir="../build"
    local file_basename=$(basename "$file")
    local output_obj_name="${file_basename%.c}.o"
    gcc -Wall -Wextra -c ${file} -o ${build_dir}/${output_obj_name}
}

function compile_job() {
    compile_to_object ../src/device/job/job.c
}

function test_job() {
    mkdir -p ../build/test
    gcc -Wall -Wextra ../test/job/test_job.c ../build/job.o -o ../build/test/test_job
}

compile_job
test_job