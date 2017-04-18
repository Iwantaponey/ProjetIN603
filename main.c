#include <stdio.h>
#include <gmp.h>
#include "fonction.h"

int main() 
{
	mpz_t a;// n, h,result;
	//mpz_init_set_str(h,"12",10);
	mpz_init_set_str(a,"1483",10);
	//mpz_init_set_str(n,"53",10);
	//mpz_init(result);
	//square_multiply(a,n,h,result);
	int k = 6;
	fermat(a, k); // Test : savoir si a est premier ou pas avec un nombre d'itération de k
	return 0;
}
