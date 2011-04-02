#include <iostream>
using namespace std;

// Taille de la grille
#define SIZE 9
// Indice du carré correspondant à la case (i,j)
#define square_of(i,j) (j / 3 + 3 * (i / 3))
// Macro pour définir si on peut jouer le nombre k sur la case (i,j)
#define is_okay(i,j,s,k) !(is_member(k, ligne[i]) || is_member(k, colonne[j]) || is_member(k, carre[s]))
// Fonctions ensemblistes : ajout, suppression, et appartenance
#define add(x,e)       (e |=  (1 << x))
#define remove(x,e)    (e &= ~(1 << x))
#define is_member(x,e) (e &   (1 << x))

// Les variables globales
int grille[SIZE][SIZE]; // La grille de jeu
int ligne[SIZE];        // ligne[i]   = ensemble des nombres joués sur la ligne   i
int colonne[SIZE];      // colonne[j] = ensemble des nombres joués sur la colonne j
int carre[SIZE];        // carre[s]   = ensemble des nombres joués sur le carre   s


// Fonction récursive d'exploration
int explore(int i, int j) {
	int new_i, new_j, k, square;
	new_i = i + j / (SIZE - 1);
	new_j = (j + 1) % SIZE;
	// Si on dépassé la dernière ligne, la grille est correctement remplie
	if (i == SIZE)
		return true;
	// Si la case n'est pas déjà remplie ...
	if (grille[i][j] == 0) {
		square = square_of(i,j);
		// Brute-force
		for (k = 1; k <= SIZE; k++) {
			if (is_okay(i, j, square, k)) {
				add(k, ligne[i]);
				add(k, colonne[j]);
				add(k, carre[square]);
				if (explore(new_i, new_j)) {
					grille[i][j] = k;
					return true;
				}
				remove(k, ligne[i]);
				remove(k, colonne[j]);
				remove(k, carre[square]);
			}
		}
		grille[i][j] = 0;
	} else if (explore(new_i, new_j))
		return true;
	return false;
}

int main(void) {
	int i, j, n;
	char c;
	cin >> n;
	while (n > 0) {
		// Initialisation des ensembles ligne/colonne/carre
		for (i = 0; i < SIZE; i++) {
			ligne[i] = 0;
			colonne[i] = 0;
			carre[i] = 0;
		}
		// Lecture de l'entrée
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				cin >> c;
				grille[i][j] = (int) (c - '0');
				// Mise à jour des ensembles ligne/colonne/carre
				if (grille[i][j]) {
					add(grille[i][j], ligne[i]);
					add(grille[i][j], colonne[j]);
					add(grille[i][j], carre[square_of(i,j)]);
				}
			}
		}
		// Affichage du résultat
		if (explore(0, 0))
			for (i = 0; i < SIZE; i++) {
				for (j = 0; j < SIZE; j++) {
					cout << (char) ('0' + grille[i][j]);
				}
				cout << '\n';
			}
		n--;
	}
	return 0;
}
