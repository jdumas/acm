#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
	int i, j, k, p, q, n;
	cin >> n;
	vector<int> a(n), b(n), c(n), d(n);
	vector<int> t(n * n), s(n * n);
	// Lecture des entrées
	for (k = 0; k < n; ++k)
		cin >> a[k] >> b[k] >> c[k] >> d[k];
	// Calcul des sommes partielles
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j) {
			t[i * n + j] = a[i] + b[j];
			s[i * n + j] = c[i] + d[j];
		}
	// On trie les sommes
	sort(t.begin(), t.end());
	sort(s.begin(), s.end());
	i = 0, j = s.size() - 1;
	k = 0;
	while (i < (int) t.size() && j >= 0) {
		// La somme n'est pas nulle
		if (t[i] + s[j] < 0) { ++i; continue; }
		if (t[i] + s[j] > 0) { --j; continue; }
		// La somme est nulle
		for (p = i; p < (int) t.size() && t[p] + s[j] == 0; ++p);
		for (q = j; q >= 0             && t[i] + s[q] == 0; --q);
		// On avance jusqu'à p,q et on augmente le compteur intelligemment
		k += (p - i) * (j - q);
		i = p, j = q;
	}
	cout << k << endl;
}
