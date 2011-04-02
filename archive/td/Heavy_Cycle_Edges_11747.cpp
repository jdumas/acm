#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
	int x, y, w;
	edge(void) :
		x(), y(), w() {}
	edge(int a, int b, int c) :
		x(a), y(b), w(c) {}
	bool operator<(const edge & e) const {
		return w < e.w;
	}
};

typedef vector<edge> tree;
vector<int> pere;

void init(int n) {
	int i;
	pere.resize(n);
	for (i = 0; i < n; ++i)
		pere[i] = i;
	return;
}

int find(int i) {
	if (pere[i] == i) return i;
	pere[i] = find(pere[i]);
	return pere[i];
}

void merge(int i, int j) {
	pere[find(i)] = find(j);
	return;
}

void compute(vector<edge> e, int n) {
	int i, last = -1;
	init(n);
	for (i = 0; i < (int) e.size(); ++i) {
		if (find(e[i].x) == find(e[i].y)) {
			if (e[i].w == last) continue;
			cout << (last == -1 ? "" : " ") << e[i].w;
			last = e[i].w;
		} else
			merge(e[i].x, e[i].y);
	}
	if (last == -1)
		cout << "forest";
	cout << endl;
}

int main(void) {
	int n, m, x, y, w;
	vector<vector<int> > g;
	tree e;
	while (1) {
		cin >> n >> m;
		if (n == 0 && m == 0) break;
		g.resize(n);
		for (; m; --m) {
			cin >> x >> y >> w;
			g[x].push_back(y);
			g[y].push_back(x);
			e.push_back(edge(x, y, w));
		}
		sort(e.begin(), e.end());
		compute(e, n);
		g.clear();
		e.clear();
	}
	return 0;
}
