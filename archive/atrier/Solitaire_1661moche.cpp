#include <cstdio>
#include <iostream>
#include <set>
using namespace std;
typedef unsigned long long uint64;
set<uint64> states;
uint64 goal, current_state;
char pos[4][2];

#define probe(new_state) {						\
		current_state |= new_state;				\
		it = states.insert(current_state);		\
		if (it.second) {						\
			if (explore())						\
				return true;					\
			states.erase(it.first);				\
		}										\
		current_state &= ~(new_state);			\
}

bool explore(void) {
	pair<set<uint64>::iterator, bool> it;
	uint64 current_pawn;
	if (current_state == goal)
		return true;
	for (char i = 0; i < 4; i++) {
		current_pawn = 1 << pos[i][0] << (pos[i][1] << 4);
		current_state &= ~current_pawn;
		// Gauche
		if (pos[i][0] != 0) {
			if (current_state & ~(current_pawn << 1)) {
				pos[i][0]--;
				probe(current_pawn << 1);
				pos[i][0]++;
			} else if (pos[i][0] != 1 || current_state & ~(current_pawn << 2)) {
				pos[i][0] -= 2;
				probe(current_pawn << 2);
				pos[i][0] += 2;
			}
		}
		// Droite
		if (pos[i][0] != 7) {
			if (current_state & ~(current_pawn >> 1)) {
				pos[i][0]++;
				probe(current_pawn >> 1);
				pos[i][0]--;
			} else if (pos[i][0] != 6 || current_state & ~(current_pawn >> 2)) {
				pos[i][0] += 2;
				probe(current_pawn >> 2);
				pos[i][0] -= 2;
			}
		}
		// Haut
		if (pos[i][1] != 0) {
			if (current_state & ~(current_pawn << 8)) {
				pos[i][1]--;
				probe(current_pawn << 8);
				pos[i][1]++;
			} else if (pos[i][1] != 1 || current_state & ~(current_pawn << 16)) {
				pos[i][1] -= 2;
				probe(current_pawn << 16);
				pos[i][1] += 2;
			}
		}
		// Bas
		if (pos[i][0] != 7) {
			if (current_state & ~(current_pawn >> 8)) {
				pos[i][1]++;
				probe(current_pawn >> 8);
				pos[i][1]--;
			} else if (pos[i][0] != 6 || current_state & ~(current_pawn >> 16)) {
				pos[i][1] += 2;
				probe(current_pawn >> 16);
				pos[i][1] -= 2;
			}
		}
		// Fin
		current_state |= current_pawn;
	}
	return false;
}

int main(void) {
	return 0;
}
