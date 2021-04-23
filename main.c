#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <gcrypt.h>

// Loup Valiant is hero
void print_vector(const uint8_t *buf, size_t size)
{
    for(size_t i = 0; i < size; i++) {
        printf("%x%x", buf[i] >> 4, buf[i] & 0x0f);
    }
    printf(":\n");
}


int main(void) {
	gcry_md_hd_t ctx;
	
	gcry_md_open(&ctx, GCRY_MD_BLAKE2S_256, GCRY_MD_FLAG_HMAC);
	
	return 0;
}
