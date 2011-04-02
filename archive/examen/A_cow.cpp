#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int> > matrix;

int inline val(char c) {
	switch (c) {
	case 'A': return 1;
	case 'T': return 10;
	case 'J': return 11;
	case 'Q': return 12;
	case 'K': return 13;
	default:  return (int) (c - '0');
	}
}

int solve(matrix & t) {
	int i, j, n = t.size();
	for (i = 1; i < n; ++i) {
		t[0][i] = t[0][i] + t[0][i - 1];
		t[i][0] = t[i][0] + t[i - 1][0];
	}
	for (i = 1; i < n; ++i)
		for (j = 1; j < n; ++j)
			t[i][j] = t[i][j] + max(t[i - 1][j], t[i][j - 1]);
	return t[n - 1][n - 1];
}

int main(void) {
	matrix t;
	int n, i, j;
	string s;
	cin >> n;
	t.resize(n, vector<int> (n, 0));
	for (i = n - 1; i >= 0; --i) {
		for (j = 0; j < n; ++j) {
			cin >> s;
			t[i][j] = val(s[0]);
		}
	}
	cout << solve(t) << endl;
}
