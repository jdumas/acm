#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct cell {
	int x;
	int y;
	cell * next;
	cell * prev;
} cell;

// Variables globales
cell * beeper_list = NULL;
int x0, y0, w, h;

// Destruction de la liste
void libere(cell * &p) {
	if (p == NULL)
		return;
	libere(p->next);
	delete p;
	p = NULL;
}

// Suppression d'une cellule de la liste
void retirer(cell *p) {
	if (p->next != NULL)
		p->next->prev = p->prev;
	if (p->prev != NULL)
		p->prev->next = p->next;
	else
		beeper_list = p->next;
}

// Réinsertion d'une cellule dans la liste
void reinsert(cell * p) {
	if (p->next != NULL)
		p->next->prev = p;
	if (p->prev != NULL)
		p->prev->next = p;
	else
		beeper_list = p;
}

// Fonction d'exploration principale
int backtrack(int x, int y) {
	if (beeper_list == NULL)
		return abs(x - x0) + abs(y - y0);
	unsigned max_dist = -1, dist;
	cell * tmp;
	for (tmp = beeper_list; tmp != NULL; tmp = tmp->next) {
		retirer(tmp);
		dist = abs(x - tmp->x) + abs(y - tmp->y);
		dist += backtrack(tmp->x, tmp->y);
		reinsert(tmp);
		if (dist < max_dist)
			max_dist = dist;
	}
	return max_dist;
}

int main(void) {
	int n, k;
	cell * tmp;
	cin >> n;
	for (; n; n--) {
		// Lecture des entrées
		cin >> w >> h >> x0 >> y0 >> k;
		for (; k; k--) {
			tmp = new cell;
			cin >> tmp->x >> tmp->y;
			// Ajout dans la liste
			tmp->next = beeper_list;
			tmp->prev = NULL;
			if (beeper_list != NULL)
				beeper_list->prev = tmp;
			beeper_list = tmp;
		}
		// Affichage du résultat
		cout << "The shortest path has length " << backtrack(x0, y0) << endl;
		libere(beeper_list);
	}
	return 0;
}
