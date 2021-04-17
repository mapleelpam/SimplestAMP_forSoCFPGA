
#ifndef __SHARED_H__
#define __SHARED_H__

#define SHARED_MEM_ADDRESS 0x18000000

typedef struct {
	int ping; // modify by core1, receive from core0
	int pong; // modify by core0, receive from core1

} shared_memory_t;


#endif
