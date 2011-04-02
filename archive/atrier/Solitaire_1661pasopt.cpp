#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
typedef unsigned long long uint64;

map<uint64, short> steps;
uint64 goal, current_state;
short pos[4][2];
short depth;
bool explore(void);
bool make_move(short, short, short, short, short);

// Fonction utile au débugage
void print_state(void) {
	int i, j;
	uint64 buff = current_state;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			cout << (buff & 1ull);
			buff >>= 1;
		}
		cout << endl;
	}
	cout << endl;
}

// Vérifie si la case est occupée ou pas
bool is_free(short i, short j) {
	return (current_state & (1ull << (i + j * 8))) == 0ull;
}

bool make_move(short i, short x0, short y0, short x1, short y1) {
	pair<map<uint64, short>::iterator, bool> tmp;
	// Déplacement du pion sur la variable d'état
	current_state &= ~(1ull << (x0 + y0 * 8));
	current_state |= 1ull << (x1 + y1 * 8);
	pos[i][0] = x1;
	pos[i][1] = y1;
	// Exploration récursive
	tmp = steps.insert(make_pair(current_state, depth));
	if (tmp.second) {
		if (explore())
			return true;
		//steps.erase(tmp.first);
	} else if (tmp.first->second < depth) {
		tmp.first->second = depth;
		if (explore())
			return true;
	}
	// Restauration de l'état du monde
	current_state &= ~(1ull << (x1 + y1 * 8));
	current_state |= 1ull << (x0 + y0 * 8);
	return false;
}

bool explore(void) {
	short i, x, y;
	if (current_state == goal)
		return true;
	if (!depth)
		return false;
	depth--;
	for (i = 0; i < 4; i++) {
		x = pos[i][0];
		y = pos[i][1];
		// Déplacement à gauche
		if (x > 0) {
			if (is_free(x - 1, y)) {
				if (make_move(i, x, y, x - 1, y))
					return true;
			} else if (x != 1 && is_free(x - 2, y)) {
				if (make_move(i, x, y, x - 2, y))
					return true;
			}
		}
		// Déplacement à droite
		if (x < 7) {
			if (is_free(x + 1, y)) {
				if (make_move(i, x, y, x + 1, y))
					return true;
			} else if (x != 6 && is_free(x + 2, y)) {
				if (make_move(i, x, y, x + 2, y))
					return true;
			}
		}
		// Déplacement vers le haut
		if (y > 0) {
			if (is_free(x, y - 1)) {
				if (make_move(i, x, y, x, y - 1))
					return true;
			} else if (y != 1 && is_free(x, y - 2)) {
				if (make_move(i, x, y, x, y - 2))
					return true;
			}
		}
		// Déplacement vers le bas
		if (y < 7) {
			if (is_free(x, y + 1)) {
				if (make_move(i, x, y, x, y + 1))
					return true;
			} else if (y != 6 && is_free(x, y + 2)) {
				if (make_move(i, x, y, x, y + 2))
					return true;
			}
		}
		pos[i][0] = x;
		pos[i][1] = y;
	}
	depth++;
	return false;
}

int main(void) {
	short i, x, y;
	current_state = 0ull;
	goal = 0ull;
	// Lecture de l'entrée :
	for (i = 0; i < 4; i++) {
		cin >> x >> y;
		x--; y--;
		current_state |= 1ull << (x + y * 8);
		pos[i][0] = x;
		pos[i][1] = y;
	}
	for (i = 0; i < 4; i++) {
		cin >> x >> y;
		x--; y--;
		goal |= 1ull << (x + y * 8);
	}
	// Initialisation des données
	depth = 8;
	steps.insert(make_pair(current_state, depth));
	// Ecriture du résultat
	cout << (explore() ? "YES" : "NO") << endl;
	return 0;
}
