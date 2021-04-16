#include <stdint.h>
#include "../shared/shared.h"

baton_t* baton = (baton_t*) SHARED_MEM_ADDRESS;

volatile uint32_t* LED_PIO = (uint32_t*) ( 0xFF200000 + 0x10040 );
volatile uint32_t* DIP_PIO = (uint32_t*) ( 0xFF200000 + 0x10080 );
volatile uint32_t* BTN_PIO = (uint32_t*) ( 0xFF200000 + 0x100c0 );

int main() {

	baton->ping = 0;

	uint32_t prev_btn = *BTN_PIO;
	uint32_t prev_dip = *DIP_PIO;
	unsigned int prev_pong = -1;

	while (1) {

		if( prev_pong != baton->pong ) {
			prev_pong = baton->pong;
			baton->ping ++;

			*LED_PIO =  baton->ping;

		}
		if( prev_btn != *BTN_PIO ){ 
			prev_btn = baton->btn = *BTN_PIO;
		}
		if( prev_dip != *DIP_PIO ){ 
			prev_dip = baton->dip = *DIP_PIO;
		}
			
	};

	return 0;
}
