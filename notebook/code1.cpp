/********************************************************************************
* Algorithme de Dijkstra
*
* Recherche de plus court chemin entre une source et tous les sommets du graphe.
* Restriction : les aretes doivent avoir des poids positifs.
* Complexite  : temporelle O(m*log(n)), spatiale O(m)
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
		// Attention, on met un ">" car le top d'une file de priorite est le plus grand element
		// pour la relation consideree (et donc ici une arete de poids minimum).
		return w > e.w;
	}
};
typedef vector<vector<edge> > graph;

void dijsktra(graph & g, vector<int> & pere, vector<int> & dist, int source) {
	priority_queue<edge> file;
	vector<bool> vu (g.size(), false);
	edge e,f;
	int i = 0;
	dist.clear();
	dist.resize(g.size(), INT_MAX);
	file.push(edge(source,source,0));
	while (!file.empty()) {
		e = file.top();
		file.pop();
		if (vu[e.y]) continue;
		// La distance de source a e.y est la bonne
		pere[e.y] = e.x;
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
