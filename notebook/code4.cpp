/********************************************************************************
 * Union-Find ; Algorithme de Kruskal
 *
 * Recherche d'arbre couvrant de poids minimum.
 ********************************************************************************/
#include <vector>
#include <algorithm>
using namespace std;
// Structure d'union-find
vector<int> pere;

void init(int n) {
	int i;
	pere.resize(n);
	for (i = 0; i < n; ++i)
		pere[i] = i;
	return;
}
int find(int i) {
	if (pere[i] == i) return i;
	pere[i] = find(pere[i]);
	return pere[i];
}
void merge(int i, int j) {
	pere[find(i)] = find(j);
	return;
}

// Algorithme de Kruskal
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
typedef vector<edge> tree;
typedef vector<edge> adj;

void kruskal(adj & e, tree & t, int n) {
	int i;
	init(n);
	sort(e.begin(), e.end());
	for (i = 0; i < (int) e.size(); ++i) {
		if (find(e[i].x) != find(e[i].y)) {
			t.push_back(e[i]);
			merge(e[i].x, e[i].y);
		}
	}
}
