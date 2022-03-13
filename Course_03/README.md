
## Goal 
 To improve 3 major shortcoming in Course01
 1. Seperated 2 files. AMP is Walking the tightrope. Sometime seperated file will miss the version and cause debuging mistake.
 1. Core1 is free running. So we add ping/pong communication in polling style to let linux application get continuous numbers.
 1. There's no shared memory/ data format definition.

## Solution
 1. used 'xxd' to embedded core1 binary into linux application (prevent version mismatch)
 1. add shared.h to align core0/1 
 1. add two value - ping and pong. And let different core read or write its own value. Be careful, we're still running in 'SMP' mode. There's no mechism to prevent memory violation. 

## Result 

root@arrow-sockit:~/amp# ./core0_linux_app

CPU1 - BM Ping = 1  
CPU1 - BM Ping = 2  
CPU1 - BM Ping = 3  
CPU1 - BM Ping = 4  
CPU1 - BM Ping = 5  
CPU1 - BM Ping = 6  
CPU1 - FPGA Button chagned 0x08
CPU1 - BM Ping = 7  
CPU1 - BM Ping = 8  
CPU1 - BM Ping = 9  
CPU1 - BM Ping = 10  
CPU1 - FPGA Button chagned 0x00
CPU1 - BM Ping = 11  
CPU1 - BM Ping = 12  

