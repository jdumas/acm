#include <iostream>
#include <cstdio>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;

typedef complex<double> point;
typedef vector<point> poly;

double inline det(const point & u, const point & v) {
	return imag(conj(u) * v);
}

// p0 is assumed to be the leftmost point of the poly, and should be kept at position 0 in the vector
struct Compare {
	point p0;
	void init(void) { p0 = point(1./0., 1./0.); }
	bool operator ()(const point & p1, const point & p2) {
		double d = det(p1 - p0, p2 - p0);
		if (p1 == p0) return true;
		if (p2 == p0) return false;
		return (d < 0 || (d == 0 && abs(p1 - p0) < abs(p2 - p0)));
	}
};

double get_surface(poly & t) {
	double sum = 0;
	unsigned i;
	for (i = 1; i + 1 < t.size(); ++i) {
		sum += det(t[i] - t[0], t[i + 1] - t[0]);
	}
	return abs(sum / 2);
}

bool inline angle(point & a, point & b, point & c) {
	return (det(b - a, c - a) >= 0);
}

// Compute the convex hull of poly t, store it in r. Wreck the order of t's vertices
void convex_hull(poly & t, poly & r, Compare & order) {
	unsigned i;
	sort(t.begin(), t.end(), order);
	r.clear();
	r.push_back(t[0]);
	r.push_back(t[1]);
	for (i = 2; i < t.size(); ++i) {
		r.push_back(t[i]);
		// Pop vertices that become internal
		while (r.size() > 3u && angle(r.end()[-3], r.end()[-2], r.end()[-1])) {
			r.end()[-2] = r.back();
			r.pop_back();
		}
	}
	return;
}

int main(void) {
	int n, i;
	double s1, s2;
	point p;
	poly tile, hull;
	Compare order;
	for (i = 1; 1; ++i) {
		cin >> n;
		if (!n) break;
		tile.clear();
		order.init();
		for (; n; --n) {
			cin >> p.real() >> p.imag();
			if (p.real() < order.p0.real())
				order.p0 = p;
			tile.push_back(p);
		}
		s1 = get_surface(tile);
		convex_hull(tile, hull, order);
		s2 = get_surface(hull);
		s1 = 100 - 100 * s1 / s2;
		printf("Tile #%i\nWasted Space = %.2f %%\n\n", i, s1);
	}
	return 0;
}
