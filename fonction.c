#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"

expo binaire(mpz_t h)
{
	int i=0;
	mpz_t x,r,d,u,q,z; 
	char * str = malloc(2048*sizeof(char)); 
	mpz_init(r); mpz_init(q);
	mpz_init_set_str(d,"2",10);
	mpz_init_set_str(u,"1",10);
	mpz_init_set_str(z,"0",10);
	mpz_init_set(x,h);
	
	
	while(mpz_cmp(x,z) && (i < 2048))	
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
	expo e = {str, strlen(str)};
	return e;
}


// La variable result sert à stocker le résultat de l'exponentiation rapide pour l'utiliser dans la fonction fermat
// a est l'entier qui porte l'exposant h qui est aussi un entier, n est le modulo de a
void square_multiply(mpz_t a, mpz_t n, mpz_t h, mpz_t result) 
{
	expo e;
	mpz_set(result, a); // Mettre la valeur de a dans result
	
	e = binaire(h);
	printf("Dans square_multiply, str = %s \n", e.str);	 
	
	int i ;
	for (i = e.t-2; i >= 0; i--)
	{
		mpz_mul(result, result, result); // Square
		mpz_mod(result, result, n);
		gmp_printf("Carré de result : %Zd\n", result);
		printf("e.str[%d]= %c \n", i, e.str[i]);
		gmp_printf("Dans la boucle for, i = %d, result = %Zd , e.str[%d]=%c\n", i, result, i, e.str[i]);
		if(e.str[i]=='1') // Si on a un 1 dans l'écriture binaire
		{
			mpz_mul(result, result, a); // Multiply
			mpz_mod(result, result, n);
		}
		gmp_printf("Result = %Zd mod %Zd \n", result, n);
	}
	free(e.str);
}


void fermat(mpz_t n, int k) // n est un grand entier et k est juste un int, c'est le nombre de répétition
{
	printf("%s\n", "entrée dans fonction ok");
	gmp_randstate_t state;
	printf("%s\n", "déclaration state ok");
	gmp_randinit_default(state);
	printf("%s\n", "initialisation state ok");
	
	mpz_t a, result, temp;
	printf("%s\n", "déclaration des mpz_t ok");
	mpz_init(result);
	mpz_init(temp);
	mpz_init(a);
	mpz_sub_ui(temp, n, 1);
	printf("%s\n", "initilisation des mpz_t ok");
	
	int i;
	for (i = 1; i < k; i++)
	{
		printf("%s\n", "entrée en boucle ok");
		mpz_urandomm(a, state, n);
		gmp_printf("%s%Zd\n", "valeur du random créé :", a);
		
		square_multiply(a, temp, n, result); // Calcul de l'exponentielle dans a
		printf("%s\n", "calcul de la valeur de l'entier à tester ok");
		
		if(mpz_cmp_ui(result, 1) != 0) // On cherche à savoir si le random puissance n-1 modulo n est égal à 1
		{
			printf("%s\n", "Composé");
		}
		else printf("%s\n", "Premier1");
	}
	printf("%s\n", "Premier2");
	
	gmp_randclear(state);
	mpz_clear(result);
}

mp_bitcnt_t decomposer(mpz_t tmp, mpz_t t) // tmp : nombre à décomposer (n-1), t : multiple impair
{
	mpz_t div;
	mpz_init_set_str(div, "0", 10);
	mp_bitcnt_t s = mpz_scan1(tmp, 0);
	printf("s1 : %lu\n", s);
	mpz_setbit(div, s); // Mettre le bit s de div à 1
	printf("s1,5 : %lu\n", s);
	mpz_cdiv_q(t, tmp, div); // Trouver t
	gmp_printf("t : %Zd\n", t);
	mpz_clear(div);
	return s;
}

int miller_rabin(mpz_t n, int k)
{
	mpz_t a, y, t, tmp;
	mpz_init(a);
	mpz_init(y);
	mpz_init(t);
	mpz_init(tmp);
	
	int i, j;
	
	mpz_sub_ui(tmp, n, 1); // La décomposition se fait sur n-1 stocké dans tmp
	mp_bitcnt_t s = decomposer(tmp, t); // Appel de la fonction de décomposition de n-1 sous forme (2^s)*t avec t impair
	printf("s2 : %lu\n", s);
	gmp_printf("t2 : %Zd\n", t);
	gmp_randstate_t state; // Création de la graine du random
	gmp_randinit_default(state); //Initalisation de la graine du random
	
	for (i = 1; i < k; i++)
	{
		mpz_urandomm(a, state, n); //Génération du random 0<a<n
		gmp_printf("a : %Zd\n", a);
		square_multiply(a, n, t, y); //Calcul de a^t mod n
		if((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp_ui(y, -1) != 0)) // y!=1 et y!=-1
		{
			s = s - 1;
			printf("s3 : %lu\n", s);
			for (j = 1; j < s; j++)
			{
				printf("s4 : %lu\n", s);
				mpz_mul(y, y, y); //y=y^2
				mpz_mod(y, y, n); //y=y mod n;
				gmp_printf("y : %Zd\n", y);
				if(mpz_cmp_ui(y, 1) == 0)
				{
					printf("%s\n", "Composé1");
					mpz_clear(a);
					mpz_clear(y);
					mpz_clear(t);
					mpz_clear(tmp);
					gmp_randclear(state);
					return 0;
				}
				if(mpz_cmp_ui(y, -1) == 0)
				{
					break; //Arrêter la boucle j et continuer avec le i suivant
				}
				s = s-1;
			}
			printf("%s\n", "Composé2");
			mpz_clear(a);
			mpz_clear(y);
			mpz_clear(t);
			mpz_clear(tmp);
			gmp_randclear(state);
			return 0;
		}		
	}
	printf("%s\n", "Premier");	
	mpz_clear(a);
	mpz_clear(y);
	mpz_clear(t);
	mpz_clear(tmp);
	gmp_randclear(state);
	return 0;
}
