#!/bin/bash
make distclean
make $1
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-  V=1 
arm-linux-gnueabihf-objdump -D u-boot > u-boot.dis
