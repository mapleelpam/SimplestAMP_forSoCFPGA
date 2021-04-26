
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "../shared/shared.h"

#ifdef ARROW_SOCKIT_GSRD_19_1
#include "../core1/core1_bin.c"
#define CORE1_BIN core1_bin
#define CORE1_BIN_LEN core1_bin_len
#else
#include "../core1/core1_sockit_bin.c" 
#define CORE1_BIN core1_sockit_bin
#define CORE1_BIN_LEN core1_sockit_bin_len
#endif

#define NUM_OF_MAPPED_ADDR 10 

struct {
	struct {
		unsigned int  phy_addr;
		unsigned int  size;
		unsigned int* vir_addr;
	} mmapped[ NUM_OF_MAPPED_ADDR ];
	int _fd;
} g_ctx;


int init_ctx()
{
	for ( int i = 0 ; i < NUM_OF_MAPPED_ADDR ; i ++ ) {
		g_ctx. mmapped[ i ]. phy_addr = 0;
		g_ctx. mmapped[ i ]. size = 0 ;
		g_ctx. mmapped[ i ]. vir_addr = NULL;
	}
	g_ctx. _fd = 0;
	
	g_ctx. _fd= open("/dev/mem", O_RDWR|O_SYNC);
	if(g_ctx. _fd < 0){
		printf(" failed to open /dev/mem\n");
		return -1;
	}
}

int destroy_ctx()
{
	for ( int i = 0 ; i < NUM_OF_MAPPED_ADDR ; i ++ ) {
		if( g_ctx. mmapped[ i ]. vir_addr ) {
			munmap( g_ctx. mmapped[i]. vir_addr, g_ctx. mmapped[i]. size );
			g_ctx. mmapped[ i ]. phy_addr = 0;
			g_ctx. mmapped[ i ]. size = 0;
			g_ctx. mmapped[ i ]. vir_addr = NULL;
		}
	}
	close( g_ctx. _fd ); g_ctx. _fd = 0;
}
void _prepare_vir_memory( int index, unsigned int addr, unsigned int size )
{
	g_ctx. mmapped[ index ]. phy_addr = addr;
	g_ctx. mmapped[ index ]. size = size;
	g_ctx. mmapped[ index ]. vir_addr = (unsigned int *)mmap(NULL,
			g_ctx. mmapped[ index ]. size,
			PROT_READ|PROT_WRITE,
			MAP_SHARED,
			g_ctx. _fd,
			g_ctx. mmapped[ index ]. phy_addr);
}

unsigned int ctx_phymem_memcpy( unsigned int addr, int size, int offset, unsigned char* copy_from, int length_of_copy )
{
	int copy_success = -1;
	for ( int i = 0 ; i < NUM_OF_MAPPED_ADDR ; i ++ ) {
		if( g_ctx. mmapped[ i ]. phy_addr == 0 && g_ctx. mmapped[ i ]. size == 0 ) {
			_prepare_vir_memory( i, addr, size );
		}
		if( g_ctx. mmapped[ i ]. phy_addr == addr && g_ctx. mmapped[ i ]. size == size ) {
			memcpy( g_ctx. mmapped[ i ]. vir_addr, copy_from, length_of_copy );
			copy_success = 1; break;
		}
	}

	return copy_success;
}

unsigned int ctx_phymem_map( unsigned int addr, int size, void** return_value )
{
	int map_success = -1;
	for ( int i = 0 ; i < NUM_OF_MAPPED_ADDR ; i ++ ) {
		if( g_ctx. mmapped[ i ]. phy_addr == 0 && g_ctx. mmapped[ i ]. size == 0 ) {
			_prepare_vir_memory( i, addr, size );
		}
		if( g_ctx. mmapped[ i ]. phy_addr == addr && g_ctx. mmapped[ i ]. size == size ) {
			*return_value = (void*) (g_ctx. mmapped[ i ]. vir_addr );
			map_success = 1; break;
		}
	}

	return map_success;
}


int main(int argc, char** argv)
{
	int ret_value = 0;

	ret_value = init_ctx(); // Open /dev/mem and initialize global context
	if( ret_value < 0 )	return -1;

	/*  Address - 0xFFD08000, system manager
	 *  Length  - 0x1000, a page
	 *  Offset  - 0xC4/4, <-- cpu1startaddr/ cv_54001.pdf / p6-56
	 *  Value   - 0x10000000, <-- the address of start address of BM
	 * */
//	ret_value = ctx_phymem_write( 0xFFD08000, 0x1000, (0xC4/4), 0x10000000 );
//	if( ret_value < 0 )	goto LEAVE;
	
	volatile unsigned int *pointer_zero = NULL;
	ret_value = ctx_phymem_map( 0x00000000, 0x1000, (void*) &pointer_zero );
	if( ret_value < 0 )	goto LEAVE; 

	int pointer_zero_save = *pointer_zero;
	*pointer_zero = 0xE3A0F201 /* ldr pc, =x10000000 */;

	/*  Address - 0xFFD05000, reset manager
	 *  Length  - 0x1000, a page
	 *  Offset  - 0x10,  (/4 for 32bit addressing)
	 *  Value   - ,
	 *  Referenc - cv_54001.pdf / p4-17 / rstmgr -mpumodrst/ bit1-1 meant to assert CPU1 
	 * */
	volatile unsigned int *mpumodrst = NULL;
	ret_value = ctx_phymem_map( 0xFFD05000, 0x1000, (void*) &mpumodrst );
	if( ret_value < 0 )	goto LEAVE; 
	mpumodrst += (0x10/4);

	*mpumodrst = (*mpumodrst) | (~0xFFFFFFFD);
	usleep( 1000 );

	/* copy core1 BM program to the address */
	ctx_phymem_memcpy( 0x10000000, 0x3000000, 0x0, CORE1_BIN, CORE1_BIN_LEN);

	/*  Address - 0xFFD05000, reset manager
	 *  Length  - 0x1000, a page
	 *  Offset  - 0x10/4, 
	 *  Value   - 0x10000000,
	 *  Referenc - cv_54001.pdf / p4-17 / rstmgr -mpumodrst/ bit1-0 meant to de-assert CPU1 
	 * */
	*mpumodrst = (*mpumodrst) & (0xFFFFFFFD); 
	usleep( 1000 );

	*pointer_zero = pointer_zero_save; // recovery, after reset


	shared_memory_t *shm= NULL;
	ctx_phymem_map( SHARED_MEM_ADDRESS, 0x1000, (void*) &shm);
	shm->pong = 1;

	unsigned int prev_ping = -1 ;
	unsigned int prev_btn = shm->btn ;
	unsigned int prev_dip = shm->dip ;
	while ( 1 ) { /* 0x18000000 */

		if( prev_ping != shm->ping ) {
			prev_ping = shm->ping;
//			printf( "CPU1 - BM Ping = %d\n", prev_ping );
			shm->pong ++;
		}

		if( prev_btn != shm->btn ) {
			prev_btn = shm->btn;
			printf("CPU1 - FPGA Button chagned 0x%d\n", prev_btn );
		}
		if( prev_dip != shm->dip ) {
			prev_dip = shm->dip;
			printf("CPU1 - FPGA DIP chagned 0x%d\n", prev_dip );
		}

	}


LEAVE:
	destroy_ctx();
}
