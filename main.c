#include <stdio.h>
#include <gmp.h>
#include "fonction.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
	mpz_t a;
	mpz_init_set_str(a, argv[1], 10); 			/*!< Nombre à tester initié à la valeur saisie en argument d'exécution */
	
	int k = atoi(argv[2]); 			/*!< Nombre de répétitions des deux algorithmes */
	
	
	/***********Tests sur k***************************************/
	
	if(k < 1)
	{
		printf("Impossible de faire 0 répétition\n");
		return 0;
	}
	
	
	/***********Tests sur le nombre*******************************/

	if((mpz_cmp_ui(a, 0) == 0) || (mpz_cmp_ui(a, 1) == 0))
	{
		gmp_printf("Le nombre %Zd n'est pas considéré comme premier\n", a);
		return 0;
	}	
	if(mpz_cmp_ui(a, 4) == -1) 			/*!< Si un nombre est strictement inférieur à 4 alors il est forcément premier */
	{
		gmp_printf("Le nombre %Zd est premier\n", a);
		return 0;
	}
	if((mpz_cmp_ui(a, 2) != 0) && (mpz_tstbit(a, 0) == 0)) 			/*!< Si nombre est pair et différent de 2 alors il est toujours composé */
	{
		gmp_printf("Le nombre %Zd est composé\n", a);
		return 0;
	}
	
	
	/***********Appel des fonctions des algorithmes***************/
	
	printf("D'après l'algorithme de Fermat, le nombre");
	fermat(a, k);
	printf("D'après l'algorithme de Miller-Rabin, le nombre");
	miller_rabin(a, k);
	
	return 0;
}
