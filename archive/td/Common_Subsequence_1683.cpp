#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int lcs(const string s1, const string s2) {
	const int n = s1.length()+1, m = s2.length()+1;
	int i, j;
	vector <vector <int> > v;
	v.resize(n, vector <int> (m,0));
	for (i = 1; i < n; i++) {
		for (j = 1; j < m; j++) {
			if (s1[i-1] == s2[j-1])
				v[i][j] = 1 + v[i - 1][j - 1];
			else
				v[i][j] = max (v[i][j - 1], v[i - 1][j]);
		}
	}
	return v[n-1][m-1];
}

int main(void) {
	string s1, s2;
	while (cin >> s1 >> s2) {
		cout << lcs(s1, s2) << endl;
	}
	return 0;
}
