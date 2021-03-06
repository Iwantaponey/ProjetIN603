#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

 /** Description des arguments des fonctions dans le fichier README.txt */

void square_multiply(mpz_t a, mpz_t n, mpz_t h, mpz_t result) 
{
	mpz_set(result, a);
	
	size_t taille = mpz_sizeinbase(h, 2);			/*!< Obtenir le nombre de bits de h */
	
	int i;
	for (i = taille-2; i >= 0; i--)
	{
		mpz_mul(result, result, result); 			/*!< Square (faire le carré) */
		if(mpz_tstbit(h, i) == 1)
		{
			mpz_mul(result, result, a); 			/*!< Multiply */
		}
		mpz_mod(result, result, n);					/*!< Modulo */
	}
}

int fermat(mpz_t n, int k)
{
	mpz_t a, result, tmp, tmp2;
	mpz_init(a); mpz_init(result); mpz_init(tmp); mpz_init(tmp2);
	mpz_sub_ui(tmp, n, 1);
	mpz_sub_ui(tmp2, n, 3);
	
	gmp_randstate_t state;
	gmp_randinit_default(state);
	
	int i;
	for (i = 0; i < k; i++)
	{
		mpz_urandomm(a, state, tmp2); 			/*!< Génération d'un random 0 <= a <= (n-3) */
		mpz_add_ui(a, a, 2); 					/*!< On rajoute 2 pour avoir 1 < a < (n-1) */
		
		square_multiply(a, n, tmp, result);
		
		if(mpz_cmp_ui(result, 1) != 0)
		{
			gmp_printf(" %Zd est composé\n", n);
			return 0;
		}
	}
	gmp_printf(" %Zd est premier\n", n);
	
	gmp_randclear(state);
	mpz_clear(result); mpz_clear(tmp); mpz_clear(tmp2); mpz_clear(a);
	return 0;
}

mp_bitcnt_t decomposer(mpz_t tmp, mpz_t t)
{
	mpz_t div;
	
	mpz_init_set_str(div, "0", 10);
	mp_bitcnt_t s = mpz_scan1(tmp, 0);
	mpz_setbit(div, s);					/*!< Mettre le bit s de div à 1 pour que div = 2^s */
	mpz_cdiv_q(t, tmp, div);			/*!< Obtenir t = tmp/div */
	
	mpz_clear(div);
	return s;
}

int miller_rabin(mpz_t n, int k)
{
	int i, j, bool = 0;
	mpz_t r, y, t, tmp, tmp2;
	mpz_init(r); mpz_init(y); mpz_init(t); mpz_init(tmp); mpz_init(tmp2);
	
	gmp_randstate_t state; 					/*!< Création de la graine du random */
	gmp_randinit_default(state); 			/*!< Initialisation de la graine du random */
	
	mpz_sub_ui(tmp, n, 1); 					/*!< La décomposition se fait sur n-1 stocké dans tmp */
	mp_bitcnt_t s = decomposer(tmp, t); 	/*!< Appel de la fonction de décomposition de n-1 sous forme (2^s)*t avec t impair */
	
	mpz_sub_ui(tmp2, tmp, 1); 				/*!< On prend n-2 pour borne supérieur de la génération de l'aléatoire puis on rajout 1 afin de ne pas tomber sur un aléatoire égal à zéro */
	
	for (i = 1; i < k; i++)
	{
		mpz_urandomm(r, state, tmp2); 		/*!< Génération du random 0 <= r <= (n-2) */
		mpz_add_ui(r, r, 1); 				/*!< On ajoute 1 pour avoir 0 < r < (n-1) */
		
		square_multiply(r, n, t, y);
		
		if((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, tmp) != 0))
		{
			for (j = 0; j < s-1; j++)
			{
				mpz_mul(y, y, y);
				mpz_mod(y, y, n);
				if(mpz_cmp_ui(y, 1) == 0)
				{
					gmp_printf(" %Zd est composé\n", n);
					mpz_clear(r); mpz_clear(y); mpz_clear(t); mpz_clear(tmp); mpz_clear(tmp2);
					gmp_randclear(state);
					return 0;
				}
				if(mpz_cmp(y, tmp) == 0)
				{
					bool = 1;
					break; 					/*!< Arrêter la boucle j et continuer avec le i suivant */
				}
			}
			if(bool == 0)
			{
				gmp_printf(" %Zd est composé\n", n);
				mpz_clear(r); mpz_clear(y); mpz_clear(t); mpz_clear(tmp); mpz_clear(tmp2);
				gmp_randclear(state);
				return 0;
			}
		}		
	}
	gmp_printf(" %Zd est premier\n", n);
	
	mpz_clear(r); mpz_clear(y); mpz_clear(t); mpz_clear(tmp); mpz_clear(tmp2);
	gmp_randclear(state);
	return 0;
}
