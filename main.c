#include <stdio.h>
#include <gmp.h>
#include "fonction.h"

int main() 
{
	mpz_t a;// n, h,result;
	//mpz_init_set_str(h,"12",10);
	mpz_init_set_str(a,"11",10);
	//mpz_init_set_str(n,"53",10);
	//mpz_init(result);
	//square_multiply(a,n,h,result);
	if((mpz_cmp_ui(a, 2) != 0) && (mpz_tstbit(a, 0) == 0)) // Si nombre est pair et différent de 2 alors il est toujours composé
	{
		printf("%s\n", "Composé");
		return 0;
	}
	
	int k = 2;
	//fermat(a, k); // Test : savoir si a est premier ou pas avec un nombre d'itération de k
	int ok = miller_rabin(a, k);
	return ok;
}
