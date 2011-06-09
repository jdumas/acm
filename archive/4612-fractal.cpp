/*
 * 4612-fractal.cpp
 *
 * Regionals 2009 :: Europe - Northwestern
 *
 * http://livearchive.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=362&page=show_problem&problem=2613
 */

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <complex>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define forn(i, n) for (int i = 0; i < (n); ++i)
#define foreach(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

typedef complex<double> point;
typedef vector<point> poly;

poly line;
vector<double> frac;

// Find out where we end up
point recurse(double d, double f) {
	if (d == 0)
		return f * (line.back() - line.front()) + line.front();
	for (int i = 0; i < (int) line.size() - 1; ++i) {
		double f1 = frac[i], f2 = frac[i + 1];
		if (f2 >= f)
			return (line[i] - line[i + 1]) / (line.front() - line.back())
					* (recurse(d - 1, (f - f1) / (f2 - f1)) - line.front())
					+ line[i];
	}
	return point(0, 0);
}

point compute(int depth, double fraction) {
	// Cumulative length of each segment of the line
	double acc = 0;
	vector<double> length;
	for (int i = 0; i < (int) line.size() - 1; ++i) {
		acc += abs(line[i] - line[i + 1]);
		length.push_back(acc);
	}
	// Compute the fraction of the total length corresponding to each point
	frac.clear();
	frac.push_back(0);
	for (int i = 0; i < (int) length.size(); ++i)
		frac.push_back(length[i] / length.back());
	// Recursive computation of the resulting point
	return recurse(depth, fraction);
}

int main(void) {
	int c, n, x, y, d;
	double f;
	point coord;
	for (cin >> c; c; --c) {
		line.clear();
		for (cin >> n; n; --n) {
			cin >> x >> y;
			line.push_back(point(x, y));
		}
		cin >> d >> f;
		coord = compute(d, f);
		printf("(%.10lf,%.10lf)\n", coord.real(), coord.imag());
	}
	return 0;
}
