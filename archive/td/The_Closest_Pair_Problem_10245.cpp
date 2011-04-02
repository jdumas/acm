#include <iostream>
#include <vector>
#include <complex>
#include <list>
#include <cstdio>
using namespace std;

typedef complex<double> point;
typedef list<point> plist;

bool compare_x(const point & x, const point & y) {
	return (x.real() < y.real());
}

bool compare_y(const point & x, const point & y) {
	return (x.imag() < y.imag());
}

void test(point & x, point & y, double & d) {
	d = min(abs(x - y), d);
	return;
}

double closest(plist & l) {
	double d1, d2, d, x;
	int i;
	plist l1, lbande;
	plist::iterator it = l.begin(), it2;
	if (l.size() <= 1) return 1. / 0.; // Return +/infty
	advance(it, l.size() / 2);
	x = it->real(); // Un point au milieu
	// Déplacer le début de la liste l dans l1
	l1.splice(l1.begin(), l, l.begin(), it);
	// Appels récursifs
	d1 = closest(l1);
	d2 = closest(l);
	d = min(d1, d2);
	// Remélanger les listes triées selon y croissants
	l.merge(l1, compare_y);
	// Filtrer les points qui sont à distances suffisament proche de la coupue
	for (it = l.begin(); it != l.end(); ++it)
		if (it->real() >= x - d && it->real() <= x + d)
			lbande.push_back(*it);
	for (it = lbande.begin(); it != lbande.end(); ++it) {
		it2 = it; ++it2;
		// On regarde quelques points après xi
		for(i = 0; i < 4 && it2 != lbande.end(); ({++it2; ++i;}))
			test(*it, *it2, d);
	}
	return d;
}

int main(void) {
	int n;
	double x, y;
	double result;
	plist l;
	while (cin >> n) {
		if (n == 0) break;
		for (; n; --n) {
			cin >> x >> y;
			l.push_back(point(x, y));
		}
		// Trier initialement selon les x croissants
		l.sort(compare_x);
		result = closest(l);
		if (result > 10000)
			printf("INFINITY\n");
		else
			printf("%.4f\n", result);
		l.clear();
	}
	return 0;
}
