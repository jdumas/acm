/*
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=&problem=45&mosmsg=Submission+received+with+ID+8882530
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;

typedef complex<double> point;
typedef vector<point> poly;
point e(600, 300);

double inline det(const point & u, const point & v) {
	return imag(conj(u) * v);
}

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

// Test whether [a,b] and [c,d] intersect each other
bool inline intersect(const point & a, const point & b, const point & c,
		const point & d) {
	double z = det(b - a, d - c);
	double x = det(c - a, b - a);
	double y = det(d - c, a - c);
	int sx = (x > 0 ? 1 : -1);
	int sy = (y > 0 ? 1 : -1);
	// Compute the test using only integers if possible
	return (z != 0 && x * z >= 0 && sx * x < sx * z && y * z >= 0 && sy * y
			< sy * z);
}

// Test whether point a is inside poly p
bool is_inside(const point & a, const poly & p) {
	unsigned i;
	int n = p.size();
	bool tmp, b = false;
	for (i = 0; i < p.size(); ++i) {
		tmp = intersect(a, e, p[i], p[(i + 1) % n]);
		b = (b != tmp);
	}
	return b;
}

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
	int i;
	point p;
	double s = 0;
	vector<poly> kingdom;
	vector<bool> destroyed;
	poly kingdom_sites, kingdom_border;
	Compare order;
	while (1) {
		cin >> i;
		if (i == -1) break;
		kingdom_sites.clear();
		order.init();
		for (; i; --i) {
			cin >> p.real() >> p.imag();
			if (p.real() < order.p0.real())
				order.p0 = p;
			kingdom_sites.push_back(p);
		}
		convex_hull(kingdom_sites, kingdom_border, order);
		kingdom.push_back(kingdom_border);
	}
	// Compute missile attacks
	destroyed.resize(kingdom.size());
	while (cin >> p.real() >> p.imag()) {
		for (i = kingdom.size(); i;) {
			if (destroyed[--i]) continue;
			if (is_inside(p, kingdom[i])) {
				destroyed[i] = true;
				s += get_surface(kingdom[i]);
				i = 0;
			}
		}
	}
	printf("%.2f\n",s);
	return 0;
}
