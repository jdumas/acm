/*
 * http://livearchive.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=43&problem=2451&mosmsg=Submission+received+with+ID+806777
 */

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <vector>
#include <complex>
#include <string>
#include <algorithm>
using namespace std;
typedef complex<double> point;
typedef vector<point> poly;

poly saplings;
int n, m;

double inline det(const point & u, const point & v) {
	return imag(conj(u) * v);
}

struct Compare {
	point p0;
	void init(void) {
		p0 = point(1. / 0., 1. / 0.);
	}
	bool operator ()(const point & p1, const point & p2) {
		double d = det(p1 - p0, p2 - p0);
		if (p1 == p0) return true;
		if (p2 == p0) return false;
		return (d < 0 || (d == 0 && abs(p1 - p0) < abs(p2 - p0)));
	}
};

bool inline angle(point & a, point & b, point & c) {
	return (det(b - a, c - a) >= 0);
}

void convex_hull(poly & t, poly & r) {
	unsigned i;
	Compare order;
	// Search leftmost vertex
	order.p0 = t[0];
	for (i = 1; i < t.size(); ++i)
		if (t[i].real() < order.p0.real())
			order.p0 = t[i];
	sort(t.begin(), t.end(), order);
	for (i = 0; i < t.size(); ++i) {
		r.push_back(t[i]);
		// Pop vertices that become internal
		while (r.size() > 3u && angle(r.end()[-3], r.end()[-2], r.end()[-1])) {
			r.end()[-2] = r.back();
			r.pop_back();
		}
	}
	return;
}

double get_fence_length(poly & r) {
	double sum = 2*arg(point(-1,0))*m;
	unsigned i, k = r.size();
	for (i = 0; i < k; ++i) {
		sum += abs(r[i] - r[(i+1)%k]);
	}
	return sum;
}

double get_fence(unsigned s) {
	poly v, r;
	int i;
	// Reconstruire le groupe de sapling correspondant à s
	for (i = 0; i < n; ++i)
		if (s & (1u << i))
			v.push_back(saplings[i]);
	// Puis calculer l'enveloppe convexe
	convex_hull(v, r);
	// Enfin calculer la longueur de la clôture utilisée pour cette enveloppe
	return get_fence_length(r);
}

double solve(void) {
	vector <double> t;
	double m;
	unsigned s, y;
	t.resize(1u << n);
	// Pour tout subset s de {1...n}
	for (s = 1u; s < 1u << n; ++s) {
		// 1er cas, notre clôture contient tout s
		m = get_fence(s);
		// Pour tout y
		for (y = 1u; y < s; ++y) {
			// Si y contient un élément qui n'est pas dans s
			if (y & ~s) continue;
			// 2e cas, on enclot un subset strict et son complémentaire dans s
			m = min(m, t[s & ~y] + t[y]);
		}
		t[s] = m;
	}
	return t[(1u << n) - 1];
}

int main(void) {
	int x, y, i, k = 0;
	point p;
	while (1) {
		cin >> n >> m;
		if (n == 0 && m == 0) break;
		saplings.clear();
		for (i = 0; i < n; ++i) {
			cin >> x >> y;
			p = point(x,y);
			saplings.push_back(p);
		}
		printf("Case %d: length = %.2f\n", ++k, solve());
	}
	return 0;
}
