#include <cstdio>
using namespace std;

char grille[9][9];
short masque = (1 << 9) - 1;

int valide_point(char i, char j) {
	char ic = (i / 3) * 3, jc = (j / 3) * 3;
	char p = 0, k, l;
	short v = 0;
	for (k = 0; k < 3; k++) {
		for (l = 0; l < 3; l++) {
			v |= (1 << grille[p][j]);
			v |= (1 << grille[i][p]);
			v |= (1 << grille[ic + k][jc + l]);
			p++;
		}
	}
	v >>= 1;
	v = masque & ~v;
	return v;
}

// Backtracking
bool solve(char i, char j) {
	char js = (j + 1) % 9, is = i + (j / 8);
	if (i == 9)
		return true;
	if (grille[i][j] != 0) {
		return solve(is, js);
	} else {
		short libres;
		libres = valide_point(i, j);
		grille[i][j] = 1;
		// On va forcer un peu !
		while (libres) {
			if (libres & 1) {
				if (solve(is, js))
					return true;
			}
			libres >>= 1;
			grille[i][j]++;
		}
		grille[i][j] = 0;
	}
	return false;
}

int main() {
	int n, i, j;
	char ch;
	// Nombre de grille
	scanf("%d\n", &n);
	// Pour les x grilles, on résout
	for (; n > 0; n--) {
		// Initialisation
		for (j = 0; j < 9; j++) {
			for (i = 0; i < 9; i++) {
				scanf("%c", &ch);
				grille[i][j] = ch - '0';
			}
			scanf("\n");
		}
		solve(0, 0);
		// Affichage du résultat
		for (int j = 0; j <= 8; j++) {
			for (int i = 0; i <= 8; i++) {
				printf("%d", grille[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}
