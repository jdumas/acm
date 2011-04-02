/********************************************************************************
 * Algorithme de Roy-Warshall
 *
 * Recherche de plus court chemin entre tout couple de sommets.
 * Detection de circuits absorbants, poids negatifs possibles.
 * Complexite : O(n^3)
 ********************************************************************************/

#include <vector>
#include <climits>
using namespace std;

typedef vector<vector<int> > matrix;

// Renvoie true ssi il y a un circuit absorbant
// Matrice des successeurs sur un chemin de i a j --> r
bool roy_warshall(matrix & g, matrix & r) {
	int i, j, k, n = g.size();
	// Initialisation de la table de routage
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			r[i][j] = (g[i][j] == INT_MAX ? i : j);
	// Algorithme principal
	for (k = 0; k < n; ++k)
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j) {
				if (g[i][k] == INT_MAX) continue;
				if (g[k][j] == INT_MAX) continue;
				if (g[i][k] + g[k][j] >= g[i][j]) continue;
				g[i][j] = g[i][k] + g[k][j];
				r[i][j] = r[i][k];
			}
	// Detection des circuits absorbant
	for (i = 0; i < n; ++i)
		if (g[i][i] < 0)
			return true;
	return false;
}
