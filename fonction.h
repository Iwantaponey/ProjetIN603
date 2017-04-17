#include <stdio.h>
#include <gmp.h>

char * binaire(mpz_t h);
void square_multiply(mpz_t a, mpz_t n, mpz_t h);
void fermat(mpz_t n, mpz_t k);
void miller_rabin(mpz_t n, mpz_t k);
