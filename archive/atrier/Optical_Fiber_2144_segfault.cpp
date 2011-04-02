#include <cstdio>
#include <iostream>
#include <map>
#include <set>
using namespace std;

map<string, int> ville_id;
map<string, set<string> > fils;

void parcours(string current, string pere) {
	map<string, set<string> >::iterator it_fils;
	set<string>::iterator it_set;
	it_fils = fils.find(current);
	it_fils->second.erase(pere);
	for (it_set = it_fils->second.begin(); it_set != it_fils->second.end(); it_set++) {
		parcours(*it_set, current);
	}
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
		for (i = 0; i < n; i++) {
			cin >> name1 >> j;
			for (; j > 0; j--)
				cin >> x >> y;
		}
		for (i = 1; i < n; i++) {
			cin >> name1 >> name2;
			fils[name1].insert(name2);
			fils[name2].insert(name1);
		}
		// Génération de l'arbre
		parcours(fils.begin()->first, "");
	}
}
