#!/usr/bin/env bash

set -x

pushd core1/

arm-none-eabi-as -o startup.o startup.s
arm-none-eabi-gcc -c -nostdlib -nostartfiles -o cstart.o cstart.c
arm-none-eabi-ld -T linkscript.ld -o core1.elf startup.o cstart.o
arm-none-eabi-objcopy -O binary core1.elf core1.bin
arm-none-eabi-objdump -d core1.elf > core1.elf.objdump
xxd -i core1.bin core1_bin.c

popd

pushd core0/

arm-linux-gnueabi-gcc -o core0_linux_app core0_linux_app.c -static

popd

#make -C ../common_uboot/ vexpress_ca9x4_config ARCH=arm CROSS_COMPILE=arm-none-eabi-
#make -C ../common_uboot/ all ARCH=arm CROSS_COMPILE=arm-none-eabi-

#../common_uboot/tools/mkimage -A arm -C none -T kernel -a 0x60000000 -e 0x60000000 -d cenv.elf bare-arm.uimg
#../common_uboot/tools/mkimage -A arm -C none -T kernel -a 0x60000000 -e 0x60000000 -d cenv.bin bare-arm.uimg
#./create-sd.sh sdcard.img bare-arm.uimg
