# SimplestAMP_forSoCFPGA

## Goal
 1. Simple/ Lean as possible
 1. Hardware independent (should apply to any CV/AV and A10 SoCFPGA without or limited modification )

## Simple Description for each

  Course | Description |
  --- | --- |
  Course1 | initialize. simple example for BM and how to trigger CPU1 in Linux |
  Course2 | Closed to real world application and show the communication skelton |
  Course3 | Example for FPGA HW/IP read and write through the bridge in GHRD |

## Tested Enviroment 


SoCFPGA |Hardware/Software | core0 | core1 | Host Enviorment |
:---: | :---: | --- | --- | :---:
Cyclone5 | [Arrow SoCKit 201911](https://rocketboards.org/foswiki/Documentation/ArrowSoCKitEdition201911) | [gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabi](https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-linux-gnueabihf/) | [gcc-arm-none-eabi-9-2019-q4-major](https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2?revision=108bd959-44bd-4619-9c19-26187abf5225&la=en&hash=E788CE92E5DFD64B2A8C246BBA91A249CB8E2D2D)| Ubuntu 20.04.1 LTS 
