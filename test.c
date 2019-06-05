#include <pbc.h>
#include "bgn.h"

int main(void)
{
    // Key Generation

    bgn_key_t sk, pk;
	bgn_key_generate(&sk, 1024);
    bgn_key_init_set(&pk, &sk, 0);

    // Set messages

    bgn_plaintext_t m1, m2, m3;
    bgn_ciphertext_t c1, c2, c3, c4, c5, c6;
    bgn_plaintext_init_set_word(&m1, 5);
    bgn_plaintext_init_set_word(&m2, 7);
    bgn_plaintext_init_set_word(&m3, 3);


    // Encrypt 
	
	bgn_encrypt(&c1, &m1, &pk);
	bgn_encrypt(&c2, &m2, &pk);
	bgn_encrypt(&c3, &m3, &pk);

	// Homomorphic Add

	bgn_ciphertext_add(&c4, &c2, &c1, &pk);

	// Homomorphic Multiply

	bgn_ciphertext_mul(&c5, &c2, &c1, &pk);

	// Homomorphic Add

	bgn_ciphertext_add(&c6, &c5, &c3, &pk);

	// Print ciphertext

	printf("\n ciphertext is  ");
	char c[800];
	bgn_ciphertext_to_str(&c6, c, 800);

	printf("%s\n", c);


	// Decryption

	bgn_plaintext_t dm1;
	bgn_decrypt(&dm1, &c6, &sk);

	unsigned long msg;
	bgn_plaintext_to_word(&dm1, &msg);
	printf("%lu ", msg);


    return 0;
}