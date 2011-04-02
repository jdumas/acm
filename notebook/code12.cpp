/********************************************************************************
 * Pivot de Gauss
 *
 * Calcule le determinant d'une matrice carree.
 * Calcule l'inverse d'une matrice carree.
 ********************************************************************************/

#include <vector>
#include <cmath>
using namespace std;

typedef long double elem;
typedef vector<vector<elem> > matrix;

elem inline eabs(elem x) {
	return fabs(x);
}

bool inline zero(elem x) {
	return (eabs(x) < 1e-20);
}

// Echange de deux lignes de la matrice
void swap_line(matrix & m, int i, int j) {
	swap(m[i], m[j]);
	return;
}

// Effectue M[i] <-- M[i] - M[j] * y/x
void sub_line(matrix & m, int i, int j, elem x, elem y) {
	int k;
	for (k = 0; k < (int) m.size(); ++k)
		m[i][k] = m[i][k] - m[j][k] * y / x;
	return;
}

// Effectue M[i] <-- M[i] * x
void mult_line(matrix & m, int i, elem x) {
	int k;
	for (k = 0; k < (int) m.size(); ++k)
		m[i][k] = m[i][k] * x;
	return;
}

elem det(matrix & m) {
	int i, j, n;
	elem d = 1;
	n = m.size();
	for (i = 0; i < n; ++i) {
		// Recherche du plus grand element non nul de la colonne i (entre les lignes i et n-1)
		for (j = i + 1; j < n; ++j) {
			if (zero(m[j][i]))
				continue;
			if (eabs(m[j][i]) > eabs(m[i][i]))
				swap_line(m, i, j);
		}
		// S'il n'y a pas de nombre non nul sur la diagonale, le determinant est nul
		if (zero(m[i][i]))
			return 0;
		d *= m[i][i];
		// Sinon, soustraire la ligne i aux lignes suivantes
		for (j = i + 1; j < n; ++j) {
			sub_line(m, j, i, m[i][i], m[j][i]);
		}
	}
	// Le determinant est alors le produit des elements diagonaux
	return d;
}

// Inverse la matrice m
// Stocke le resultat dans inv, renvoie true ssi m est inversible
bool inverse(matrix & m, matrix & inv) {
	int i, j, n;
	n = m.size();
	inv.clear();
	inv.resize(n, vector<elem> (n, 0));
	// Au debut inv = la matrice identite
	for (i = 0; i < n; ++i)
		inv[i][i] = 1.;
	// On diagonalise la matrice
	for (i = 0; i < n; ++i) {
		// Recherche du plus grand element non nul de la colonne i (entre les lignes i et n-1)
		for (j = i + 1; j < n; ++j) {
			if (zero(m[j][i]))
				continue;
			if (eabs(m[j][i]) > eabs(m[i][i])) {
				swap_line(inv, i, j);
				swap_line(m, i, j);
			}
		}
		// S'il n'y a pas de nombre non nul sur la diagonale, m n'est pas inversible
		if (zero(m[i][i]))
			return false;
		// Sinon, soustraire la ligne i aux autres lignes
		for (j = 0; j < n; ++j) {
			if (i != j) {
				sub_line(inv, j, i, m[i][i], m[j][i]);
				sub_line(m, j, i, m[i][i], m[j][i]);
			}
		}
		// Normalisation
		mult_line(inv, i, 1. / m[i][i]);
		mult_line(m, i, 1. / m[i][i]);
	}
	return true;
}
