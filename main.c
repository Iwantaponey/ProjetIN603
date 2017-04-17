#include <stdio.h>
#include <gmp.h>
#include "fonction.h"

int main() 
{
	mpz_t a, n, h,result;
	mpz_init_set_str(h,"26",10);
	mpz_init_set_str(a,"5",10);
	mpz_init_set_str(n,"2000000000000000000000000000000000000000000000000000000000000000000",10);
	mpz_init(result);
	square_multiply(a,n,h,result);
	return 0;
}
