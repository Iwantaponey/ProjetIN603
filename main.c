#include <stdio.h>
#include <gmp.h>
#include "fonction.h"

int main(int argc, char** argv)
{
	mpz_t a;
	
	mpz_init_set_str(a, argv[1], 10); // Nombre à tester initié à la valeur saisie en argument d'exécution
	
	if(mpz_cmp_ui(a, 3) == -1) 
	{
		gmp_printf("Le nombre %Zd est premier\n", a);
		return 0;
	}
	if((mpz_cmp_ui(a, 2) != 0) && (mpz_tstbit(a, 0) == 0)) // Si nombre est pair et différent de 2 alors il est toujours composé
	{
		gmp_printf("Le nombre %Zd est composé\n", a);
		return 0;
	}
	
	int k = 3;
	//fermat(a, k); // Test : savoir si a est premier ou pas avec un nombre d'itération de k
	printf("D'après l'algorithme de Miller-Rabin, le nombre");
	int ok = miller_rabin(a, k);
	return ok;
}
