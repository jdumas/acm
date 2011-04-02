/********************************************************************************
 * Algorithme de Graham
 *
 * Calcul de l'enveloppe convexe d'un ensemble de points.
 * Complexite : O(n*log(n))
 ********************************************************************************/
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;

typedef complex<double> point;
typedef vector<point> poly;

double inline det(const point & u, const point & v) {
	return imag(conj(u) * v);
}

// p0 is assumed to be the leftmost point of the poly, and should be kept at pos. 0 in the vector
struct Compare {
	point p0;
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

// Compute the convex hull of the set of point t, store it in r.
// Does not preserve the ordering of t's vertices
void convex_hull(poly & t, poly & r) {
	int i;
	Compare order;
	// Search leftmost vertex
	order.p0 = t[0];
	for (i = 1; i < (int) t.size(); ++i)
		if (t[i].real() < order.p0.real())
			order.p0 = t[i];
	sort(t.begin(), t.end(), order);
	for (i = 0; i < (int) t.size(); ++i) {
		r.push_back(t[i]);
		// Pop vertices that become internal
		while (r.size() > 3u && angle(r.end()[-3], r.end()[-2], r.end()[-1])) {
			r.end()[-2] = r.back();
			r.pop_back();
		}
	}
	return;
}
