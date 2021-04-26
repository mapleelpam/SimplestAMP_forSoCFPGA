# SimplestAMP_forSoCFPGA

## Goal
 1. Simple/ Lean as possible
 2. decouple HW and easy to migrate to different generation and boards

## BareMetal Polling 
 The main reason of AMP (Linux+BM) is - 
  * unleash real-time capabilty in BareMetal 
  * use rich OpenSource resource in Linux
 If you have multiple, unknown latency, different priotiy event. It's better to use interrupt and/or enable an RTOS on a dedicate core.
 For simple case, polling should work for most cases.

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
Cyclone5 | [SoC Devlopment Kit 20.1](https://rocketboards.org/foswiki/Documentation/CycloneVSoCGSRD) | [gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabi](https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-linux-gnueabihf/) | [gcc-arm-none-eabi-9-2019-q4-major](https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2?revision=108bd959-44bd-4619-9c19-26187abf5225&la=en&hash=E788CE92E5DFD64B2A8C246BBA91A249CB8E2D2D)| Ubuntu 20.04.1 LTS 
