#include <stdint.h>

volatile uint32_t* counter = (uint32_t*)0x18000000;

int main() {
	*counter = 0;

	for( int i = 0 ; i < 0xffffffffff ; i ++ ) {

		*counter = (*counter) + 1;
	}

	while (1) {};

	return 0;
}
