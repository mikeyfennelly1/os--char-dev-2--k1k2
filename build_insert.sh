#!/bin/bash

make clean
cd src
make clean
cd ..
make
cd src
make clean
cd ..
sudo rmmod sysinfo
sudo insmod ./build/k_objs/sysinfo.ko
