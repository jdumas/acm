#include <iostream>
#include <vector>
using namespace std;

int l, sx, sy, ax, ay;
vector<vector<bool> > vu;
vector<pair<int, int> > current, next;

void inline check(int x, int y) {
	if (x < 0 || y < 0 || x >= l || y >= l) return;
	if (vu[x][y]) return;
	vu[x][y] = true;
	next.push_back(make_pair(x,y));
}

int explore(void) {
	int x,y,d = 0;
	vu[sx][sy] = true;
	current.push_back(make_pair(sx, sy));
	while (!current.empty()) {
		x = current.back().first;
		y = current.back().second;
		current.pop_back();
		if (x == ax && y == ay) break;
		check(x + 1, y + 2);
		check(x + 1, y - 2);
		check(x - 1, y + 2);
		check(x - 1, y - 2);
		check(x + 2, y + 1);
		check(x + 2, y - 1);
		check(x - 2, y + 1);
		check(x - 2, y - 1);
		if (current.empty()) {swap(current, next); ++d;}
	}
	current.clear();
	next.clear();
	return d;
}

int main(void) {
	int n;
	for (cin >> n; n; --n) {
		cin >> l >> sx >> sy >> ax >> ay;
		vu.clear();
		vu.resize(l, vector<bool> (l, false));
		cout << explore() << endl;
	}
	return 0;
}
