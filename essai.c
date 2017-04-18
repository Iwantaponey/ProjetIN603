#include <stdio.h>
#include <gmp.h>
#include <time.h>

// La variable result sert à stocker le résultat de l'exponentiation rapide pour l'utiliser dans la fonction fermat
void square_multiply(mpz_t a, mpz_t n, mpz_t h, mpz_t result) // a est l'entier qui porte l'exposant h qui est aussi un entier, n est le modulo de a
{
	mpz_t bin, impair; // Déclaration d'un grand entier result
	mpz_set(result, a); // Mettre la valeur de a dans result
	mpz_init(bin);
	mpz_init_set_str(impair, "1", 10); // Allouer et mettre 1 dans impair
	
//	appel fonction binaire(bin, h); // Récupérer le binaire de h pour la boucle
	
	int i, t = 3;
	for (i = t-1; i < 0; i++)
	{
		mpz_mul(result, result, result); // Square
		if(!mpz_cmp(bin, impair)) // Si on a un 1 dans l'écriture binaire
		{
			mpz_mul(result, result, a); // Multiply
			mpz_mod(result, result, n); // Multiply
		}
	}
	mpz_clear(bin);
	mpz_clear(impair);
}

void miller_rabin(mpz_t n, int k)
{
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	mpz_t impair, impair2, result;
	mpz_init_set_str(impair2, "-1", 10);
	mpz_init_set_str(impair, "1", 10);
	mpz_init(result);
	
	// Appel fonction de décomposition de n-1 en (2^s)*t avec t impair
	for (i = 1; i < k; i++)
	{
		gmp_randseed_ui(state, time(NULL));
		mpz_urandomm(a, state, n);
		while(mpz_cmp(a, n) == -1)
		{
			gmp_randseed_ui(state, time(NULL));
			mpz_urandomm(a, state, n);
		}
		square_multiply(a, n, t, result); // Calcul de l'exponentielle dans a
		if((result != impair) && (result != impair2)
		{
			for (j = 1; j < (s-1); j++)
			{
				square_multiply(result, n, 2, result);
				if(result == impair)
				{
					printf("%s\n", "composé");
				}
				else if(result == impair2)
				{
					break;
				}
				
			}
			printf("%s\n", "composé");
		}
	}
	printf("%s\n", "premier");
}

void fermat(mpz_t n, int k) // n est un grand entier et k est juste un int, c'est le nombre de répétition
{
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	mpz_t impair, a, result;
	mpz_init_set_str(impair, "1", 10);
	mpz_init(result); // Equivalent d'un malloc
	
	int i;
	for (i = 1; i < k; i++)
	{
		gmp_randseed_ui(state, time(NULL));
		mpz_urandomm(a, state, n);
		while(mpz_cmp(a, n) == -1)
		{
			gmp_randseed_ui(state, time(NULL));
			mpz_urandomm(a, state, n);
		}
		square_multiply(a, (n-1), n, result); // Calcul de l'exponentielle dans a
		if(!mpz_cmp(result, impair)) // On cherche à savoir 
		{
			printf("%s\n", "composé");
			return ;
		}
	}
	printf("%s\n", "premier");
	
	gmp_randclear(state);
	mpz_clear(result);
	mpz_clear(impair);
}

int main(void) {
 mpz_t x,y,result;

 mpz_init_set_str(x, "7612058254738945", 10);
 mpz_init_set_str(y, "9263591128439081", 10);
 mpz_init(result);

 mpz_mul(result, x, y);
 gmp_printf("    %Zd\n"
            "*\n"
            "    %Zd\n"
            "--------------------\n"
            "%Zd\n", x, y, result);

 /* free used memory */
 mpz_clear(x);
 mpz_clear(y);
 mpz_clear(result);

 return 0;
}
