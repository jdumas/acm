#include <cstdio>
using namespace std;
// Quelques macros
#define square_of(i,j) (j / 3 + 3 * (i / 3))
#define SIZE 9

unsigned int grille[SIZE][SIZE]; // La grille de jeu
unsigned int ligne[SIZE];  // ligne[i]   = ensemble des nombres disponibles pour la ligne   i
unsigned int colonne[SIZE];// colonne[j] = ensemble des nombres disponibles pour la colonne j
unsigned int carre[SIZE];  // carre[s]   = ensemble des nombres disponibles pour le carre   s
unsigned int all_free = (1 << SIZE) - 1; // Constante représentant l'ensemble {0,...,SIZE-1}


int explore(int i, int j) {
	unsigned int masque, libres, square;
	int next_i = i + (j + 1 == SIZE), next_j = (j + 1) % SIZE;
	// Si on dépassé la dernière ligne, la grille est correctement remplie
	if (i == SIZE)
		return true;
	// Si la case est déjà remplie, on passe à la suivante
	if (grille[i][j])
		return explore(next_i,next_j);
	square = square_of(i,j);
	libres = ligne[i] & colonne[j] & carre[square];
	masque = 1;
	while (libres) {
		if (libres & 1) {
			ligne[i]      &= ~masque;
			colonne[j]    &= ~masque;
			carre[square] &= ~masque;
			if (explore(next_i,next_j)) {
				grille[i][j] = masque;
				return true;
			}
			ligne[i]      |= masque;
			colonne[j]    |= masque;
			carre[square] |= masque;
		}
		masque <<= 1;
		libres >>= 1;
	}
	grille[i][j] = 0;
	return false;
}

int main(void) {
	int i, j, n;
	char c;
	scanf("%d\n", &n);
	while (n > 0) {
		// Initialisation des ensembles ligne/colonne/carre
		for (i = 0; i < SIZE; i++) {
			ligne[i]   = all_free;
			colonne[i] = all_free;
			carre[i]   = all_free;
		}
		// Lecture de l'entrée
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				scanf("%c", &c);
				if (c == '0')
					grille[i][j] = 0;
				else {
					grille[i][j] = 1 << (int) (c - '1');
					// Mise à jour des ensembles ligne/colonne/carre
					ligne[i]              &= ~grille[i][j];
					colonne[j]            &= ~grille[i][j];
					carre[square_of(i,j)] &= ~grille[i][j];
				}
			}
			scanf("\n");
		}
		// Affichage du résultat
		if (explore(0, 0))
			for (i = 0; i < SIZE; i++) {
				for (j = 0; j < SIZE; j++) {
					c = '0';
					while (grille[i][j]) {
						c++;
						grille[i][j] >>= 1;
					}
					printf("%c",c);
				}
				printf("\n");
			}
		n--;
	}
	return 0;
}
