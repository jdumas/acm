#include <cstdio>
#include <iostream>
using namespace std;

#define get_libres(i,j) row[i] & col[j] & sqr[((i) & ~3) + ((j) & 3)]
#define get_num_pos(mask) num_of_pos_8[(mask) & 0xff] + num_of_pos_8[(mask) >> 8 & 0xff]
#define get_sqr(i,j) (((i) & ~3u) + ((j) & 3u))

unsigned char grille[16][16];
unsigned short row[16];
unsigned short col[16];
unsigned short sqr[16];

unsigned char const num_of_pos_8[256] = {
   0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
   4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};

bool solve(void);

// Initialisation de la grille
void initialize(void) {
	unsigned char i, j;
	for (i = 0; i < 16; i++) {
		row[i] = 0;
		col[i] = 0;
		sqr[i] = 0;
	}
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			row[i]				|= 1 << grille[i][j];
			col[j]				|= 1 << grille[i][j];
			sqr[get_sqr(i,j)]	|= 1 << grille[i][j];
		}
	}
	for (i = 0; i < 16; i++) {
		row[i] = ~row[i];
		col[i] = ~col[i];
		sqr[i] = ~sqr[i];
	}
	return;
}

// Choix de la case où backtracker
void choose_number(unsigned char &imin, unsigned char &jmin) {
	unsigned char i, j, nb_pos, min_pos = -1;
	unsigned short libres;
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			printf("%d, %d ;", grille[i][j], 0xff);
			if (grille[i][j] != 0xff)
				continue;
			libres = get_libres(i,j);
			nb_pos = get_num_pos(libres);
			if (nb_pos < min_pos) {
				imin = i;
				jmin = j;
				min_pos = nb_pos;
			}
		}
	}
	return;
}

void slice(unsigned char i, unsigned char j, unsigned short &libres) {
	unsigned char k, ic = i & ~3u, jc = j & ~3u;
	unsigned short mask = 0xffff;
	for (k = 0; k < 4; k++) {
		if (ic+k != i)
			mask &= ~row[ic+k];
		if (jc+k != j)
			mask &= ~col[jc+k];
	}
	if (mask != 0)
		libres &= mask;
	return;
}

inline bool affecte(unsigned char i, unsigned char j, unsigned short mask) {
	row[i]				&= ~mask;
	col[j]				&= ~mask;
	sqr[get_sqr(i,j)]	&= ~mask;
	if (solve())
		return true;
	row[i]				|= mask;
	col[j]				|= mask;
	sqr[get_sqr(i,j)]	|= mask;
	return false;
}

// Backtracking
bool solve(void) {
	/*if (filtre())
		return true;*/
	unsigned char i = -1, j = -1;
	choose_number(i, j);
	if (i == -1)
		return true;
	unsigned short libres = get_libres(i,j);
	unsigned short current = 1u;
	grille[i][j] = 0;
	// On va forcer un peu !
	while (libres) {
		if (libres & 1) {
			row[i] &= ~current;
			col[j] &= ~current;
			sqr[get_sqr(i,j)] &= ~current;
			if (solve())
				return true;
			row[i] |= current;
			col[j] |= current;
			sqr[get_sqr(i,j)] |= current;
		}
		libres  >>= 1;
		current <<= 1;
		grille[i][j]++;
	}
	grille[i][j] = 0xff;
	return false;
}

int main() {
	unsigned char ch, i, j;
	// Initialisation
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			scanf("%c", &ch);
			grille[i][j] = (ch == '-' ? 0xff : ch - 'A');
		}
		scanf("\n");
	}
	initialize();
	solve();
	// Affichage du résultat
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			printf("%c", 'A' + grille[i][j]);
		}
		printf("\n");
	}
	return 0;
}
