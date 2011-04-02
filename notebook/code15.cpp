#include <vector>
using namespace std;

typedef vector<vector<int> > matrix;

// Calcul de la plus longue sous-sequence commune par programmation dynamique
int lcs(string & s1, string & s2) {
	int i, j;
	int n = s1.length();
	int m = s2.length();
	matrix v(n + 1, vector<int> (m + 1, 0));
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			if (s1[i - 1] == s2[j - 1])
				v[i][j] = 1 + v[i - 1][j - 1];
			else
				v[i][j] = max(v[i][j - 1], v[i - 1][j]);
		}
	}
	return v[n][m];
}
