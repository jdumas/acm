/********************************************************************************
 * Algorithme de Prim
 *
 * Recherche d'arbre couvrant de poids maximum, version avec des priority_queue.
 ********************************************************************************/

#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct edge {
	int x, y, w;
	edge(void): x(),y(),w() {};
	edge(int a, int b, int c): x(a), y(b), w(c) {}
	bool operator< (const edge & e) const {
		return w < e.w; // Attention, changer "<" en ">" pour obtenir un arbre couvrant de poids minimal.
	}
};

typedef vector<vector<edge> > graph;
typedef vector<edge> tree;

// Retourne le poids d'un arbre couvrant de poids maximal + la liste des aretes d'un tel arbre
int prim(graph & g, tree & t) {
	priority_queue<edge> file;
	vector<bool> vu (g.size(), false);
	edge e;
	int i,s = 0;
	vu[0] = true;
	for (i = 0; i < (int) g[0].size(); ++i)
		file.push(g[0][i]);
	while (!file.empty()) {
		e = file.top();
		file.pop();
		if (vu[e.y]) continue;
		// Ajout de l'arete "e"
		t.push_back(e);
		s += e.w;
		vu[e.y] = true;
		// Parcours des voisins de "y"
		for (i = 0; i < (int) g[e.y].size(); ++i)
			file.push(g[e.y][i]);
	}
	return s;
}
