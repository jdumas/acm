#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct edge {
	int x, y, w;
	edge(void): x(),y(),w() {};
	edge(int a, int b, int c): x(a), y(b), w(c) {}
	bool operator< (const edge & e) const {
		return w > e.w;
	}
};

typedef vector<vector<edge> > graph;
typedef vector<int> tab;

void dijsktra(graph & g, tab & pere, tab & dist, int source) {
	priority_queue<edge> file;
	vector<bool> vu (g.size(), false);
	edge e,f;
	int i = 0;
	file.push(edge(source,source,0));
	while (!file.empty()) {
		e = file.top();
		file.pop();
		if (vu[e.y]) continue;
		// La distance de source à e.y est la bonne
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

bool does_need_path(graph & g, int & x0, int & x1) {
	int i;
	bool needed = false, b = false;
	for (i = 0; i < 26; ++i) {
		if ((g[i].size() % 2) == 0) continue;
		needed = true;
		b ? x0 = i : x1 = i;
		b = !b;
	}
	return needed;
}

int main(void) {
	graph g;
	tab pere,dist;
	string s;
	int x, y, total = 0;
	g.resize(26);
	pere.resize(26);
	dist.resize(26, INT_MAX);
	while (cin >> s) {
		if (s != "deadend") {
			// Index des sommets incidents
			x = s[0]            - 'a';
			y = s[s.size() - 1] - 'a';
			// On retient les poids
			total += s.size();
			// Et on ajoute l'arête (x,y)
			g[x].push_back(edge(x,y,s.size()));
			g[y].push_back(edge(y,x,s.size()));
			continue;
		}
		// On a fini de lire une instance
		if (does_need_path(g,x,y)) {
			dijsktra(g,pere,dist,x);
			total += dist[y];
		}
		cout << total << endl;
		total = 0;
		g.clear();
		dist.clear();
		g.resize(26);
		dist.resize(26, INT_MAX);
	}
	return 0;
}
