#!/usr/bin/env bash

set -x -e

pushd core1/

arm-none-eabi-as -o startup.o startup.s
arm-none-eabi-gcc -c -nostdlib -nostartfiles -o cstart.o cstart.c
arm-none-eabi-ld -T linkscript.ld -o core1.elf startup.o cstart.o
arm-none-eabi-objcopy -O binary core1.elf core1.bin
arm-none-eabi-objdump -d core1.elf > core1.elf.objdump
xxd -i core1.bin core1_bin.c

arm-none-eabi-gcc -c -nostdlib -nostartfiles -o cstart.o cstart.c -DARROW_SOCKIT_GSRD_19_1
arm-none-eabi-ld -T linkscript.ld -o core1.sockit.elf startup.o cstart.o
arm-none-eabi-objcopy -O binary core1.sockit.elf core1.sockit.bin
arm-none-eabi-objdump -d core1.sockit.elf > core1.sockit.elf.objdump
xxd -i core1.sockit.bin core1_sockit_bin.c

popd

pushd core0/

arm-linux-gnueabi-gcc -o core0_linux_c3 core0_linux_app.c -static 
arm-linux-gnueabi-gcc -o core0_linux_c3_sockit core0_linux_app.c -static -DARROW_SOCKIT_GSRD_19_1

popd
