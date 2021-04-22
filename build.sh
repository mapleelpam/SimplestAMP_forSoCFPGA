#!/usr/bin/env bash

set -x

pushd Course_01/
./build.sh 
popd


pushd Course_02/
./build.sh 
popd

pushd Course_03/
./build.sh 
popd

