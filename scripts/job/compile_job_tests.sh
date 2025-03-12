#!/bin/bash

mkdir -p ../../build/test

cd ../../test/job/
gcc -Wall -Wextra test_job.c ../../build/job.o -o ../../build/test/test_job