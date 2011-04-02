#include <cstdio>
#define get_libres(i,j) row[i] & col[j] & sqr[((i) & ~3) + ((j) & 3)]

typedef struct cell {
	unsigned  char x;
	unsigned y;
	cell * next;
	cell * prev;
} cell;

typedef struct subset {
	unsigned char n;
	cell * content;
	subset * next;
	subset * prev;
} subset;

unsigned char grille[16][16];
unsigned short row[16];
unsigned short col[16];
unsigned short sqr[16];
subset * partition = NULL;

unsigned char const numb_of_possibilities[256] = {
   0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
   4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};

// Destruction de la liste
void libere_cell(cell * &p) {
	if (p == NULL)
		return;
	libere_cell(p->next);
	delete p;
	p = NULL;
}
void libere_subset(subset * &p) {
	if (p == NULL)
		return;
	libere_subset(p->next);
	libere_cell(p->content);
	delete p;
	p = NULL;
}

// Suppression d'une cellule de la liste
void retirer(cell *p, cell * &head) {
	if (p->next != NULL)
		p->next->prev = p->prev;
	if (p->prev != NULL)
		p->prev->next = p->next;
	else
		head = p->next;
}

// Réinsertion d'une cellule dans la liste
void reinsert(cell * p, cell * &head) {
	if (p->next != NULL)
		p->next->prev = p;
	if (p->prev != NULL)
		p->prev->next = p;
	else
		head = p;
}

// Insertion d'une nouvelle cellule en début de liste
void push_front_new(cell * &head, unsigned char i, unsigned char j) {
	cell * tmp = new cell;
	tmp->x = i;
	tmp->y = j;
	tmp->next = head;
	tmp->prev = NULL;
	if (head != NULL)
		head->prev = tmp;
	head = tmp;
}

// Insertion d'une cellule en début de liste
void push_front(cell * p, cell * &head) {
	p->next = head;
	p->prev = NULL;
	if (head != NULL)
		head->prev = p;
	head = p;
}

// Insertion d'une nouvelle partie avant 'pos'
subset * insert_new_subset(subset * pos, subset * &head, unsigned char nb_pos) {
	subset * tmp = new subset;
	tmp->n = nb_pos;
	tmp->content = NULL;
	tmp->next = pos;
	if (pos != NULL) {
		pos->prev = tmp;
		tmp->prev = pos->prev;
	}
	if (pos == head)
		head = tmp;
	else
		pos->prev->next = tmp;
	return tmp;
}

// Déplacement d'une cellule
void move(cell *p, cell * &head, subset * part, subset * &head_part) {
	if (part->prev == NULL || part->prev->n + 1 != part->n)
		insert_new_subset(part, head_part, part->n - 1);
	retirer(p, head);
	push_front(p, part->prev->content);
}

subset * find_part(subset * head, unsigned char nb_pos) {
	subset * p;
	for (p = head; p != NULL || p->n < nb_pos; p = p->next);
	return p;
}

// Initialisation de la partition selon le nombre de possibilités
void make_partition(void) {
	unsigned char i, j, nb_pos;
	subset * part;
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			if (grille[i][j] != 255)
				continue;
			nb_pos = numb_of_possibilities[get_libres(i,j)];
			part = find_part(partition, nb_pos);
			if (part == NULL || part->n != nb_pos)
				part = insert_new_subset(part, partition, nb_pos);
			push_front_new(part->content, i, j);
		}
	}
	return;
}

// Initialisation de la grille
void initialize(void) {
	unsigned char i, j;
	for (i = 0; i < 16; i++) {
		row[i] = 0;
		col[i] = 0;
		sqr[i] = 0;
	}
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			row[i]					|= 1 << grille[i][j];
			col[j]					|= 1 << grille[i][j];
			sqr[(i & ~3) + (j & 3)]	|= 1 << grille[i][j];
		}
	}
	for (i = 0; i < 16; i++) {
		row[i] = ~row[i];
		col[i] = ~col[i];
		sqr[i] = ~sqr[i];
	}
	return;
}

// Backtracking
bool solve(void) {
	unsigned char i = -1, j = -1;
	if (i == -1)
		return true;
	short libres = get_libres(i,j);
	short current = 1u;
	grille[i][j] = 0;
	// On va forcer un peu !
	while (libres) {
		if (libres & 1) {
			row[i] 					&= ~current;
			col[j] 					&= ~current;
			sqr[(i & ~3) + (j & 3)]	&= ~current;
			if (solve())
				return true;
			row[i]					|= current;
			col[j]					|= current;
			sqr[(i & ~3) + (j & 3)]	|= current;
		}
		libres	>>= 1;
		current	<<= 1;
		grille[i][j]++;
	}
	grille[i][j] = 255;
	return false;
}

int main() {
	unsigned char ch, i, j;
	// Initialisation
	for (j = 0; j < 16; j++) {
		for (i = 0; i < 16; i++) {
			scanf("%c", &ch);
			grille[i][j] = (ch == '-' ? 255 : ch - 'A');
		}
		scanf("\n");
	}
	initialize();
	make_partition();
	solve();
	// Affichage du résultat
	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < 16; i++) {
			printf("%c", 'A' + grille[i][j]);
		}
		printf("\n");
	}
	return 0;
}
