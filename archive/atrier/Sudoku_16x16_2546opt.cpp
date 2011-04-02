//#include <iostream>
#include <cstdio>
using namespace std;
#define square_of(i,j) (j / 4 + 4 * (i / 4))
#define next(i,j) i + (j + 1 == SIZE),(j + 1) % SIZE
#define SIZE 16

unsigned int grille[SIZE][SIZE];
unsigned int ligne[SIZE];
unsigned int colonne[SIZE];
unsigned int carre[SIZE];
unsigned int all_free = (1 << SIZE) - 1;

int explore(int i, int j) {
	unsigned int masque, libres, square;
	if (i == SIZE)
		return true;
	if (grille[i][j])
		return explore(next(i,j));
	square = square_of(i,j);
	libres = ligne[i] & colonne[j] & carre[square];
	masque = 1;
	while (libres) {
		if (libres & 1) {
			ligne[i]      &= ~masque;
			colonne[j]    &= ~masque;
			carre[square] &= ~masque;
			if (explore(next(i,j))) {
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
	int i, j;
	char c;
	for (i = 0; i < SIZE; i++) {
		ligne[i] = all_free;
		colonne[i] = all_free;
		carre[i] = all_free;
	}
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			scanf("%c", &c);
			if (c == '-')
				grille[i][j] = 0;
			else {
				grille[i][j] = 1 << (int) (c - 'A');
				ligne[i]              &= ~grille[i][j];
				colonne[j]            &= ~grille[i][j];
				carre[square_of(i,j)] &= ~grille[i][j];
			}
		}
		scanf("\n");
	}
	if (explore(0, 0))
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				c = '@';
				while (grille[i][j]) {
					c++;
					grille[i][j] >>= 1;
				}
				printf("%c", c);
			}
			printf("\n");
		}
	return 0;
}
