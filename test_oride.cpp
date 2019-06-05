#include <iostream>
#include <random>
#include <pbc.h>
#include "bgn.h"

using namespace std;

void test_simple_impl(int count)
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, (1<<9) - 1);
	

	int a, b, c, d;
	bgn_plaintext_t dx, dy, rx, ry; // driver-x, driver-y, rider-x, rider-y
	bgn_ciphertext_t edx, edy, erx, ery; // encrypted versions

	bgn_ciphertext_t euclidean; // euclidean

	for(int i = 0; i < count; ++i){

		
		// generate keys

		bgn_key_t sk, pk;
		bgn_key_generate(&sk, 1024);
    	bgn_key_init_set(&pk, &sk, 0);


    	// compute rider and driver location

    	a = distribution(generator);
    	b = distribution(generator);
    	c = distribution(generator);
    	d = distribution(generator);

    	bgn_plaintext_init_set_word(&dx, a);
    	bgn_plaintext_init_set_word(&dy, b);
    	bgn_plaintext_init_set_word(&rx, c);
    	bgn_plaintext_init_set_word(&ry, d);

    	// encrypt rider and driver location

    	bgn_encrypt(&edx, &dx, &pk);
    	bgn_encrypt(&edy, &dy, &pk);
    	bgn_encrypt(&erx, &rx, &pk);
    	bgn_encrypt(&ery, &ry, &pk);

    	// homomorphically compute euclidean distance

    	bgn_ciphertext_sub(&erx, &erx, &edx, &pk);
    	bgn_ciphertext_sub(&ery, &ery, &edy, &pk);

    	bgn_ciphertext_mul(&erx, &erx, &erx, &pk);
    	bgn_ciphertext_mul(&ery, &ery, &ery, &pk);

    	bgn_ciphertext_add(&euclidean, &erx, &ery, &pk);

    	// rider decrypts

    	bgn_plaintext_t dec;
		bgn_decrypt(&dec, &euclidean, &sk);
		unsigned long int dist;
		bgn_plaintext_to_word(&dec, &dist);

		unsigned long int original = (a-c)*(a-c) + (b-d)*(b-d);

		if(dist != original){
			cout << "Error in iteration " << i+1 << endl;
			cout << "Stopping simulation" << endl;

			break;
		} 


	}

	cout << "Simulation successful" << endl;
}


int main(){
	test_simple_impl(2);
}