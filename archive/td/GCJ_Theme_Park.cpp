#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int inline mod(int a, int b) {
	return (a % b < 0 ? b + a % b : a % b);
}

int main(void) {
	int p, i, j, t, r, k, n, g;
	ll accu;
	vector<int> group; // Size of the group 0...n
	vector<int> next;  // Next starting position of the queue
	vector<ll> gain;   // Gain obtained when the queue start at pos. 0...n
	vector<int> first; // First time seen
	for (cin >> t, p = 1; p <= t; ++p) {
		cin >> r >> k >> n;
		group.resize(n);
		next.resize(n);
		gain.resize(n, 0ll);
		first.resize(n, -1);
		for (i = 0; i < n; ++i) {
			cin >> g;
			group[i] = g;
		}
		accu = group.back();
		j = 0;
		for (i = 0; i < n; ++i) {
			accu -= group[mod(i-1,n)];
			while (accu + group[j] <= k) {
				accu += group[j];
				j = (j+1) % n;
				if (j == i) break;
			}
			gain[i] = accu;
			next[i] = j;
		}
		accu = 0ll;
		for (i = 0, j = 0; first[i] != -1 && j < r; ++j) {
			first[i] = j;
			accu += gain[i];
			i = next[i];
		}
		accu *= (r / (j - first[i]));
		j *= (r / (j - first[i]));
		for (; j < r; ++j) {
			accu += gain[i];
			i = next[i];
		}
		cout << "Case #" << p << ": " << accu << endl;
		group.clear();
		next.clear();
		gain.clear();
		first.clear();
	}
	return 0;
}
