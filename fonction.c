#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <string.h>

void binaire(mpz_t bin, mpz_t h)
{
	int i=0,j=0,k;
	mpz_t x,r,d,u,q,z; char * str=malloc(2048*sizeof(char)); 
	mpz_init(r); mpz_init(q);
	mpz_init_set_str(d,"2",10);
	mpz_init_set_str(u,"1",10);
	mpz_init_set_str(z,"0",10);
	mpz_init_set(x,h);
	gmp_printf(" avant boucle r = %Zd \n",r);
	gmp_printf("x = %Zd \n",x);
	gmp_printf("d = %Zd \n",d);
	gmp_printf("q = %Zd \n",q);
	
	
	while(mpz_cmp(x,z) && i<2048)	
	{	
		mpz_fdiv_r(r,x,d);
		mpz_fdiv_q(q,x,d);
		gmp_printf(" boucle r = %Zd \n",r);
		gmp_printf("x = %Zd \n",x);
		gmp_printf("d = %Zd \n",d);
		gmp_printf("q = %Zd \n",q);
		if(!mpz_cmp(r,u))
			str[i]='1';
		else 
			str[i]='0';
		mpz_set(x,q);
		i++;
	}
	printf("str = %s \n", str);
	printf("i= %d \n", i);
	char * str2=malloc(strlen(str)*sizeof(char));
	j=0;
	for (k=strlen(str)-1; k>-1; k--)
	{
		printf(" str[%d]= %c \n",k, str[k]);
		str2[j]=str[k];
		printf(" str2[%d]= %c \n",j, str[j]);
		++j;
	}
	printf("str2 = %s \n", str2);
	mpz_set_str(bin,str2,10);
	mpz_clear(d);
	mpz_clear(q);
	mpz_clear(u);
	mpz_clear(x);
	mpz_clear(r);
	free(str);
	free(str2);
}


void square_multiply(mpz_t a, mpz_t n, mpz_t h)
{
	mpz_t result,bin;
	mpz_init(result);
	mpz_init(bin);
	binaire(bin,h);
	mpz_set(result, a);
	gmp_printf("bin = %Zd \n", bin);
	mpz_clear(result);
}



void fermat(mpz_t n, mpz_t k)
{
	
	
}

void miller_rabin(mpz_t n, mpz_t k)
{

	
}
