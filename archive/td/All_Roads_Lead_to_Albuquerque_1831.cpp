#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

typedef vector<vector <int> > matrix;

void roy_warshall(matrix & g) {
	int i, j, k, n = g.size();
	for (k = 0; k < n; ++k)
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j) {
				if (g[i][k] == INT_MAX) continue;
				if (g[k][j] == INT_MAX) continue;
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
			}
}

bool compare(const pair<int, int> & a, const pair<int, int> & b) {
	return (a.second < b.second);
}

int test_with(int h1, int h2, bool b, matrix & g, vector<bool> & assign) {
	int c, i, imax = 0, n = g.size();
	int tmp, result = INT_MAX, sum = 0;
	vector<pair<int, int> > delta (n); // Contient les différences (a_i - b_i)
	for(i = 0; i <n; ++i) {
		delta[i] = make_pair(i,g[i][h1] - g[i][h2]);
		sum += g[i][h2];
	}
	delta[h1].second -= 1; // On s'assure que h1 soit le plus petit élément
	delta[h2].second += 1; // On s'assure que h2 soit le plus grand élément
	sort(delta.begin(), delta.end(), compare); // Tri
	++sum;
	for (i = 0; i < n-1; ++i) {
		sum = sum + delta[i].second;
		c = (i+1)*(n-i-1)*g[h1][h2];
		tmp = c + (n-1)*sum;
		// Si le nouveau total est meilleur on le mémorise
		if (tmp < result) {
			result = tmp;
			imax = i;
		}
	}
	if (b)
	for (i = 0; i < n; ++i)
		assign[delta[i].first] = (i <= imax);
	return result;
}

void try_hubs(matrix & g) {
	int h1, h2, bh1 = 0, bh2 = 0, n = g.size();
	int tmp, average = INT_MAX;
	vector<bool> assign(n);
	// On essaie tous couples de hubs possibles
	for (h1 = 0; h1 < n; ++h1)
		for (h2 = h1+1; h2 < n; ++h2) {
			tmp = test_with(h1, h2, false, g, assign);
			if (tmp < average) {
				bh1 = h1;
				bh2 = h2;
				average = tmp;
			}
		}
	test_with(bh1, bh2, true, g, assign);
	// On réutilise les variables h1, h2 pour l'affichage du résultat
	h2 = (bh1 == 0 || bh2 == 0 ? 0 : (assign[0] ? 1 + bh1 : 1 + bh2));
	cout << h2;
	for (h1 = 1; h1 < n; ++h1) {
		// "assign[i] == true" signifie que i est rattaché au hub "bh1".
		h2 = (h1 == bh1 || h1 == bh2 ? 0 : (assign[h1] ? 1 + bh1 : 1 + bh2));
		cout << " " << h2;
	}
	cout << endl;
	return;
}

int main(void) {
	int total, n, m, x, y, d, i;
	matrix g;
	while(cin >> n >> m) {
		g.resize(n, vector <int> (n, INT_MAX));
		for (i = 0; i < n; ++i)
			g[i][i] = 0;
		for (i = 0; i < m; ++i) {
			cin >> x >> y >> d;
			--x; --y;
			g[x][y] = min(g[x][y],d);
			g[y][x] = min(g[y][x],d);
		}
		roy_warshall(g);
		try_hubs(g);
		g.clear();
	}
	return 0;
}
