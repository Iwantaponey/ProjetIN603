#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"

expo binaire(mpz_t h)
{
	int i=0,j=0,k;
	mpz_t x,r,d,u,q,z; char * str=malloc(2048*sizeof(char)); 
	mpz_init(r); mpz_init(q);
	mpz_init_set_str(d,"2",10);
	mpz_init_set_str(u,"1",10);
	mpz_init_set_str(z,"0",10);
	mpz_init_set(x,h);
	
	
	while(mpz_cmp(x,z) && i<2048)	
	{	
		mpz_fdiv_r(r,x,d);
		mpz_fdiv_q(q,x,d);
		if(!mpz_cmp(r,u))
			str[i]='1';
		else 
			str[i]='0';
		mpz_set(x,q);
		i++;
	}
	printf("str = %s \n", str);
	printf("taille de str= %d \n", i);
	mpz_clear(d);
	mpz_clear(q);
	mpz_clear(u);
	mpz_clear(x);
	mpz_clear(r);
	expo e={str, strlen(str)};
	return e;
}


// La variable result sert à stocker le résultat de l'exponentiation rapide pour l'utiliser dans la fonction fermat
void square_multiply(mpz_t a, mpz_t n, mpz_t h, mpz_t result) // a est l'entier qui porte l'exposant h qui est aussi un entier, n est le modulo de a
{
	expo e;
	mpz_t bin, impair; // Déclaration d'un grand entier result
	mpz_set(result, a); // Mettre la valeur de a dans result
	mpz_init(bin);
	mpz_init_set_str(impair, "1", 10); // Allouer et mettre 1 dans impair
	e=binaire(h);
	printf("dans square_multiply, str = %s \n", e.str);	 
	int i ;
	for (i = e.t-2; i>=0; i--)
	{
		mpz_mul(result, result, result); // Square
		printf("e.str[%d]= %c \n",i,e.str[i]);
		gmp_printf("dans la boucle for, i = %d, result = %Zd , e.str[%d]=%c\n", i,result,i,e.str[i]);
		if(e.str[i]=='1') // Si on a un 1 dans l'écriture binaire
		{
			mpz_mul(result, result, a); // Multiply
			mpz_mod(result, result, n); // Multiply
		}
		gmp_printf("result = %Zd mod %Zd \n", result,n);
	}
	
	mpz_clear(bin);
	mpz_clear(impair);
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

void miller_rabin(mpz_t n, mpz_t k)
{

	
}
