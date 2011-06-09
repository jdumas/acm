/*
 * 4611-divisible-subsequences.cpp
 *
 * Regionals 2009 :: Europe - Northwestern
 *
 * http://livearchive.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=362&page=show_problem&problem=2612
 */

#include <vector>
#include <iostream>
using namespace std;

long long solve(vector<int> & seq, int d) {
	int n = seq.size();
	vector<long long> rem(d, 0);

	// Partial sums
	long long sum = 0;
	++rem[sum];
	for (int i = 0; i < n; ++i) {
		sum = (sum + seq[i]) % d;
		++rem[sum];
	}

	// Count the divisible subseq
	long long count = 0;
	for (int i = 0; i < d; ++i)
		count += rem[i] * (rem[i] - 1) / 2;

	return count;
}

int main(void) {
	int c, d, n;
	vector<int> seq;
	for (cin >> c; c; --c) {
		cin >> d >> n;
		seq.resize(n);
		for (int i = 0; i < n; ++i)
			cin >> seq[i];

		cout << solve(seq, d) << endl;

		seq.clear();
	}
}
