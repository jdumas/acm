#include <iostream>
#include <complex>
#include <vector>
using namespace std;

typedef complex<double> point;
typedef vector<point> poly;
point e (0, 10); // The faraway point ... well, it's not so faraway after all

double inline det(const point & u, const point & v) {
	return imag(conj(u) * v);
}

// Test whether [a,b] and [c,d] intersect each other
bool inline intersect(const point & a, const point & b, const point & c,
		const point & d) {
	double z = det(b - a, d - c);
	double x = det(c - a, b - a);
	double y = det(d - c, a - c);
	int sx = (x > 0 ? 1 : -1);
	int sy = (y > 0 ? 1 : -1);
	// Compute the test using only integers if possible
	return (z != 0 && x*z >= 0 && sx*x < sx*z
				   && y*z >= 0 && sy*y < sy*z);
}

// Test whether point a is inside poly p
bool is_inside(const point & a, const poly & p) {
	unsigned i;
	int n = p.size();
	bool tmp, b = false;
	for (i = 0; i < p.size(); i++) {
		tmp = intersect(a, e, p[i], p[(i + 1) % n]);
		b = (b != tmp);
	}
	return b;
}

// Test whether the submarine {a,b} is beached on the island p or not
unsigned test_island(const point & a, const point & b, const poly & p) {
	unsigned i, n = p.size();
	bool tmp;
	for (i = 0; i < n; i++) {
		tmp = intersect(a, b, p[i], p[(i + 1) % n]);
		if (tmp)
			return 2; // Partially on land
	}
	tmp = is_inside(a, p);
	if (tmp)
		return 3; // Entirely on land
	return 1; // Still in water
}

int main(void) {
	unsigned n, k;
	point a, b, c, d;
	poly island;
	vector<pair<point, point> > sub;
	vector<int> state;
	cin >> n;
	state.resize(n, 0);
	// Read submarine entries from standard input
	for (; n; n--) {
		cin >> a.real() >> a.imag() >> b.real() >> b.imag();
		sub.push_back(make_pair(a, b));
	}
	// Read island entries from standard input
	for (cin >> n; n; n--) {
		island.clear();
		for (cin >> k; k; k--) {
			cin >> a.real() >> a.imag();
			island.push_back(a);
		}
		// Test if a submarine is beached to that island
		for (k = 0; k < sub.size(); k++) {
			if (state[k] <= 1)
				state[k] = test_island(sub[k].first, sub[k].second, island);
		}
	}
	// Output the final states of the submarines
	for (k = 0; k < sub.size();) {
		switch (state[k++]) {
		case 1:
			cout << "Submarine " << k << " is still in water." << endl;
			break;
		case 2:
			cout << "Submarine " << k << " is partially on land." << endl;
			break;
		default:
			cout << "Submarine " << k << " is completely on land." << endl;
		}
	}
	return 0;
}
