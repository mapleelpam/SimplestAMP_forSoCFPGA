#include <stdint.h>
#include "../shared/shared.h"

shared_memory_t* shm = (shared_memory_t*) SHARED_MEM_ADDRESS;

int main() {

	shm->ping = 0;

	int prev_pong = -1;
	while (1) {

		if( prev_pong != shm->pong ) {
			prev_pong = shm->pong;
			shm->ping ++;
		}
			
	};

	return 0;
}
