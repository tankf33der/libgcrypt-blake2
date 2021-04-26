#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <gcrypt.h>
#include "blake2.h"		// libb2

// Loup Valiant is hero
void print_vector(const uint8_t *buf, size_t size)
{
    for(size_t i = 0; i < size; i++) {
        printf("%x%x", buf[i] >> 4, buf[i] & 0x0f);
    }
    printf(":\n");
}

int main(void) {
	uint8_t d[32];
	gcry_md_hd_t ctx;
	uint8_t *s1;
	uint8_t s2[32];

	for(size_t i = 0; i < 32; i++) d[i] = i;

	// libgcrypt
	gcry_md_open(&ctx, GCRY_MD_BLAKE2S_256, 0);
	gcry_md_setkey(ctx, d, 0);
	gcry_md_write(ctx, d, 32);
	s1 = gcry_md_read(ctx, GCRY_MD_BLAKE2S_256);

	// libb2
	blake2s(s2, d, d, 32, 32, 0);

	print_vector(s1, 32);
	print_vector(s2, 32);
	return 0;
}

/*
$ make demo
gcc -Wall -Wextra demo.c -lgcrypt -lb2 && ./a.out
ad81ee42a31f9b5b4d4e67e5e05514d3c26670325f570628fa3947a6867df134:
05825607d7fdf2d82ef4c3c8c2aea961ad98d60edff7d018983e21204c0d93d1:

//gcry_md_setkey(ctx, d, 1);
//blake2s(s2, d, d, 32, 32, 1);
$ make demo
gcc -Wall -Wextra demo.c -lgcrypt -lb2 && ./a.out
ca21cd1cb9bcbd9d66327dfc84e15f4f5806c287bb9a9b3f72549799d73f3d3b:
ca21cd1cb9bcbd9d66327dfc84e15f4f5806c287bb9a9b3f72549799d73f3d3b:
*/
