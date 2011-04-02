#include <iostream>
#include <complex>
#include <vector>
using namespace std;

typedef complex<double> point;
vector<string> resp;
vector<point> v;

// Teste si x ≈ 0
#define zero(x) (abs(x) < 1e-10)
// Déterminant de (u,v)
#define det(u, v) imag(conj(u) * (v))

// Teste si les points d'indices i,j,k et l sont cocycliques
void check(int i, int j, int k, int l) {
	point a = v[i], b = v[j], c = v[k], d = v[l];
	point tmp;
	if (zero(det(c - a, c - b)) || zero(det(d - a, d - b)))
		return;
	tmp = ((a - c) * (b - d)) / ((b - c) * (a - d));
	if (! zero(tmp.imag()))
		return;
	string s(4, 'A');
	s[0] += i;
	s[1] += j;
	s[2] += k;
	s[3] += l;
	resp.push_back(s);
	return;
}

int main(void) {
	int n, i, j, k, l;
	point p;
	while (1) {
		cin >> n;
		if (!n)
			break;
		v.clear();
		resp.clear();
		for (i = 0; i < n; i++) {
			cin >> p.real() >> p.imag();
			v.push_back(p);
		}
		for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
		for (k = j + 1; k < n; k++)
		for (l = k + 1; l < n; l++)
			check(i, j, k, l);
		n = resp.size();
		cout << n << endl;
		for (i = 0; i < n; i++)
			cout << resp[i] << endl;
	}
	return 0;
}
