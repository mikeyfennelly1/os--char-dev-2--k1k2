#!/bin/bash


build_dir="./build"
job_dir="./src/device/job"
mkdir -p ${build_dir}


gcc -Wall -Wextra -c ${job_dir}/job.c -o ${build_dir}/prejob.o
gcc -Wall -Wextra -c ${job_dir}/job_buffer.c -o ${build_dir}/job_buffer.o
gcc -Wall -Wextra -r ${build_dir}/prejob.o ${build_dir}/job_buffer.o -o ${build_dir}/job.o
rm ${build_dir}/prejob.o ${build_dir}/job_buffer.o