#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <climits>
using namespace std;

typedef vector<vector<int> > graph;
typedef vector<int> tab;
typedef vector<bool> marque;
typedef stack<int> pile;

// Un premier DFS
void first_pass(graph & g, marque & vu, pile & s, int i) {
	int j;
	for (j = 0; j < (int) g[i].size(); ++j) {
		if (vu[g[i][j]])
			continue;
		vu[g[i][j]] = true;
		first_pass(g, vu, s, g[i][j]);
	}
	s.push(i);
}

// Un second DFS
void second_pass(graph & g, marque & vu, tab & t, int i, int nc) {
	int j;
	t[i] = nc;
	for (j = 0; j < (int) g[i].size(); ++j) {
		if (vu[g[i][j]])
			continue;
		vu[g[i][j]] = true;
		second_pass(g, vu, t, g[i][j], nc);
	}
}

// Calcul des composantes fortement connexes
// Entrées : le graphe “g”, le graphe inversé “rg”
// Sortie  : un tableau “t” qui associe à un sommet sa composante connexe + le nombre de composantes connexes
int cfc(graph & g, graph & rg, tab & t) {
	marque vu(g.size(), false);
	pile comp;
	int i, nc = 0;
	t.resize(g.size());
	for (i = 0; i < (int) g.size(); ++i) {
		if (vu[i])
			continue;
		vu[i] = true;
		first_pass(g, vu, comp, i);
	}
	// Maintenant il faut dépiler
	vu.clear();
	vu.resize(g.size(), false);
	while (not comp.empty()) {
		i = comp.top();
		comp.pop();
		if (vu[i])
			continue;
		vu[i] = true;
		second_pass(rg, vu, t, i, nc);
		++nc;
	}
	return nc;
}

// Construction du graphe des composantes fortement connexes
void get_cfc_graph(graph & g, tab & t, graph & res, int nc) {
	int i, j;
	bool b;
	vector<set<int> > voisin(nc);
	set<int>::iterator it;
	res.clear();
	res.resize(nc);
	for (i = 0; i < (int) g.size(); ++i) {
		for (j = 0; j < (int) g[i].size(); ++j) {
			b = voisin[t[i]].insert(t[g[i][j]]).second;
			if (b && t[i] != t[g[i][j]])
				res[t[i]].push_back(t[g[i][j]]);
		}
	}
}

// En sortie : t[i] = indice du i-ème sommet dans l'ordre topologique ...
void tri_topologique(graph & g, tab & t) {
	marque vu(g.size(), false);
	pile s;
	int i;
	t.resize(g.size());
	for (i = 0; i < (int) g.size(); ++i) {
		if (vu[i])
			continue;
		vu[i] = true;
		first_pass(g, vu, s, i);
	}
	i = 0;
	while (not s.empty()) {
		t[i] = s.top();
		++i;
		s.pop();
	}
}

// En entrée : un tableau t décrivant les composantes fortement connexes de G,
//             un tableau cost contenant le coût d'information de chaque personne.
// En sortie : cost_cc[i] = coût minimal nécessaire pour informer la cfc n°i
void get_cost(tab & t, tab & cost, tab & cost_cc, int nc) {
	int i;
	cost_cc.clear();
	cost_cc.resize(nc, INT_MAX);
	for (i = 0; i < (int) t.size(); ++i) {
		cost_cc[t[i]] = min(cost_cc[t[i]], cost[i]);
	}
}

// Marquer les sommets accessibles depuis “i”
void dfs(graph & g, marque & vu, int i) {
	int j;
	for (j = 0; j < (int) g[i].size(); ++j) {
		if (vu[g[i][j]])
			continue;
		vu[g[i][j]] = true;
		dfs(g, vu, g[i][j]);
	}
}

// Informe successivement chaque sommet selon l'ordre indiqué par “ordre_cc”
// Renvoie le coût total pour informer tout le monde
int spread_the_word(graph & g, tab & cost_cc, tab & ordre_cc) {
	marque vu(g.size(), false);
	int i, x, accu = 0;
	for (i = 0; i < (int) g.size(); ++i) {
		x = ordre_cc[i];
		if (vu[x]) continue;
		accu += cost_cc[x];
		vu[x] = true;
		dfs(g, vu, x);
	}
	return accu;
}

int main(void) {
	int i, j, c, k, n, m, nc, res;
	graph g, rg, cc;
	tab cost, repr, cost_cc, order;
	while (true) {
		cin >> n >> m;
		if (n == 0 && m == 0) break;
		g.resize(n);
		rg.resize(n);
		cost.resize(n);
		// Lecture des entrées
		for (k = 0; k < n; ++k) {
			cin >> c;
			cost[k] = c;
		}
		for (k = 0; k < m; ++k) {
			cin >> i >> j;
			--i, --j;
			g[i].push_back(j);
			rg[j].push_back(i);
		}
		// Calcul principal
		nc = cfc(g,rg,repr);
		get_cfc_graph(g,repr,cc,nc);
		tri_topologique(cc,order);
		get_cost(repr, cost, cost_cc, nc);
		res = spread_the_word(cc, cost_cc, order);
		// Affichage de la sortie
		cout << res << endl;
		g.clear();
		rg.clear();
		cost.clear();
	}
}
