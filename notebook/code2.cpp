/********************************************************************************
 * Algorithme de Bellman-Ford
 *
 * Recherche de plus court chemin entre une source et tous les sommets du graphe.
 * Detection de circuits absorbants, poids negatifs possibles.
 * Complexite : O(n*m)
 ********************************************************************************/

#include <vector>
#include <climits>
using namespace std;

struct edge {
	int x, y, w;
	edge(void) :
		x(), y(), w() {}
	edge(int a, int b, int c) :
		x(a), y(b), w(c) {}
	bool operator<(const edge & e) const {
		return w < e.w;
	}
};

typedef vector<edge> edges;

// Renvoie true ssi il y a un circuit absorbant
// Tableau des predecesseurs sur un chemin de la source a i --> pred
bool bellman(edges & e, vector<int> & d, vector<int> pred, int borne, int source) {
	int i, k = 0;
	bool changed = true;
	d[source] = 0;
	for (k = 0; changed && k < borne; ++k) {
		changed = false;
		for (i = 0; i < (int) e.size(); ++i) {
			if (d[e[i].x] != INT_MAX && d[e[i].y] > d[e[i].x] + e[i].w) {
				d[e[i].y] = d[e[i].x] + e[i].w;
				pred[e[i].y] = e[i].x;
				changed = true;
			}
		}
	}
	return changed;
}
