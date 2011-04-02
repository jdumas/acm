#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

map<string, set<string> > my_map;

void read_dictionnary(void) {
	string clef, valeur;
	while (1) {
		cin >> valeur;
		if (valeur[0] == 'X')
			return;
		clef.clear();
		clef.append(valeur);
		sort(clef.begin(), clef.end());
		my_map[clef].insert(valeur);
	}
}

void read_scrambled(void) {
	string clef;
	map<string, set<string> >::iterator map_it;
	set<string>::iterator set_it;
	while (1) {
		cin >> clef;
		if (clef[0] == 'X')
			return;
		sort(clef.begin(), clef.end());
		map_it = my_map.find(clef);
		if (map_it == my_map.end())
			cout << "NOT A VALID WORD" << endl;
		else {
			for (set_it = map_it->second.begin(); set_it != map_it->second.end(); set_it++) {
				cout << *set_it << endl;
			}
		}
		cout << "******" << endl;
	}
}

int main(void) {
	string clef, valeur;
	read_dictionnary();
	read_scrambled();
	return 0;
}
