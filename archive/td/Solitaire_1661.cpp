#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
typedef unsigned long long uint64;

map<uint64, short> first_pass_states;
map<uint64, short> second_pass_states;
map<uint64, short> *map_pointer;
uint64 current_state, accu_state;
short current_pos[4][2];
short accu_pos[4][2];
short depth;
bool is_first_pass;
bool explore(void);
bool make_move(short, short, short, short, short, pair<
		map<uint64, short>::iterator, bool> &);

// Vérifie si la case est occupée ou pas
bool is_free(short i, short j) {
	return (current_state & (1ull << (i + j * 8))) == 0ull;
}

bool make_move(short i, short x0, short y0, short x1, short y1, pair<map<
		uint64, short>::iterator, bool> &tmp) {
	// Déplacement du pion sur la variable d'état
	current_state &= ~(1ull << (x0 + y0 * 8));
	current_state |= 1ull << (x1 + y1 * 8);
	current_pos[i][0] = x1;
	current_pos[i][1] = y1;
	// Exploration récursive
	tmp = (*map_pointer).insert(make_pair(current_state, depth));
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
	if (is_first_pass) {
		if (current_state == accu_state)
			return true;
	} else if (first_pass_states.count(current_state)) {
		return true;
	}
	if (!depth)
		return false;
	depth--;
	pair<map<uint64, short>::iterator, bool> tmp;
	for (i = 0; i < 4; i++) {
		x = current_pos[i][0];
		y = current_pos[i][1];
		// Déplacement à gauche
		if (x > 0) {
			if (is_free(x - 1, y)) {
				if (make_move(i, x, y, x - 1, y, tmp))
					return true;
			} else if (x != 1 && is_free(x - 2, y)) {
				if (make_move(i, x, y, x - 2, y, tmp))
					return true;
			}
		}
		// Déplacement à droite
		if (x < 7) {
			if (is_free(x + 1, y)) {
				if (make_move(i, x, y, x + 1, y, tmp))
					return true;
			} else if (x != 6 && is_free(x + 2, y)) {
				if (make_move(i, x, y, x + 2, y, tmp))
					return true;
			}
		}
		// Déplacement vers le haut
		if (y > 0) {
			if (is_free(x, y - 1)) {
				if (make_move(i, x, y, x, y - 1, tmp))
					return true;
			} else if (y != 1 && is_free(x, y - 2)) {
				if (make_move(i, x, y, x, y - 2, tmp))
					return true;
			}
		}
		// Déplacement vers le bas
		if (y < 7) {
			if (is_free(x, y + 1)) {
				if (make_move(i, x, y, x, y + 1, tmp))
					return true;
			} else if (y != 6 && is_free(x, y + 2)) {
				if (make_move(i, x, y, x, y + 2, tmp))
					return true;
			}
		}
		current_pos[i][0] = x;
		current_pos[i][1] = y;
	}
	depth++;
	return false;
}

int main(void) {
	short i, x, y;
	bool result;
	current_state = 0ull;
	accu_state = 0ull;
	// Lecture de l'entrée :
	for (i = 0; i < 4; i++) {
		cin >> x >> y;
		x--;
		y--;
		current_state |= 1ull << (x + y * 8);
		current_pos[i][0] = x;
		current_pos[i][1] = y;
	}
	for (i = 0; i < 4; i++) {
		cin >> x >> y;
		x--;
		y--;
		accu_state |= 1ull << (x + y * 8);
		accu_pos[i][0] = x;
		accu_pos[i][1] = y;
	}
	// Exploration
	is_first_pass = true;
	map_pointer = &first_pass_states;
	depth = 4;
	(*map_pointer).insert(make_pair(current_state, depth));
	result = explore();
	if (!result) {
		// Echange des données et préparation de la deuxième passe
		current_state = accu_state;
		for (i = 0; i < 4; i++) {
			current_pos[i][0] = accu_pos[i][0];
			current_pos[i][1] = accu_pos[i][1];
		}
		is_first_pass = false;
		map_pointer = &second_pass_states;
		depth = 4;
		(*map_pointer).insert(make_pair(current_state, depth));
		result = explore();
	}
	// Ecriture du résultat
	cout << (result ? "YES" : "NO") << endl;
	return 0;
}
