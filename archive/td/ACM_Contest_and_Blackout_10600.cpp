#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct edge {
	int x, y, w;
	edge(void) :
		x(), y(), w() {}
	edge(int a, int b, int c) :
		x(a), y(b), w(c) {}
	bool operator<(const edge & e) const {
		return w > e.w;
	}
};

typedef vector<vector<edge> > graph;
typedef vector<edge> tree;

int x0, y0;

int prim(graph & g, tree & t) {
	priority_queue<edge> file;
	vector<bool> vu(g.size(), false);
	edge e;
	int i, s = 0;
	vu[0] = true;
	for (i = 0; i < (int) g[0].size(); ++i)
		file.push(g[0][i]);
	while (!file.empty()) {
		e = file.top();
		file.pop();
		if (e.x == x0 && e.y == y0) continue;
		if (vu[e.y]) continue;
		// Ajout de l'arête “e”
		t.push_back(e);
		s += e.w;
		vu[e.y] = true;
		// Parcours des voisins de “y”
		for (i = 0; i < (int) g[e.y].size(); ++i)
			file.push(g[e.y][i]);
	}
	return s;
}

void compute(graph & g) {
	int r0, r1 = INT_MAX, r2 = 0;
	int i, n = g.size();
	tree t, tmp;
	x0 = -1;
	y0 = -1;
	r0 = prim(g, t);
	for (i = 0; i < (int) t.size(); ++i) {
		x0 = t[i].x;
		y0 = t[i].y;
		r2 = prim(g, tmp);
		if ((int) tmp.size() == n - 1 && r2 < r1) r1 = r2;
		tmp.clear();
	}
	cout << r0 << " " << r1 << endl;
}

int main(void) {
	int nbcases, n, m, a, b, c;
	graph g;
	for (cin >> nbcases; nbcases; --nbcases) {
		cin >> n >> m;
		// Réinitialisation
		g.clear();
		g.resize(n);
		// Ajout des arêtes
		for (; m; --m) {
			cin >> a >> b >> c;
			--a; --b;
			g[a].push_back(edge(a, b, c));
			g[b].push_back(edge(b, a, c));
		}
		compute(g);
	}
	return 0;
}
