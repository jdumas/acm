#include <cstdio>
using namespace std;

char grille[16][16];

int valide_point(char i, char j) {
	char ic = i & ~3, jc = j & ~3;
	char p = 0, k, l;
	short v = 0;
	for (k = 0; k < 4; k++) {
		for (l = 0; l < 4; l++) {
			if (grille[p][j] != -1)
				v |= (1 << grille[p][j]);
			if (grille[i][p] != -1)
				v |= (1 << grille[i][p]);
			if (grille[ic + k][jc + l] != -1)
				v |= (1 << grille[ic + k][jc + l]);
			p++;
		}
	}
	return ~v;
}

// Backtracking
bool solve(char i, char j) {
	char js = (j + 1) & 15;
	char is = i + (js == 0);
	if (i == 16)
		return true;
	if (grille[i][j] != -1) {
		return solve(is, js);
	} else {
		short libres;
		libres = valide_point(i, j);
		grille[i][j] = 0;
		// On va forcer un peu !
		while (libres) {
			if (libres & 1) {
				if (solve(is, js))
					return true;
			}
			libres >>= 1;
			grille[i][j]++;
		}
		grille[i][j] = -1;
	}
	return false;
}

void first_pass(char i, char j) {
	if (i == 16)
		return;
	if (grille[i][j] == -1) {
		short libres;
		libres = valide_point(i, j);
		grille[i][j] = 0;
		// On va forcer un peu !
		while (libres) {
			if (libres == 1) {
				first_pass(0, 0);
				return;
			}
			libres >>= 1;
			grille[i][j]++;
		}
		grille[i][j] = -1;
	}
	first_pass(i + j / 15, (j + 1) & 15);
	return;
}

int main() {
	int i, j;
	char ch;
	// Initialisation
	for (j = 0; j < 16; j++) {
		for (i = 0; i < 16; i++) {
			scanf("%c", &ch);
			if (ch == '-')
				grille[i][j] = -1;
			else
				grille[i][j] = ch - 'A';
		}
		scanf("\n");
	}
	first_pass(0, 0);
	solve(0, 0);
	// Affichage du résultat
	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < 16; i++) {
			printf("%c", 'A' + grille[i][j]);
		}
		printf("\n");
	}
	return 0;
}
