#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

struct node {
	vector<int> e;
	int match;
	node(void) : match(-1) {}
};

struct bipartite {
	vector<node> lg, rg;
	vector<bool> vu;
	int couplage;
	void reset(void) {
		vu.clear();
		vu.resize(lg.size(), false);
	}
	void init(int p, int q) {
		lg.resize(p);
		rg.resize(q);
		couplage = 0;
	}
	void clear(void) {
		lg.clear();
		rg.clear();
	}
};

bool explore(bipartite & g, int x) {
	int i,y,z;
	if (x == -1) return true;
	if (g.vu[x]) return false;
	g.vu[x] = true;
	for(i = 0; i < (int) g.lg[x].e.size(); ++i) {
		y = g.lg[x].e[i];
		z = g.rg[y].match;
		if (explore(g, z)) {
			g.rg[y].match = x;
			g.lg[x].match = y;
			return true;
		}
	}
	return false;
}

bool find_path(bipartite & g) {
	int i;
	for(i = 0; i < (int) g.lg.size(); ++i) {
		if (g.lg[i].match == -1 && explore(g,i))
			return true;
	}
	return false;
}

void greedy_matching(bipartite & g) {
	int i,j,k;
	for (i = 0; i < (int) g.lg.size(); ++i) {
		for (k = 0; k < (int) g.lg[i].e.size(); ++k) {
			j = g.lg[i].e[k];
			if (g.lg[i].match == -1 && g.rg[j].match == -1) {
				g.lg[i].match = j;
				g.rg[j].match = i;
				++g.couplage;
			}
		}
	}
}

void couplage_max(bipartite & g) {
	while (true) {
		g.reset();
		if (find_path(g)) ++g.couplage;
		else break;
	}
	return;
}

struct people {
	int height;
	string music;
	string sport;
	people(int h, string m, string s) :
		height(h), music(m), sport(s) {}
};

bool can_become_tuple(const people & a, const people & b) {
	bool r = true;
	r &= abs(a.height - b.height) <= 40;
	r &= a.music == b.music;
	r &= a.sport != b.sport;
	return r;
}

int main(void) {
	vector<people> boys, girls;
	int ntest, n, i, j, sl, sr;
	int a1; string a2, a3, a4;
	bipartite g;
	for (cin >> ntest; ntest; --ntest) {
		sl = 0;
		sr = 0;
		for (cin >> n; n; --n) {
			cin >> a1 >> a2 >> a3 >> a4;
			if (a2 == "M")
				boys.push_back(people(a1, a3, a4));
			else
				girls.push_back(people(a1, a3, a4));
		}
		sl = boys.size();
		sr = girls.size();
		g.init(sl, sr);
		for (i = 0; i < sl; ++i) {
			for (j = 0; j < sr; ++j) {
				if (can_become_tuple(boys[i], girls[j])) {
					g.lg[i].e.push_back(j);
					g.rg[j].e.push_back(i);
				}
			}
		}
		boys.clear();
		girls.clear();
		greedy_matching(g);
		couplage_max(g);
		cout << sl+sr-g.couplage << endl;
		g.clear();
	}
	return 0;
}
