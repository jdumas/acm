/********************************************************************************
 * Nombre d'arbres couvrants d'un graphe
 *
 * Soit A la matrice d'adjacence du graphe (avec des A[i][j] = 1 ssi (i,j) est une arete),
 * D la matrice diagonale contenant les degres des sommets (D[i][i] = deg(i) et 0 ailleurs).
 * On note alors Q = D-A.
 *
 * On peut montrer que le nombre d'arbres couvrants de G est alors la valeur absolue du
 * determinant d'un des cofacteurs de Q (obtenu en supprimant une ligne et une colonne de Q).
 *
 * L'algorithme utilise pour le calcul du determinant est celui du pivot de Gauss :
 *
 * ⋅ Pour i = 0 a n-1 faire
 *     ⋅ Trouver une ligne j telle que Q[j][i] != 0
 *     ⋅ Inverser les lignes i et j
 *     ⋅ Pour j = i+1 a n-1 faire
 *         ⋅ Soit x = Q[j][i] / Q[i][i]
 *         ⋅ Faire l'operation Q[j] ← Q[j] - x * Q[i]
 *     ⋅ Fin pour
 * ⋅ Fin pour
 * ⋅ Renvoyer le produit des elements diagonaux de Q
 ********************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long double elem;
typedef vector<vector<elem> > matrix;

elem inline eabs(elem x) {
	return fabs(x);
}


int main(void) {
	matrix m;
	int p, k, i, j, n;
	while (cin >> n >> p >> k) {
		// Reinitialiser m.
		m.clear();
		m.resize(n, vector<elem> (n, -1));
		// Au depart m contient des -1 partout sauf sur la diagonale
		for (i = 0; i < n; ++i)
			m[i][i] = n - 1;
		for (; p; --p) {
			cin >> i >> j;
			--i; --j;
			if (m[i][j] == 0) continue;
			// Quand on rencontre une arete, on met la case correspondante a 0
			m[i][j] = 0;
			m[j][i] = 0;
			// Et on decremente le degre de chaque sommet incident
			--m[i][i];
			--m[j][j];
		}
		// On enleve une ligne/colonne a la matrice : la premiere par exemple
		for (i = 1; i < n; ++i) {
			m[i][0] = 0;
			m[0][i] = 0;
		}
		m[0][0] = 1;
		// On renvoie le determinant calcule (det = fonction qui calcule le determinant !!)
		cout << (long long) roundl(eabs(det(m))) << endl;
	}
	return 0;
}
