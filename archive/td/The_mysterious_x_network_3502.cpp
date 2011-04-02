#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int> > graph;
graph g;

int parcours(int depart, int arrivee) {
	vector<int> current, next;
	vector<bool> vu(g.size(), false);
	int i, j, d = 0;
	current.push_back(depart);
	while (!current.empty()) {
		i = current.back();
		current.pop_back();
		if (i == arrivee) break;
		for (j = 0; j < (int) g[i].size(); ++j) {
			if (vu[g[i][j]]) continue;
			vu[g[i][j]] = true;
			next.push_back(g[i][j]);
		}
		if (current.empty()) {swap(current, next); ++d;}
	}
	return d - 1;
}

int main(void) {
	int n, i, j, d;
	for (cin >> n; n; --n) {
		g.push_back(vector<int> ());
		for (cin >> i >> d; d; --d) {
			cin >> j;
			g.back().push_back(j);
		}
	}
	cin >> i >> j;
	cout << i << " " << j << " " << parcours(i, j) << endl;
	return 0;
}
