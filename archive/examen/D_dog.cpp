#include <iostream>
#include <complex>
#include <vector>
using namespace std;

struct node {
	vector<int> e;
	int match;
	node(void) :
		match(-1) {
	}
};

struct bipartite {
	vector<node> lg, rg;
	vector<bool> vu;
	int couplage;
	void reset(void) {
		vu.clear();
		vu.resize(lg.size(), false);
	}
	void init(int p, int q) {
		lg.resize(p);
		rg.resize(q);
		couplage = 0;
	}
	void clear(void) {
		lg.clear();
		rg.clear();
	}
};

bool explore(bipartite & g, int x) {
	int i, y, z;
	if (x == -1)
		return true;
	if (g.vu[x])
		return false;
	g.vu[x] = true;
	for (i = 0; i < (int) g.lg[x].e.size(); ++i) {
		y = g.lg[x].e[i];
		z = g.rg[y].match;
		if (explore(g, z)) {
			g.rg[y].match = x;
			g.lg[x].match = y;
			return true;
		}
	}
	return false;
}

bool find_path(bipartite & g) {
	int i;
	for (i = 0; i < (int) g.lg.size(); ++i) {
		if (g.lg[i].match == -1 && explore(g, i))
			return true;
	}
	return false;
}

void greedy_matching(bipartite & g) {
	int i, j, k;
	for (i = 0; i < (int) g.lg.size(); ++i) {
		for (k = 0; k < (int) g.lg[i].e.size(); ++k) {
			j = g.lg[i].e[k];
			if (g.lg[i].match == -1 && g.rg[j].match == -1) {
				g.lg[i].match = j;
				g.rg[j].match = i;
				++g.couplage;
			}
		}
	}
}

void couplage_max(bipartite & g) {
	while (true) {
		g.reset();
		if (find_path(g))
			++g.couplage;
		else
			break;
	}
	return;
}

typedef complex<double> point;
typedef vector<point> poly;

bool reachable(const point & p1, const point & p2, const point & p3) {
	return(abs(p1 - p3) + abs(p2 - p3) <= 2*abs(p1 - p2));
}

void print(const point & p) {
	cout << (int) p.real() << " " << (int) p.imag() << " ";
}

int main(void) {
	poly bob, place;
	bipartite g;
	int i, j, n, m, x, y;
	// Lecture des entrées
	cin >> n >> m;
	for (i = 0; i < n; ++i) {
		cin >> x >> y;
		bob.push_back(point (x, y));
	}
	for (j = 0; j < m; ++j) {
		cin >> x >> y;
		place.push_back(point (x, y));
	}
	// Construction du graphe
	g.init(n - 1, m);
	for (i = 0; i < n - 1; ++i) {
		for (j = 0; j < m; ++j) {
			if (reachable(bob[i], bob[i+1], place[j])) {
				g.lg[i].e.push_back(j);
				g.rg[j].e.push_back(i);
			}
		}
	}
	// Résolution du problème
	greedy_matching(g);
	couplage_max(g);
	// Affichage du résultat
	cout << g.couplage + n << endl;
	for (i = 0; i < n-1; ++i) {
		print(bob[i]);
		if (g.lg[i].match != -1)
			print(place[g.lg[i].match]);
	}
	print(bob.back());
}
