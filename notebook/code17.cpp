/********************************************************************************
 * Algorithme de Prim
 * Implementation avec des set
 * Recherche d'arbre couvrant de poids minimum.
 ********************************************************************************/
#include <vector>
#include <set>
using namespace std;

struct edge {
	int from;
	int to;
	int weight;
	edge(void) :
		from(), to(), weight() {}
	edge(int a, int b, int c) :
		from(a), to(b), weight(c) {}
	bool operator<(const edge & e) const {
		return weight < e.weight || (weight == e.weight && (from < e.from
				|| (from == e.from && to < e.to)));
	}
};
typedef vector<vector<edge> > graph;
typedef vector<edge> tree;

// Retourne le poids d'un arbre couvrant de poids minimal + la liste des aretes d'un tel arbre
int prim(graph & g, tree & t) {
	set<edge> Q;
	vector<set<edge>::iterator> old (g.size(), Q.end());
	vector<bool> vu (g.size(), false);
	int i, j, k, s = 0;
	vu[0] = true;
	for (i = 0; i < (int) g[0].size(); ++i) {
		old[g[0][i].to] = Q.insert(g[0][i]).first;
	}
	while (not Q.empty()) {
		t.push_back(*Q.begin());
		i = Q.begin()->to;
		s += Q.begin()->weight;
		vu[i] = true;
		Q.erase(Q.begin());
		for (k = 0; k < (int) g[i].size(); ++k) {
			j = g[i][k].to;
			if (not vu[j] && (old[j] == Q.end() || old[j]->weight > g[i][k].weight)) {
				// Mise a jour de l'element "j" en temps log(n)
				if (old[j] != Q.end())
					Q.erase(old[j]);
				old[j] = Q.insert(g[i][k]).first;
			}
		}
	}
	return s;
}
