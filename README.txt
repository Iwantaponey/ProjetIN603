DM IN603 - CATTELIN Céline - SEGUENI Julie

On utilise la documentation doxygen pour annoter notre code.

I - Commandes

Compiler le programme : make crypto
Exécuter le programme : ./crypto n k   (avec : n le nombre à tester (grand entier) et k le nombre de répétitions des algorithmes (entier))
Nettoyer tous les fichiers de compilation (fichiers .o) du dossier et les exécutables : make clean

II - Choix de présentation et explications des fonctions

Nous avons divisé notre programme en différents fichiers :
un fichier main.c qui gère l’appel des fonctions et la récupération des paramètres d’exécution entrés au clavier par l’utilisateur.
un fichier fonction.h inclus dans main qui contient les prototypes de nos fonctions implémentées dans le fichier fonction.c.
un fichier fonction.c qui contient le code des fonctions appelées dans le main.

On considère que le nombre 0 n’est pas premier, car il est divisible par tous les nombres positifs donc son nombre de diviseurs est différent de 2.Il en est de même avec le nombre 1 car 1 n’est divisible que par lui-même donc son nombre de diviseurs est différent de 2. On ajoute que si n est compris entre 2 et 4 non inclus alors il est forcément premier. De même si n est pair alors il est forcément composé.
Ainsi, dans ces différents cas énoncés, il est inutile d’appeler les fonctions implémentées dans fonction.c, c’est pourquoi on ne fait qu’un affichage de réponse.

A - Fonction square and multiply

La fonction square_multiply est la première fonction que nous avons implémenté car elle est indispensable pour que fonctionnent les algorithmes de Fermat et de Miller-Rabin.

void square_multiply (mpz_t a, mpz_t h, mpz_t n, mpz_t result);
Avec :
a : grand entier qu’on génère aléatoirement dans les algorithmes de tests de primalité Fermat et Miller-Rabin.
h = (n-1) : grand entier qui est l’exposant dont on va se servir pour savoir quand élever au carré et quand élever au carré puis multiplier.
n  : grand entier dont on veut tester la primalité. C’est le premier argument entré par l’utilisateur. On s’en sert ici pour effectuer le modulo.
result : grand entier qui contiendra le résultat lors de l’exécution de square_multiply.

On fait seulement un square quand on a un 0 dans la décomposition binaire de l'exposant et on fait un square puis un multiply quand on a un 1 dans la décomposition binaire de l'exposant.
On ne doit pas tenir compte du un le plus grand. On prend un binaire qui n'a pas de zéros à gauche donc le plus grand nombre est forcément un 1 (dont on ne tient pas compte ici)

B - Fermat


int fermat (mpz_t n, int k);
Avec :
n : nombre dont on veut tester la primalité.
k : nombre de répétitions du test.

C - Fonction de décomposition 

decomposer(mpz_t tmp, mpz_t t);
Avec :
tmp : nombre à décomposer, il est toujours égal à (n-1) lors de l’entrée dans la fonction.
t : multiple impair que l’on trouve lors de la décomposition, il est égal à 0 lors de l’entrée dans la fonction.

Cette fonction considère que le premier bit à 1 (en allant du bit de poids faible vers le bit de poids fort) est le bit qui vaut la puissance s de la décomposition de de tmp en (2^s)*t. On fabrique donc ensuite un mpz_t div (pour “diviseur” car il va servir pour une division  juste après sa définition) qui sera égal à 2^s. Il suffit ensuite simple de faire la division de mpz_t tmp par mpz_t div pour obtenir t qui sera toujours impair.

D - Miller-Rabin

int miller_rabin(mpz_t n, int k)
Avec :
n : nombre dont on veut tester la primalité.
k : nombre de répétitions du test.

On remplace les comparaison de y = r^t mod n à -1 par des comparaisons à n-1 sinon le code de fonctionne pas puisqu’on aura jamais y = -1 par ordinateur. 
On utilise un booléen bool dans le cas ou le résultat de y = r^t mod n est égal à (n-1) car on ne sait alors pas si le nombre est premier ou pas, c’est pourquoi on effectue des tests suivants en repassant dans la boucle avec le i suivant

Remarque : On observe que lorsqu’on teste la primalité d’un nombre pseudo premier, Miller-Rabin détecte plus rapidement que Fermat que le nombre entré est composé.
