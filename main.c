#include <stdio.h>
#include <gmp.h>
#include "fonction.h"

int main() 
{
	mpz_t a, n, h;
	mpz_init_set_str(h,"1830",10);
	square_multiply(a,n,h);
	return 0;
}
