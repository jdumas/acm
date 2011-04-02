#include <iostream>
#include <list>
using namespace std;

typedef struct {
	int s; // Start (abscisse de départ)
	int e; // End   (abscisse d'arrivée)
	int h; // Height
} block;

list<block> my_list;

// Renvoie la hauteur maximum atteinte par un bloc du jeu
int hmax(void) {
	list<block>::iterator it;
	int max = 0;
	for (it = my_list.begin(); it != my_list.end(); it++) {
		if (it->h > max)
			max = it->h;
	}
	return max;
}

// Ajouter un bloc à la bonne position dans la liste
void add_one_block(void) {
	list<block>::iterator it;
	int s, e, h, max_h;
	cin >> s >> e >> h;
	max_h = h;
	for (it = my_list.begin(); it != my_list.end(); it++) {
		// Si le nouveau bloc n'est pas au dessus du bloc courant
		if (it->e < s || it->s > e)
			continue;
		// Calcul de la hauteur max pour atterir
		if (it->h + h > max_h)
			max_h = it->h + h;
	}
	block new_s = { s, e, max_h };
	my_list.insert(it, new_s);
	return;
}

int main(void) {
	int n, w;
	while (cin >> n >> w) {
		if (n == 0 && w == 0)
			break;
		my_list.clear();
		for (; n; n--) {
			add_one_block();
		}
		cout << hmax() << endl;
	}
	return 0;
}
