#include <stdint.h>
#include "../shared/shared.h"

shared_memory_t* shm= (shared_memory_t*) SHARED_MEM_ADDRESS;

// Define in GHRD, and test with 19.1
#ifdef ARROW_SOCKIT_GSRD_19_1

volatile uint32_t* LED_PIO = (uint32_t*) ( 0xFF200000 + 0x10040 );
volatile uint32_t* DIP_PIO = (uint32_t*) ( 0xFF200000 + 0x10080 );
volatile uint32_t* BTN_PIO = (uint32_t*) ( 0xFF200000 + 0x100c0 );

#else  // This default setting is for CVSoCDevKit GSRD 20.1

volatile uint32_t* LED_PIO = (uint32_t*) ( 0xFF200000 + 0x60040 );
volatile uint32_t* DIP_PIO = (uint32_t*) ( 0xFF200000 + 0x60080 );
volatile uint32_t* BTN_PIO = (uint32_t*) ( 0xFF200000 + 0x600c0 );

#endif

int main() {

	shm->ping = 0;

	uint32_t prev_btn = *BTN_PIO;
	uint32_t prev_dip = *DIP_PIO;
	unsigned int prev_pong = -1;

	while (1) {

		if( prev_pong != shm->pong ) {
			prev_pong = shm->pong;
			shm->ping ++;

			*LED_PIO =  shm->ping;

		}
		if( prev_btn != *BTN_PIO ){ 
			prev_btn = shm->btn = *BTN_PIO;
		}
		if( prev_dip != *DIP_PIO ){ 
			prev_dip = shm->dip = *DIP_PIO;
		}
			
	};

	return 0;
}
