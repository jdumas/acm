#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<string, int> ville_id;
vector<vector<int> > fils;

void parcours(int cur, int pere) {
	unsigned i;
	// Numérotation des différents sommets dans l'ordre
	for (i = 0; i < fils[cur].size(); i++) {
		if (fils[cur][i] == pere) {
			fils[cur].erase(fils[cur].begin() + i);
			i--;
		} else
			parcours(fils[cur][i], cur);
	}
	return;
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
		fils.resize(n);
		for (i = 0; i < n; i++) {
			cin >> name1 >> j;
			ville_id.insert(make_pair(name1, i));
			for (; j > 0; j--) {
				cin >> x >> y;
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
		parcours(0, -1);
	}
}
