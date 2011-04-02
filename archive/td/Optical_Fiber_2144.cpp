#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <math.h>
using namespace std;

map<string, int> ville_id;
vector<int> t;
vector<vector<int> > fils;
vector<vector<pair<int, int> > > sites;
int counter;

double inline dist(pair<int, int> p1, pair<int, int> p2) {
	double d;
	int p;
	p = (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
	d = sqrt((double) p);
	return d;
}

void parcours(int cur, int pere) {
	unsigned i;
	// Numérotation des différents sommets dans l'ordre
	t[counter] = cur;
	counter++;
	for (i = 0; i < fils[cur].size(); i++) {
		if (fils[cur][i] == pere) {
			fils[cur].erase(fils[cur].begin() + i);
			i--;
		} else
			parcours(fils[cur][i], cur);
	}
	return;
}

double explore(int n) {
	int i;
	unsigned j, k, l;
	double sum, accu, tmp;
	vector<vector<double> > p;
	p.resize(n);
	for (i = n - 1; i >= 0; i--) {
		for (j = 0; j < sites[t[i]].size(); j++) {
			sum = 0.;
			for (k = 0; k < fils[t[i]].size(); k++) {
				accu = 1. / 0.; // Tout le monde sait que 1./0. = +infiny
				for (l = 0; l < sites[fils[t[i]][k]].size(); l++) {
					// Calcul de p(k,l) + d(j,l)
					tmp = p[fils[t[i]][k]][l] + dist(sites[t[i]][j], sites[fils[t[i]][k]][l]);
					if (tmp < accu)
						accu = tmp;
				}
				sum += accu;
			}
			p[t[i]].push_back(sum);
		}
	}
	accu = 1. / 0.;
	for (j = 0; j < sites[0].size(); j++) {
		if (p[0][j] < accu)
			accu = p[0][j];
	}
	return accu;
}

int main(void) {
	unsigned n, i, j;
	int x, y;
	string name1, name2;
	while (cin >> n) {
		if (!n)
			break;
		// Initialisation
		ville_id.clear();
		fils.clear();
		sites.clear();
		t.clear();
		fils.resize(n);
		sites.resize(n);
		t.resize(n);
		for (i = 0; i < n; i++) {
			cin >> name1 >> j;
			ville_id.insert(make_pair(name1, i));
			for (; j > 0; j--) {
				cin >> x >> y;
				sites[i].push_back(make_pair(x, y));
			}
		}
		for (i = 1; i < n; i++) {
			cin >> name1 >> name2;
			x = ville_id.find(name1)->second;
			y = ville_id.find(name2)->second;
			// Création du graphe
			fils[x].push_back(y);
			fils[y].push_back(x);
		}
		// Génération de l'arbre
		counter = 0;
		parcours(0, -1);
		printf("%.1f\n", explore(n));
	}
}
