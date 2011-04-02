#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef vector<vector<int> > graph;

bool uncoloriable(graph & g) {
	int i;
	for (i = 0; i < (int) g.size(); ++i) {
		if (g[i].size() != 0)
			return false;
	}
	return true;
}

bool deuxcoloriable(graph & g) {
	vector<int> coul(g.size(), -1);
	stack<int> s;
	int i, j, x, y;
	for (i = 0; i < (int) g.size(); ++i) {
		if (coul[i] != -1)
			continue;
		coul[i] = 0;
		s.push(i);
		while (not s.empty()) {
			x = s.top();
			s.pop();
			for (j = 0; j < (int) g[x].size(); ++j) {
				y = g[x][j];
				if (coul[y] == coul[x]) return false;
				if (coul[y] != -1) continue;
				coul[y] = 1 - coul[x];
				s.push(y);
			}
		}
	}
	return true;
}

bool troiscoloriable(graph & g) {
	vector<int> coul(g.size(), -1);
	int i, j;
	for (i = 0; i < (int) g.size(); ++i) {
		++coul[i];
		if (coul[i] > 2) return false; // Limite de couleur atteinte
		for (j = 0; j < (int) g[i].size(); ++j) {
			if (coul[g[i][j]] == coul[i])
			{ --i; break; } // Backtrack
		}
	}
	return true;
}

int main(void) {
	graph g;
	int n, i, j, c;
	string s;
	while (true) {
		cin >> n;
		if (n == 0) break;
		g.resize(n);
		// Lecture de l'entrée
		for (; n; --n) {
			cin >> s;
			i = (int) (s[0] - 'A');
			for (j = 2; j < (int) s.size(); ++j)
				g[i].push_back((int) (s[j] - 'A'));
		}
		// Résolution du problème
		if      (uncoloriable(g))    c = 1;
		else if (deuxcoloriable(g))  c = 2;
		else if (troiscoloriable(g)) c = 3;
		else                         c = 4;
		// Affichage du résultat
		cout << c << (c == 1 ? " channel" : " channels") << " needed." << endl;
		g.clear();
	}
}
