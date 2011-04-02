#include <iostream>
using namespace std;

char grille[4][4];
char coin;

void flip_coin(void) {
	coin = (coin == 'x' ? 'o' : 'x');
	return;
}

bool did_it_make_me_win(char i, char j) {
	char k, yes_no_maybe;
	if (i == j) {
		yes_no_maybe = 7;
		for (k = 0; k < 4; k++) {
			if (grille[k][j] != coin)
				yes_no_maybe &= ~1;
			if (grille[i][k] != coin)
				yes_no_maybe &= ~2;
			if (grille[k][k] != coin)
				yes_no_maybe &= ~4;
		}
	} else if (i + j == 3) {
		yes_no_maybe = 7;
		for (k = 0; k < 4; k++) {
			if (grille[k][j] != coin)
				yes_no_maybe &= ~1;
			if (grille[i][k] != coin)
				yes_no_maybe &= ~2;
			if (grille[k][3 - k] != coin)
				yes_no_maybe &= ~4;
		}
	} else {
		yes_no_maybe = 3;
		for (k = 0; k < 4; k++) {
			if (grille[k][j] != coin)
				yes_no_maybe &= ~1;
			if (grille[i][k] != coin)
				yes_no_maybe &= ~2;
		}
	}
	return (yes_no_maybe != 0);
}

bool has_winning_strategy(void) {
	char i, j;
	flip_coin();
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (grille[i][j] != '.')
				continue;
			grille[i][j] = coin;
			if (did_it_make_me_win(i, j) || !has_winning_strategy()) {
				grille[i][j] = '.';
				flip_coin();
				return true;
			}
			grille[i][j] = '.';
		}
	}
	flip_coin();
	return false;
}

pair<int, int> first_move(void) {
	char i, j;
	coin = 'x';
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (grille[i][j] != '.')
				continue;
			grille[i][j] = coin;
			if (did_it_make_me_win(i, j) || !has_winning_strategy()) {
				grille[i][j] = '.';
				return make_pair(i, j);
			}
			grille[i][j] = '.';
		}
	}
	return make_pair(4, 4);
}

int main(void) {
	int i, j;
	char c;
	pair<int, int> answer = make_pair(0, 0);
	while (1) {
		cin >> c;
		if (c == '$')
			break;
		if (c != '?') {
			cerr << "Wrong input";
			return 1;
		}
		// Initialisation
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				cin >> grille[i][j];
			}
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
