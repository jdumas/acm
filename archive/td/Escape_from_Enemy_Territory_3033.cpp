#include <iostream>
#include <vector>
#include <deque>
using namespace std;

typedef vector<vector<unsigned> > matrix;
typedef deque<pair<int, int> > points;

matrix world;
matrix result;
points to_explore;
points to_explore_next;
int m, n, xs, ys, xa, ya;
unsigned threshold;
bool stop;

void inline first_pass_op(int a, int b, unsigned d) {
	if (world[a][b] != ~0u) return;
	world[a][b] = d;
	to_explore.push_back(make_pair(a, b));
	return;
}

// Déterminer la distance d'un point à une base
void first_pass(void) {
	int x, y;
	unsigned d;
	while (!to_explore.empty()) {
		x = to_explore.front().first;
		y = to_explore.front().second;
		d = world[x][y] + 1;
		to_explore.pop_front();
		if (x + 1 < n) first_pass_op(x + 1, y, d);
		if (x     > 0) first_pass_op(x - 1, y, d);
		if (y + 1 < m) first_pass_op(x, y + 1, d);
		if (y     > 0) first_pass_op(x, y - 1, d);
	}
	return;
}

void inline second_pass_op(int x1, int y1, int x0, int y0) {
	// On a atteint le sommet de départ
	if (x1 == xs && y1 == ys) stop = true;
	// Le sommet a déjà été visité
	if (result[x1][y1] != ~0u) return;
	unsigned s0 = result[x0][y0];
	unsigned s1 = min(world[x1][y1], s0);
	result[x1][y1] = s1;
	if (s0 == s1) to_explore.push_back(make_pair(x1, y1));
	else     to_explore_next.push_back(make_pair(x1, y1));
}

// Déterminer un chemin de sécurité maximale
void second_pass(void) {
	int x, y;
	stop = false;
	result.clear();
	result.resize(n, vector<unsigned> (m, -1));
	result[xa][ya] = world[xa][ya];
	to_explore.push_back(make_pair(xa, ya));
	while (!stop && !to_explore.empty()) {
		// Récupérer le sommet en tête
		x = to_explore.front().first;
		y = to_explore.front().second;
		to_explore.pop_front();
		// Visiter les voisins
		if (x + 1 < n) second_pass_op(x + 1, y, x, y);
		if (x     > 0) second_pass_op(x - 1, y, x, y);
		if (y + 1 < m) second_pass_op(x, y + 1, x, y);
		if (y     > 0) second_pass_op(x, y - 1, x, y);
		// On doit passe à un chemin de sécurité plus faible
		if (to_explore.empty())
			swap(to_explore, to_explore_next);
	}
	threshold = result[xs][ys];
	to_explore.clear();
	to_explore_next.clear();
	return;
}

void inline third_pass_op(int x1, int y1, int x0, int y0) {
	// On a atteint le sommet de départ
	if (x1 == xs && y1 == ys) stop = true;
	// Le sommet a déjà été visité
	if (result[x1][y1] != ~0u) return;
	// Le sommet est trop proche d'une base
	if (world[x1][y1] < threshold)    return;
	result[x1][y1] = 1 + result[x0][y0];
	to_explore.push_back(make_pair(x1, y1));
}

// Déterminer un plus court chemin de sécurité >= threshold
void third_pass(void) {
	int x, y;
	stop = false;
	result.clear();
	result.resize(n, vector<unsigned> (m, -1));
	result[xa][ya] = 0;
	to_explore.push_back(make_pair(xa, ya));
	while (!stop && !to_explore.empty()) {
		x = to_explore.front().first;
		y = to_explore.front().second;
		to_explore.pop_front();
		if (x + 1 < n) third_pass_op(x + 1, y, x, y);
		if (x     > 0) third_pass_op(x - 1, y, x, y);
		if (y + 1 < m) third_pass_op(x, y + 1, x, y);
		if (y     > 0) third_pass_op(x, y - 1, x, y);
	}
	to_explore.clear();
	return;
}

int main(void) {
	int ntest, nbase, x, y;
	cin >> ntest;
	for (; ntest; ntest--) {
		cin >> nbase >> n >> m;
		cin >> xs >> ys >> xa >> ya;
		world.clear();
		world.resize(n, vector<unsigned> (m, -1));
		for (; nbase; --nbase) {
			cin >> x >> y;
			world[x][y] = 0;
			to_explore.push_back(make_pair(x, y));
		}
		first_pass();
		second_pass();
		third_pass();
		cout << threshold << " " << result[xs][ys] << endl;
	}
	return 0;
}
