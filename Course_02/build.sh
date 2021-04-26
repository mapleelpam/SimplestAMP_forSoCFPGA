#!/usr/bin/env bash

set -x -e

pushd core1/

arm-none-eabi-as -o startup.o startup.s
arm-none-eabi-gcc -c -nostdlib -nostartfiles -o cstart.o cstart.c
arm-none-eabi-ld -T linkscript.ld -o core1.elf startup.o cstart.o
arm-none-eabi-objcopy -O binary core1.elf core1.bin
arm-none-eabi-objdump -d core1.elf > core1.elf.objdump
xxd -i core1.bin core1_bin.c

popd

pushd core0/

arm-linux-gnueabi-gcc -o core0_linux_c2 core0_linux_app.c -static

popd

