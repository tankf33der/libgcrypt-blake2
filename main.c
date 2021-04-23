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
	int result = 0;
	uint8_t d[65];
	
	for(size_t i = 0; i < 65; i++) d[i] = i;


	for(size_t k = 1; k <= 32; k++)
		for(size_t m = 0; m <= 64; m++) {
			gcry_md_hd_t ctx;
			uint8_t *s1;
			uint8_t s2[32];

			// libgcrypt
			gcry_md_open(&ctx, GCRY_MD_BLAKE2S_256, 0);
			gcry_md_setkey(ctx, d, k);
			gcry_md_write(ctx, d, m);
			s1 = gcry_md_read(ctx, GCRY_MD_BLAKE2S_256);

			// libb2
			blake2s(s2, d, d, 32, m, k);

			result |= memcmp(s1, s2, 32);
			// printf("%ld:%ld:%d\n", k, m, result);
		}

	for(size_t k = 1; k <= 64; k++)
		for(size_t m = 0; m <= 64; m++) {
			gcry_md_hd_t ctx;
			uint8_t *s1;
			uint8_t s2[64];

			// libgcrypt
			gcry_md_open(&ctx, GCRY_MD_BLAKE2B_512, 0);
			gcry_md_setkey(ctx, d, k);
			gcry_md_write(ctx, d, m);
			s1 = gcry_md_read(ctx, GCRY_MD_BLAKE2B_512);

			// libb2
			blake2b(s2, d, d, 64, m, k);

			result |= memcmp(s1, s2, 64);
			// printf("%ld:%ld:%d\n", k, m, result);
		}
	
	return result;
}
