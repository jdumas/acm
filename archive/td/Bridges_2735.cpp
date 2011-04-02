#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<vector<pair<int, int> > > graph;
typedef pair<double, int> weight; // Couple (poids, numéro) correspondant à une arête

int n, k, sh, sc;
graph g;
vector<int> deg;    // Degré d'un sommet au fur et à mesure qu'on effeuille
vector<int> nbdesc; // Nombre de noeud dans l'arbre constitué des fils effeuillés + le noeud courant
vector<double> len; // Longueur d'une arête
vector<int> occur;  // Nombre de chemins passant par cette arête
vector<weight> ordered; // L'ensemble des arêtes triées en fonction de leur poids

bool compare(const weight & w1, const weight & w2) {
	return (w1.first < w2.first);
}

void effeuille(void) {
	int i0, i, j, m, e;
	vector<pair<int, int> >::iterator it;
	vector<bool> vu(n, false);
	vector<int> stack;
	for (i = 0; i < n; ++i) {
		deg[i] = g[i].size();
		if (deg[i] == 1) {
			vu[i] = true;
			stack.push_back(i);
		}
	}
	for (i0 = 0; i0 < n; ++i0) {
		i = stack[i0];
		m = nbdesc[i];
		for (it = g[i].begin(); it < g[i].end(); ++it) {
			j = it->first;
			e = it->second;
			if (occur[e] == 0)
				occur[e] = m * (n - m);
			if (vu[j]) continue;
			deg[j] -= 1;
			nbdesc[j] += m;
			if (deg[j] != 1) continue;
			vu[j] = true;
			stack.push_back(j);
		}
	}
	return;
}

void compute(void) {
	int i;
	double cost;
	for (i = 0; i < n - 1; ++i) {
		cost = occur[i] * len[i] * (sh - sc);
		ordered[i] = make_pair(cost, 1+i);
	}
	sort(ordered.begin(), ordered.end(), compare);
	for (i = 0; i < k; ++i)
		cout << ordered[i].second << " ";
	cout << endl;
}

int main(void) {
	int i, x, y, l;
	cin >> n >> k >> sh >> sc;
	g.resize(n);
	deg.resize(n);
	nbdesc.resize(n, 1);
	len.resize(n - 1);
	occur.resize(n - 1);
	ordered.resize(n - 1);
	for (i = 0; i < n - 1; ++i) {
		cin >> x >> y >> l;
		--x;
		--y;
		len[i] = l;
		g[x].push_back(make_pair(y, i));
		g[y].push_back(make_pair(x, i));
	}
	effeuille();
	compute();
	return 0;
}
