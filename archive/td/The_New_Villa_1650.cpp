#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

/* Le graphe = une matrice (etat, piece_courrante) -> action nécessaire pour arriver ici.
 * Cette action est représentée par une paire p avec :
 * _ p.first = true  s'il a fallut changer de pièce
 *   (auquel cas p.second indique la pièce où on était avant)
 * _ p.first = false s'il a fallut commuter un interrupteur
 *   (auquel cas p.second indique la pièce qui a été modifiée)
 */

vector<vector<bool> > vu; // La matrice des sommets visités
vector<vector<pair<bool, int> > > graph;

vector<vector<int> > reachable_rooms; // Associe à une pièce les pièces adjacentes
vector<vector<int> > lightable_rooms; // Associe à une pièce celles que l'on peut modifer depuis là

int r, d, s; // Déclaré en global, plus pratique
int nb_step; // Utilisé pour l'affichage de la réponse

void parcours(void) {
	queue<pair<int, int> > q;
	unsigned state, new_state;
	int room;
	vector<int>::iterator it; // Itérateur pour les voisins;
	// Initialisation
	q.push(make_pair(1u, 0));
	vu[1][0] = true;
	// Parcours en largeur
	while (!q.empty()) {
		state = q.front().first;
		room = q.front().second;
		q.pop();
		// Une condition d'arrêt supplémentaire mais superflue
		if (room == r-1 && state == (1u << (r-1)))
			break;
		// Recherche des pièces atteignables depuis la pièce courante
		for (it = reachable_rooms[room].begin(); it
				!= reachable_rooms[room].end(); it++) {
			if (vu[state][*it])
				continue;
			// Il ne faut pas que la pièce "*it" soit éteinte !
			if (~state & (1u << *it))
				continue;
			vu[state][*it] = true;
			graph[state][*it] = make_pair(true, room);
			q.push(make_pair(state, *it));
		}
		// Recherche des pièces modifiables depuis la pièce courante
		for (it = lightable_rooms[room].begin(); it
				!= lightable_rooms[room].end(); it++) {
			new_state = state ^ (1u << *it);
			if (vu[new_state][room])
				continue;
			// On ne peut pas éteindre la pièce où l'on se trouve !
			if (*it == room)
				continue;
			vu[new_state][room] = true;
			graph[new_state][room] = make_pair(false, *it);
			q.push(make_pair(new_state, room));
		}
	}
	return;
}

// Le chemin est donné à l'envers, il faut donc faire les impressions
// En remontant la pile des appels récursifs
void print_recurse(unsigned state, int room) {
	bool action;
	int movement;
	action = graph[state][room].first;
	movement = graph[state][room].second;
	// Cas de base
	if (state == 1u && room == 0) {
		cout << "The problem can be solved in " << nb_step << " steps:\n";
		return;
	}
	nb_step++;
	// Disjonction de cas
	if (action) {
		print_recurse(state, movement);
		cout << "- Move to room " << (room+1) << ".\n";
	}
	else {
		print_recurse(state ^ (1u << movement), room);
		if (state & (1u << movement))
			cout << "- Switch on light in room " << (movement+1) << ".\n";
		else
			cout << "- Switch off light in room " << (movement+1) << ".\n";
	}
}

void print_result(void) {
	if (!vu[1u << (r-1)][r - 1]) {
		cout << "The problem cannot be solved." << endl;
		return;
	}
	nb_step = 0;
	print_recurse(1u << (r-1), r-1);
	return;
}

int main(void) {
	int i, j, k = 1;
	while (1) {
		cin >> r >> d >> s;
		if (r == 0 && d == 0 && s == 0)
			break;
		// Ménage administratif
		vu.clear();
		vu.resize(1 << r, vector<bool> (r, false));
		graph.clear();
		graph.resize(1 << r, vector<pair<bool, int> > (r, make_pair(false, 0)));
		reachable_rooms.clear();
		reachable_rooms.resize(r);
		lightable_rooms.clear();
		lightable_rooms.resize(r);
		// Parsing des entrées
		for (; d; d--) {
			cin >> i >> j;
			i--;
			j--;
			reachable_rooms[i].push_back(j);
			reachable_rooms[j].push_back(i);
		}
		for (; s; s--) {
			cin >> i >> j;
			i--;
			j--;
			lightable_rooms[i].push_back(j);
		}
		// Corps principal
		parcours();
		cout << "Villa #" << k << endl;
		print_result();
		cout << endl;
		k++;
	}
	return 0;
}
