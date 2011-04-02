#include <iostream>
#include <vector>
#include <queue>
#include <complex>
using namespace std;

typedef vector<vector<int> > graph;
typedef vector<vector<int> > matrix;
typedef vector<int> tab;
typedef complex<double> pt;

struct ff {
	graph g;
	tab pere;
	matrix capa, flot;
	int source, target;
	int size(void) { return g.size(); }
	int cout(int x, int y) {
		return capa[x][y] - flot[x][y];
	}
	void init(int n) {
		g.resize(n);
		capa.resize(n, vector<int> (n,0));
		flot.resize(n, vector<int> (n,0));
	}
	void reset(void) {
		flot.clear();
		flot.resize(g.size(), vector<int> (g.size(), 0));
	}
	void clear(void) {
		g.clear();
		capa.clear();
		flot.clear();
		pere.clear();
		source = 0, target = 0;
	}
};

// Parcours en largeur conditionnel
void parcours(ff & st) {
	int x,y,i;
	queue<int> file;
	st.pere.clear();
	st.pere.resize(st.size(), -1);
	file.push(st.source);
	st.pere[st.source] = st.source;
	while (!file.empty()) {
		x = file.front();
		file.pop();
		for (i = 0; i < (int) st.g[x].size(); ++i) {
			y = st.g[x][i];
			if (st.pere[y] != -1) continue;
			if (st.cout(x,y) <= 0) continue;
			st.pere[y] = x;
			file.push(y);
			if (y == st.target) return;
		}
	}
	return;
}

// Calcul du cout résiduel le long d'un chemin
int cout_residuel(ff & st) {
	int x, y, c;
	y = st.target;
	x = st.pere[st.target];
	c = st.cout(x, y);
	while (st.pere[x] != x) {
		y = x;
		x = st.pere[x];
		c = min(c, st.cout(x,y));
	}
	return c;
}

// Agmenter le flot le long du chemin
void augmenter(ff & st, int c) {
	int x, y;
	y = st.target;
	x = st.pere[st.target];
	while (x != y) {
		st.flot[x][y] += c;
		st.flot[y][x] -= c;
		y = x;
		x = st.pere[x];
	}
	return;
}

// Calcul d'un flot maximum
int flot_max(ff & st) {
	int c, s = 0;
	while (true) {
		parcours(st);
		if (st.pere[st.target] == -1) break;
		c = cout_residuel(st);
		s += c;
		augmenter(st, c);
	}
	return s;
}

// On teste toutes les destinations possibles
void tester(ff & st, int nilots, int npinguins) {
	vector<int> valid;
	int i, v;
	st.source = st.size() - 1;
	for (i = 0; i < nilots; ++i) {
		st.target = i;
		v = flot_max(st);
		st.reset();
		if (v == npinguins)
			valid.push_back(i);
	}
	cout << (valid.size() == 0 ? -1 : valid[0]);
	for (i = 1; i < (int) valid.size(); ++i)
		cout << " " << valid[i];
	cout << endl;
}

// Construction du graphe
void add_edge(graph & g, int i, int j) {
	g[i].push_back(j);
	g[j].push_back(i);
	return;
}

void handle_vertex(ff & st, int nilots, int i, int ni, int mi) {
	// Arête entre i et i+nilots
	st.capa[i][i+nilots] = mi;
	add_edge(st.g, i, i+nilots);
	// Arête entre i et la source
	if (ni != 0) {
		st.capa[2*nilots][i] = ni;
		add_edge(st.g, i, 2*nilots);
	}
}

void handle_pair(ff & st, int nilots, int npinguins, int i, int j) {
	st.capa[j + nilots][i] = npinguins;
	st.capa[i + nilots][j] = npinguins;
	add_edge(st.g, i, j + nilots);
	add_edge(st.g, j, i + nilots);
}

int main(void) {
	int ncase, nilots, npinguins, i, j, ni, mi, n;
	vector<pt> accu;
	ff st;
	double d, x, y;
	for (cin >> ncase; ncase; --ncase) {
		cin >> nilots >> d;
		// Initialisation
		n = 2*nilots+1;
		npinguins = 0;
		st.init(n);
		// Lire les entrées et dédoubler chaque sommet
		for (i = 0; i < nilots; ++i) {
			cin >> x >> y >> ni >> mi;
			handle_vertex(st,nilots, i, ni, mi);
			npinguins += ni;
			accu.push_back(pt (x,y));
		}
		// Lier les ilots assez proche entre eux
		for (i = 0; i < nilots; ++i) {
			for (j = i + 1; j < nilots; ++j) {
				if (abs(accu[i] - accu[j]) <= d)
					handle_pair(st, nilots, npinguins, i, j);
			}
		}
		accu.clear();
		// Exécuter l'algorithme principal
		tester(st, nilots, npinguins);
		st.clear();
	}
}
