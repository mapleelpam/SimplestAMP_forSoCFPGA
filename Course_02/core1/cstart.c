#include <stdint.h>
#include "../shared/shared.h"

baton_t* baton = (baton_t*) SHARED_MEM_ADDRESS;

int main() {

	baton->ping = 0;

	int prev_pong = -1;
	while (1) {

		if( prev_pong != baton->pong ) {
			prev_pong = baton->pong;
			baton->ping ++;
		}
			
	};

	return 0;
}
