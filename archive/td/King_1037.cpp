#include <iostream>
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

bool bellman(edges & e, vector<int> & d, int borne, int source) {
	int i, k = 0;
	bool changed = true;
	d[source] = 0;
	k = 0;
	// On itère au plus n fois
	while (changed) {
		if (k >= borne) break;
		changed = false;
		for (i = 0; i < (int) e.size(); ++i) {
			if (d[e[i].x] != INT_MAX && d[e[i].y] > d[e[i].x] + e[i].w) {
				d[e[i].y] = d[e[i].x] + e[i].w;
				changed = true;
			}
		}
		++k;
	}
	return changed;
}

int main(void) {
	int x, i, j, k, n, m;
	vector<int> dist;
	edges adj;
	string s;
	while (1) {
		cin >> n >> m;
		if (n == 0) break;
		// Ajout d'un sommet bidon x1
		for (x = 1; x <= n + 1; ++x) {
			adj.push_back(edge(0, x, 0));
		}
		// Ajout des arêtes pour les contraintes entre x2 ... xn
		for (x = 0; x < m; ++x) {
			cin >> i >> j >> s >> k;
			if (s == "lt")
				adj.push_back(edge(i, i + j + 1, k - 1));
			else
				adj.push_back(edge(i + j + 1, i, -k - 1));
		}
		n += 2;
		dist.resize(n, INT_MAX);
		cout << (bellman(adj, dist, n, 0) ? "successful conspiracy"
				: "lamentable kingdom") << endl;
		dist.clear();
		adj.clear();
	}
	return 0;
}
