#include <iostream>
#include <vector>
using namespace std;

typedef vector<unsigned> tab1;
typedef vector<tab1> tab2;
typedef vector<tab2> tab3;

int solve(int m, int k) {
	int u, v, i, p;
	tab3 t(k, tab2(m + 1, tab1(m + 1, 0)));
	for (u = 0; u <= m; ++u)
		for (v = u + 1; v <= m; ++v)
			t[0][u][v] = v + t[0][u][v - 1];
	for (i = 1; i < k; ++i)
		for (u = m; u >= 0; --u)
			for (v = u + 1; v <= m; ++v) {
				t[i][u][v] = ~0u;
				for (p = u + 1; p <= v; ++p)
					t[i][u][v] = min(t[i][u][v], p + max(t[i][p][v],
							t[i - 1][u][p - 1]));
			}
	return t[k - 1][0][m];
}

int main(void) {
	int n, m, k;
	for (cin >> n; n; --n) {
		cin >> k >> m;
		cout << solve(m, k) << endl;
	}
	return 0;
}

