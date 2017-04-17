#include <stdio.h>
#include <gmp.h>
#include "fonction.h"

int main() 
{
	mpz_t a, n, h,result;
	mpz_init_set_str(h,"3",10);
	mpz_init_set_str(a,"5",10);
	mpz_init_set_str(n,"200",10);
	mpz_init(result);
	square_multiply(a,n,h,result);
	return 0;
}
