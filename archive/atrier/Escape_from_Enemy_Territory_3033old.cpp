#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <list>
using namespace std;

typedef vector<vector<unsigned> > map_matrix;
typedef vector<vector<pair<unsigned, unsigned> > > res_matrix;
typedef queue<pair<int, int> > points;

struct cell {
	points l;
	unsigned dist;
	cell(points arg_l, int arg_d) :
		l(arg_l), dist(arg_d) {
	}
};

typedef list<cell> subsetcell;

map_matrix world;
res_matrix result;
points to_explore;
subsetcell path;
int m, n, xs, ys, xa, ya;

void inline traiter(int a, int b, unsigned d) {
	if (world[a][b] <= d)
		return;
	world[a][b] = d;
	to_explore.push(make_pair(a, b));
	return;
}

void first_pass(void) {
	int x, y;
	unsigned d;
	while (!to_explore.empty()) {
		x = to_explore.front().first;
		y = to_explore.front().second;
		d = world[x][y] + 1;
		to_explore.pop();
		if (x + 1 < n)
			traiter(x + 1, y, d);
		if (x > 0)
			traiter(x - 1, y, d);
		if (y + 1 < m)
			traiter(x, y + 1, d);
		if (y > 0)
			traiter(x, y - 1, d);
	}
	return;
}

void insert_new_list(subsetcell::iterator it, int x, int y) {
	path.insert(it, cell(points(deque<pair<int, int> > (1, make_pair(x, y))),
			result[x][y].first));
	return;
}

// Visite du sommet (x1,y1)
void inline visiter(subsetcell::iterator it, int x1, int y1, int x0, int y0) {
	unsigned d0, d1;
	subsetcell::iterator it_aux = it;
	if (result[x1][y1].first != ~0u)
		return;
	d0 = result[x0][y0].first;
	result[x1][y1].first = min(world[x1][y1], d0);
	d1 = result[x1][y1].first;
	result[x1][y1].second = 1 + result[x0][y0].second;
	if (d1 == d0) {
		it->l.push(make_pair(x1, y1));
		return;
	}
	++it_aux;
	if (it_aux != path.end() && it_aux->dist == d1)
		it_aux->l.push(make_pair(x1, y1));
	else
		insert_new_list(it_aux, x1, y1);
}

void second_pass(void) {
	int x, y;
	unsigned current_dist = 0;
	subsetcell::iterator it;
	result[xa][ya].first = world[xa][ya];
	insert_new_list(path.begin(), xa, ya);
	while (!path.empty()) {
		// Récupérer le sommet en tête
		it = path.begin();
		x = it->l.front().first;
		y = it->l.front().second;
		//cout << x << "," << y << ":" << result[x][y].first << "-" << result[x][y].second << endl;
		// Visiter les voisins
		if (x + 1 < n)
			visiter(it, x + 1, y, x, y);
		if (x > 0)
			visiter(it, x - 1, y, x, y);
		if (y + 1 < m)
			visiter(it, x, y + 1, x, y);
		if (y > 0)
			visiter(it, x, y - 1, x, y);
		// Retirer le sommet visité de l'ensemble
		it->l.pop();
		if (it->l.empty())
			path.erase(it);
	}
	return;
}

int main(void) {
	int ntest, nbase, x, y;
	cin >> ntest;
	for (; ntest; ntest--) {
		cin >> nbase >> n >> m;
		world.clear();
		result.clear();
		world.resize(n, vector<unsigned> (m, -1));
		result.resize(n,
				vector<pair<unsigned, unsigned> > (m, make_pair(-1, 0)));
		cin >> xs >> ys >> xa >> ya;
		for (; nbase; --nbase) {
			cin >> x >> y;
			world[x][y] = 0;
			to_explore.push(make_pair(x, y));
		}
		first_pass();
		second_pass();
		cout << result[xs][ys].first << " " << result[xs][ys].second << endl;
		/*for (x = 0; x < n; ++x) {
			for (y = 0; y < m; ++y) {
				cout << world[x][y] << ";";
			}
			cout << endl;
		}*/
	}
	return 0;
}
