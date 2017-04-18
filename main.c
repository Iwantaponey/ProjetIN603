#include <stdio.h>
#include <gmp.h>
#include "fonction.h"

int main() 
{
	mpz_t a, n, h,result;
	mpz_init_set_str(h,"26",10);
	mpz_init_set_str(a,"5",10);
	mpz_init_set_str(n,"200000000000000",10);
	mpz_init(result);
	//square_multiply(a,n,h,result);
	int k = 2;
	fermat(a, k); // Test : savoir si 5 est premier ou pas avec un nombre d'itération de k
	return 0;
}
