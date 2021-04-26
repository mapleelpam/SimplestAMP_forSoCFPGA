#!/usr/bin/env bash

set -x -e

pushd core1/
rm -f startup.o cstart.o core1.elf  core1.bin  core1.elf.objdump 
popd

pushd core0/ 
rm -f core0_linux 
popd
