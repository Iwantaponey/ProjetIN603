#include <stdio.h>
#include <gmp.h>

typedef struct
{
	char * str;
	int t;
}expo; 

expo binaire(mpz_t h);
void square_multiply(mpz_t a, mpz_t n, mpz_t h, mpz_t result);
int fermat(mpz_t n, int k);
mp_bitcnt_t decomposer(mpz_t tmp, mpz_t t);
int miller_rabin(mpz_t n, int k);
