#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
using namespace std;

typedef map<string, vector<int> > adj;
typedef vector<adj> graph;
typedef pair<int, int> coord;

int crossed_bfs(graph & g, graph & f, coord source, coord dest) {
	vector<vector<bool> > vu(g.size(), vector<bool> (f.size(), false));
	vector<int>::iterator p, q;
	stack<coord> st, next;
	adj::iterator it1, it2;
	int i, j, dist = 1;
	st.push(make_pair(source.first, source.second));
	vu[source.first][source.second] = true;
	while (not st.empty()) {
		i = st.top().first;
		j = st.top().second;
		st.pop();
		for (it1 = g[i].begin(); it1 != g[i].end(); ++it1) {
			it2 = f[j].find(it1->first);
			if (it2 == f[j].end()) continue;
			for (p = it1->second.begin(); p != it1->second.end(); ++p) {
				for (q = it2->second.begin(); q != it2->second.end(); ++q) {
					if (vu[*p][*q]) continue;
					if (*p == dest.first && *q == dest.second)
						return dist;
					next.push(make_pair(*p, *q));
					vu[*p][*q] = true;
				}
			}
		}
		if (st.empty()) {
			swap(st, next);
			++dist;
		}
	}
	return -1;
}

int main(void) {
	int n, i, j, l, d, p;
	graph g, f;
	coord dest;
	string s;
	for (cin >> n; n; --n) {
		cin >> l >> d >> p;
		dest.first = d;
		g.resize(l);
		for (; p; --p) {
			cin >> i >> s >> j;
			g[i][s].push_back(j);
		}
		cin >> l >> d >> p;
		dest.second = d;
		f.resize(l);
		for (; p; --p) {
			cin >> i >> s >> j;
			f[i][s].push_back(j);
		}
		d = crossed_bfs(g, f, make_pair(0, 0), dest);
		cout << d << endl;
		if (n > 1) cout << endl;
		g.clear();
		f.clear();
	}
}
