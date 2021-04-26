#!/usr/bin/env bash

set -x -e

pushd Course_01/
./build.sh 
popd


pushd Course_02/
./build.sh 
popd

pushd Course_03/
./build.sh 
popd

mkdir -p deploy 
cp Course_01/core0/core0_linux Course_01/core1/core1.bin Course_02/core0/core0_linux_c2 Course_03/core0/core0_linux_c3  Course_03/core0/core0_linux_c3_sockit deploy/
