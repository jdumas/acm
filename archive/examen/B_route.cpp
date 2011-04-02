#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <climits>
using namespace std;

struct edge {
	int x, y, w, id;
	edge(void) : x(), y(), w(), id() {}
	edge(int a, int b, int c, int d) :
		x(a), y(b), w(c), id(d) {}
	bool operator<(const edge & e) const {
		// Attention, on met un “>” car le top d'une file de priorité est le plus grand élément
		// pour la relation considérée (et donc ici une arête de poids minimum).
		return w > e.w;
	}
};

typedef vector<vector<edge> > graph;
typedef vector<int> tab;

void dijsktra(graph & g, tab & dist, int source) {
	vector<bool> vu(g.size(), false);
	priority_queue<edge> file;
	edge e, f;
	int i = 0;
	file.push(edge(source, source, 0, 0));
	while (!file.empty()) {
		e = file.top();
		file.pop();
		if (vu[e.y]) continue;
		// La distance de source à e.y est la bonne
		dist[e.y] = e.w;
		vu[e.y] = true;
		// Parcours des voisins de e.y
		for (i = 0; i < (int) g[e.y].size(); ++i) {
			f = g[e.y][i];
			f.w += e.w;
			if (dist[f.y] > f.w)
				file.push(f);
		}
	}
	return;
}

int main(void) {
	graph g1, g2;
	tab d1, d2;
	vector<int> ok;
	int n, m, k, i, j, d, p;
	edge e;
	// Initialisation
	cin >> n >> m >> k;
	g1.resize(n);
	g2.resize(n);
	d1.resize(n, INT_MAX);
	d2.resize(n, INT_MAX);
	ok.resize(m, false);
	for (p = 0; p < m; ++p) {
		cin >> i >> j >> d;
		--i, --j;
		g1[i].push_back(edge(i, j, d, p));
		g2[j].push_back(edge(j, i, d, p));
	}
	// Calcul des distances
	dijsktra(g1, d1, 0);
	dijsktra(g2, d2, n - 1);
	// Ajout des arêtes
	p = 0;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < (int) g1[i].size(); ++j) {
			e = g1[i][j];
			if (not ok[e.id] && // Arête non visités
					d1[e.x] != INT_MAX && // x atteignable depuis 0
					d2[e.y] != INT_MAX && // y atteignable depuis n-1
					abs(d1[e.x] + d2[e.y] + e.w - d1[n - 1]) <= k) // La route x->y convient
			{ ok[e.id] = true; ++p; }
		}
	}
	// Affichage du résultat
	cout << p << endl;
	for (i = 0; i < m; ++i) {
		if (ok[i])
			cout << i + 1 << endl;
	}
	return 0;
}
