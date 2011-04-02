#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long double elem;
typedef vector<vector<elem> > matrix;

// Affiche la matrice (débugage)
void print(matrix & m) {
	int i, j;
	for (i = 0; i < (int) m.size(); ++i) {
		for (j = 0; j < (int) m[0].size(); ++j)
			cout << m[i][j] << ";";
		cout << endl;
	}
	cout << endl;
}

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

elem det(matrix & m) {
	int i, j, n;
	n = m.size();
	elem d = 1;
	for (i = 0; i < n; ++i) {
		// Recherche du plus grand élément non nul de la colonne i (entre les lignes i et n-1)
		for (j = i + 1; j < n; ++j) {
			if (zero(m[j][i])) continue;
			if (eabs(m[j][i]) > eabs(m[i][i]))
				swap_line(m, i, j);
		}
		// S'il n'y a pas de nombre non nul sur la diagonale, le déterminant est nul
		if (zero(m[i][i])) return 0;
		d *= m[i][i];
		// Sinon, soustraire la ligne i aux lignes suivantes
		for (j = i + 1; j < n; ++j) {
			sub_line(m, j, i, m[i][i], m[j][i]);
		}
	}
	// Le déterminant est alors le produit des éléments diagonaux
	return d;
}

int main(void) {
	matrix m;
	int p, k, i, j, n;
	while (cin >> n >> p >> k) {
		// Réinitialiser m.
		m.clear();
		m.resize(n, vector<elem> (n, -1));
		// Au départ m contient des -1 partout sauf sur la diagonale
		for (i = 0; i < n; ++i)
			m[i][i] = n - 1;
		for (; p; --p) {
			cin >> i >> j;
			--i; --j;
			if (m[i][j] == 0) continue;
			// Quand on rencontre une arête, on met la case correspondante à 0
			m[i][j] = 0;
			m[j][i] = 0;
			// Et on décrémente le degré de chaque sommet incident
			--m[i][i];
			--m[j][j];
		}
		// On enlève une ligne/colonne à la matrice : la première par exemple
		for (i = 1; i < n; ++i) {
			m[i][0] = 0;
			m[0][i] = 0;
		}
		m[0][0] = 1;
		// On renvoie le déterminant calculé
		cout << (long long) roundl(eabs(det(m))) << endl;
	}
	return 0;
}
