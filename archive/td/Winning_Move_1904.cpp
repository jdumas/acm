#include <iostream>
#include <map>
using namespace std;

unsigned coin;
unsigned current_state;

map<unsigned, bool> winning_strategies;
map<unsigned, bool>::iterator it;

#define dmask1 17043520
#define dmask2 1074791425
#define hmask 85
#define vmask 16843009
bool did_it_make_me_win(short pos) {
	unsigned new_statut = current_state >> (coin - 1);
	if ((new_statut & dmask1) == dmask1)
		return true;
	if ((new_statut & dmask2) == dmask2)
		return true;
	if ((new_statut >> (pos & ~7) & hmask) == hmask)
		return true;
	if ((new_statut >> (pos & 7) & vmask) == vmask)
		return true;
	return false;
}

bool has_winning_strategy(void) {
	short pos;
	// Si l'état a déjà été exploré, renvoyer le résultat connu
	it = winning_strategies.find(current_state);
	if (it != winning_strategies.end())
		return it->second;
	coin ^= 3;
	for (pos = 0; pos < 32; pos += 2) {
		if (current_state & (3u << pos))
			continue;
		// Modification de la variable d'état
		current_state |= (coin << pos);
		if (did_it_make_me_win(pos) || !has_winning_strategy()) {
			current_state &= ~(3u << pos);
			// Mémorisation du résultat
			winning_strategies.insert(make_pair(current_state, true));
			coin ^= 3;
			return true;
		}
		current_state &= ~(3u << pos);
	}
	winning_strategies.insert(make_pair(current_state, false));
	coin ^= 3;
	return false;
}

pair<int, int> first_move(void) {
	short pos;
	coin = 2u;
	for (pos = 0; pos < 32; pos += 2) {
		if (current_state & (3u << pos))
			continue;
		// Modification de la variable d'état
		current_state |= (coin << pos);
		if (did_it_make_me_win(pos) || !has_winning_strategy()) {
			current_state &= ~(3u << pos);
			return make_pair(pos >> 3, (pos & 7) >> 1);
		}
		current_state &= ~(3 << pos);
	}
	return make_pair(4, 4);
}

int main(void) {
	short pos;
	char c;
	pair<int, int> answer;
	while (1) {
		cin >> c;
		if (c == '$')
			break;
		if (c != '?') {
			cerr << "Wrong input";
			return 1;
		}
		// Initialisation
		current_state = 0;
		for (pos = 0; pos < 32; pos += 2) {
			cin >> c;
			switch (c) {
			case ('x'):
				coin = 2;
				break;
			case ('o'):
				coin = 1;
				break;
			default:
				coin = 0;
			}
			current_state |= (coin << pos);
		}
		answer = first_move();
		// Écriture du résultat
		if (answer == make_pair(4, 4))
			cout << "#####" << endl;
		else
			cout << '(' << answer.first << ',' << answer.second << ')' << endl;
	}
	return 0;
}
