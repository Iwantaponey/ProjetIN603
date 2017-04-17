#include <stdio.h>
#include <gmp.h>

typedef struct
{
	char * str;
	int t;
}expo; 

expo binaire(mpz_t h);
void square_multiply(mpz_t a, mpz_t n, mpz_t h, mpz_t result);
void fermat(mpz_t n, int k);
void miller_rabin(mpz_t n, mpz_t k);
