#!/bin/bash

# compile {BUILD_DIR}/job.o
./scripts/job/compile_job.sh
# compile {BUILD_DIR}/tests/test_job
./scripts/job/compile_job_tests.sh
./build/test/test_job