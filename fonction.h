#include <stdio.h>
#include <gmp.h>

void binaire(mpz_t bin, mpz_t H);
void square_multiply(mpz_t a, mpz_t n, mpz_t h);
void fermat(mpz_t n, mpz_t k);
void miller_rabin(mpz_t n, mpz_t k);
