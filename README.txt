DM IN603 - CATTELIN C�line - SEGUENI Julie

On utilise la documentation doxygen pour annoter notre code.

I - Commandes

Compiler le programme : make crypto
Ex�cuter le programme : ./crypto n k   (avec : n le nombre � tester (grand entier) et k le nombre de r�p�titions des algorithmes (entier))
Nettoyer tous les fichiers de compilation (fichiers .o) du dossier et les ex�cutables : make clean

II - Choix de pr�sentation et explications des fonctions

Nous avons divis� notre programme en diff�rents fichiers :
un fichier main.c qui g�re l�appel des fonctions et la r�cup�ration des param�tres d�ex�cution entr�s au clavier par l�utilisateur.
un fichier fonction.h inclus dans main qui contient les prototypes de nos fonctions impl�ment�es dans le fichier fonction.c.
un fichier fonction.c qui contient le code des fonctions appel�es dans le main.

On consid�re que le nombre 0 n�est pas premier, car il est divisible par tous les nombres positifs donc son nombre de diviseurs est diff�rent de 2.Il en est de m�me avec le nombre 1 car 1 n�est divisible que par lui-m�me donc son nombre de diviseurs est diff�rent de 2. On ajoute que si n est compris entre 2 et 4 non inclus alors il est forc�ment premier. De m�me si n est pair alors il est forc�ment compos�.
Ainsi, dans ces diff�rents cas �nonc�s, il est inutile d�appeler les fonctions impl�ment�es dans fonction.c, c�est pourquoi on ne fait qu�un affichage de r�ponse.

A - Fonction square and multiply

La fonction square_multiply est la premi�re fonction que nous avons impl�ment� car elle est indispensable pour que fonctionnent les algorithmes de Fermat et de Miller-Rabin.

void square_multiply (mpz_t a, mpz_t h, mpz_t n, mpz_t result);
Avec :
a : grand entier qu�on g�n�re al�atoirement dans les algorithmes de tests de primalit� Fermat et Miller-Rabin.
h = (n-1) : grand entier qui est l�exposant dont on va se servir pour savoir quand �lever au carr� et quand �lever au carr� puis multiplier.
n  : grand entier dont on veut tester la primalit�. C�est le premier argument entr� par l�utilisateur. On s�en sert ici pour effectuer le modulo.
result : grand entier qui contiendra le r�sultat lors de l�ex�cution de square_multiply.

On fait seulement un square quand on a un 0 dans la d�composition binaire de l'exposant et on fait un square puis un multiply quand on a un 1 dans la d�composition binaire de l'exposant.
On ne doit pas tenir compte du un le plus grand. On prend un binaire qui n'a pas de z�ros � gauche donc le plus grand nombre est forc�ment un 1 (dont on ne tient pas compte ici)

B - Fermat


int fermat (mpz_t n, int k);
Avec :
n : nombre dont on veut tester la primalit�.
k : nombre de r�p�titions du test.

C - Fonction de d�composition 

decomposer(mpz_t tmp, mpz_t t);
Avec :
tmp : nombre � d�composer, il est toujours �gal � (n-1) lors de l�entr�e dans la fonction.
t : multiple impair que l�on trouve lors de la d�composition, il est �gal � 0 lors de l�entr�e dans la fonction.

Cette fonction consid�re que le premier bit � 1 (en allant du bit de poids faible vers le bit de poids fort) est le bit qui vaut la puissance s de la d�composition de de tmp en (2^s)*t. On fabrique donc ensuite un mpz_t div (pour �diviseur� car il va servir pour une division  juste apr�s sa d�finition) qui sera �gal � 2^s. Il suffit ensuite simple de faire la division de mpz_t tmp par mpz_t div pour obtenir t qui sera toujours impair.

D - Miller-Rabin

int miller_rabin(mpz_t n, int k)
Avec :
n : nombre dont on veut tester la primalit�.
k : nombre de r�p�titions du test.

On remplace les comparaison de y = r^t mod n � -1 par des comparaisons � n-1 sinon le code de fonctionne pas puisqu�on aura jamais y = -1 par ordinateur. 
On utilise un bool�en bool dans le cas ou le r�sultat de y = r^t mod n est �gal � (n-1) car on ne sait alors pas si le nombre est premier ou pas, c�est pourquoi on effectue des tests suivants en repassant dans la boucle avec le i suivant

Remarque : On observe que lorsqu�on teste la primalit� d�un nombre pseudo premier, Miller-Rabin d�tecte plus rapidement que Fermat que le nombre entr� est compos�.
