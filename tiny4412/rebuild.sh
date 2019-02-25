#!/bin/bash
#make distclean
#make $1
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-
#important:! only origen board support SPL
#make origen_defconfig	
make V=1 
#arm-linux-gnueabihf-objdump -D u-boot > u-boot.dis
rm spl/u-boot-spl.dis
arm-linux-gnueabihf-objdump -D spl/u-boot-spl > u-boot-spl.dis
#rm s5pv210*.bin
#./mkv210_image  u-boot.bin s5pv210_for_sd.bin
