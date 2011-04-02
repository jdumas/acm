#include <iostream>
#include <vector>
#include <climits>
#include <stack>
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
	bool has_loop = true;
	d[source] = 0;
	k = 0;
	while (has_loop) {
		if (k >= borne) break;
		has_loop = false;
		for (i = 0; i < (int) e.size(); ++i) {
			if (d[e[i].x] != INT_MAX && d[e[i].y] > d[e[i].x] + e[i].w) {
				d[e[i].y] = d[e[i].x] + e[i].w;
				has_loop = true;
			}
		}
		++k;
	}
	return has_loop;
}

// Construction de la liste des arêtes atteignables
int build(vector<edges> & g, edges & adj, int s) {
	vector<bool> vu(s, false);
	stack<int> t;
	int i, j, count = 1;
	vu[0] = true;
	t.push(0);
	while (!t.empty()) {
		i = t.top();
		t.pop();
		for (j = 0; j < (int) g[i].size(); ++j) {
			adj.push_back(g[i][j]);
			if (vu[g[i][j].y])
				continue;
			++count;
			vu[g[i][j].y] = true;
			t.push(g[i][j].y);
		}
	}
	return count;
}

enum soil {
	GRASS, GRAVE, HOLE
};

// Ajoute une arête si les cases satisfont les bonnes propriétés
void add(vector<edges> & graph, vector<soil> & type,
		int w, int h, int x1, int y1, int x2, int y2) {
	if (x1 != w - 1 || y1 != h - 1)									// On ne part pas depuis la case de sortie
	if (x2 >= 0 && x2 < w && y2 >= 0 && y2 < h)						// On ne part pas en dehors du terrain
	if (type[x1 + y1 * w] == GRASS && type[x2 + y2 * w] != GRAVE)	// On part d'un carré d'herbe vers autre chose qu'une tombe
		graph[x1 + y1 * w].push_back(edge(x1 + y1 * w, x2 + y2 * w, 1));
}

int main(void) {
	int w, h, g, e, x, y, x2, y2, t;
	vector<int> dist;
	vector<soil> type;
	vector<edges> graph;
	edges adj;
	while (true) {
		cin >> w >> h;
		if (w == 0 && h == 0) break;
		// Initialisation
		graph.resize(w * h);
		type.resize(w * h, GRASS);
		dist.resize(w * h, INT_MAX);
		// On lit où sont les tombes
		for (cin >> g; g; --g) {
			cin >> x >> y;
			type[x + y * w] = GRAVE;
		}
		// On lit où sont les trous
		for (cin >> e; e; --e) {
			cin >> x >> y >> x2 >> y2 >> t;
			type[x + y * w] = HOLE;
			graph[x + y * w].push_back(edge(x + y * w, x2 + y2 * w, t));
		}
		// On ajoute les arêtes qu'il faut en conséquence
		for (x = 0; x < w; ++x) {
			for (y = 0; y < h; ++y) {
				add(graph, type, w, h, x, y, x + 1, y);
				add(graph, type, w, h, x, y, x - 1, y);
				add(graph, type, w, h, x, y, x, y + 1);
				add(graph, type, w, h, x, y, x, y - 1);
			}
		}
		// Construction du graphe et résolution du problème
		t = build(graph, adj, w * h);
		if (bellman(adj, dist, t, 0))
			cout << "Never" << endl;
		else if (dist[w * h - 1] == INT_MAX)
			cout << "Impossible" << endl;
		else
			cout << dist[w * h - 1] << endl;
		// Nettoyage
		adj.clear();
		graph.clear();
		dist.clear();
		type.clear();
	}
}
