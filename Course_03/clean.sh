#!/usr/bin/env bash

set -x

pushd core1/
rm -f startup.o cstart.o core1.elf  core1.bin  core1.elf.objdump  core1_bin.c
popd

pushd core0/ 
rm -f core0_linux_c3
popd
