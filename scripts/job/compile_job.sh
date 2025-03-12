#!/bin/bash

mkdir -p ../../build

cd ../../src/device/job/ 
make
mv ./job.o ../../../build/job.o