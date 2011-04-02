/********************************************************************************
 * Algorithme de Dijkstra
 * Implementation avec des set
 *
 * Recherche de plus court chemin entre une source et tous les sommets du graphe.
 * Restriction : les aretes doivent avoir des poids positifs.
 * Complexite  : temporelle O(m*log(n)), spatiale O(n)
 ********************************************************************************/
#include <vector>
#include <set>
#include <climits>
using namespace std;

struct edge {
	int to;
	int weight;
	edge(void) :
		to(), weight() {}
	edge(int a, int b) :
		to(a), weight(b) {}
};
typedef vector<vector<edge> > graph;

// pred[i] = predecesseur de "i" dans un plus court chemin de "source" a "i"
// dist[i] = longueur d'un tel plus court chemin
void dijsktra(graph & g, vector<int> & pred, vector<int> & dist, int source) {
	set<pair<int, int> > Q;
	int i, j, k, cost;
	dist.clear();
	dist.resize(g.size(), INT_MAX);
	pred.resize(g.size(), -1);
	dist[source] = 0;
	pred[source] = source;
	Q.insert(make_pair(0, source));
	while (not Q.empty()) {
		i = Q.begin()->second;
		Q.erase(Q.begin());
		for (k = 0; k < (int) g[i].size(); ++k) {
			j = g[i][k].to;        // Voisin de "i"
			cost = g[i][k].weight; // Poids de l'arete (i,j)
			if (dist[j] > dist[i] + cost) {
				// Mise a jour de l'element "j" en temps log(n)
				Q.erase(make_pair(dist[j], j));
				dist[j] = dist[i] + cost;
				pred[j] = i;
				Q.insert(make_pair(dist[j], j));
			}
		}
	}
	return;
}
