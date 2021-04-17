
#ifndef __SHARED_H__
#define __SHARED_H__

#define SHARED_MEM_ADDRESS 0x18000000

typedef struct {
	unsigned int ping; // modify by core1, receive from core0
	unsigned int pong; // modify by core0, receive from core1

	unsigned int dip;
	unsigned int btn;
} shared_memory_t;


#endif
