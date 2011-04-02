#include <iostream>
#include <vector>
using namespace std;

typedef vector<unsigned> tab;

// Nombren de “1” dans l'écriture binaire de k
int nbun(unsigned k) {
	int i = 0;
	while (k) {
		i += (k & 1);
		k >>= 1;
	}
	return i;
}

// Quels carreaux sont retournés sur la ligne, si l'on
// tape les carreaux correspondant à l'entier “i”
unsigned inline effect(unsigned i, unsigned mask) {
	return (i ^ (i << 1) ^ (i >> 1)) & mask;
}

unsigned compute(tab & t, int r, int c) {
	unsigned i, sum, minsum = ~0u;
	unsigned mask = (1 << c) - 1;
	int j;
	tab tmp = t;
	// Brute force sur toutes les configurations possibles pour la première ligne
	for (i = 0u; i < (1u << c); ++i) {
		sum = nbun(i);
		tmp[0] = t[0] ^ effect(i, mask);
		tmp[1] = t[1] ^ i;
		// Propager l'effet sur les lignes suivantes.
		for (j = 1; j < r; ++j) {
			sum += nbun(tmp[j - 1]);
			tmp[j] ^= effect(tmp[j - 1], mask);
			if (j + 1 < r)
				tmp[j + 1] = t[j + 1] ^ tmp[j - 1];
		}
		// Mettre à jour le compteur si la configuration est admissible
		if (tmp.back() == 0u)
			minsum = min(sum, minsum);
	}
	return minsum;
}

int main(void) {
	int i, j, r, c;
	unsigned sum;
	char x;
	tab t;
	while (true) {
		cin >> r >> c;
		if (r == 0 && c == 0)
			break;
		// Acquisition des entrées
		t.resize(r, 0u);
		for (i = 0; i < r; ++i) {
			for (j = 0; j < c; ++j) {
				cin >> x;
				if (x == 'X') t[i] |= 1u << j;
			}
		}
		// Calcul
		sum = compute(t, r, c);
		// Affichage de la sortie
		if (sum == ~0u)
			cout << "Damaged billboard." << endl;
		else
			cout << "You have to tap " << sum << " tiles." << endl;
		t.clear();
	}
}
