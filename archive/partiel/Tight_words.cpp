#include <iostream>
#include <cstdio>
#include <math.h>
#include <vector>
using namespace std;


double nb_tight(int n, int k) {
	int i, p;
	double m = 0;
	vector<vector <double> > t (n, vector <double> (k+1, 1));
	for (p = 1; p < n; ++p)
		for (i = 0; i <= k; ++i)
			t[p][i] = t[p-1][i]
				+ (i > 0 ? t[p-1][i-1] : 0)
				+ (i < k ? t[p-1][i+1] : 0);
	for (i = 0; i <= k; ++i)
		m += t[n-1][i];
	return m;
}

int main(void) {
	int n, k;
	double r;
	while (cin >> k >> n) {
		r = nb_tight(n,k);
		r = 100 * r / pow(k+1, n);
		printf("%.5f\n", r);
	}
	return 0;
}
