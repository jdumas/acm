/*
 * 4609-an-industrial-spy.cpp
 *
 * http://livearchive.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=362&page=show_problem&problem=2610
 */

#include <set>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
T fromString(const string& s) {
	istringstream stream(s);
	T t;
	stream >> t;
	return t;
}

// Crible d'Eratosthènes
void sieve(vector<bool> & crossed, int limit) {
	int i, j;
	crossed.clear();
	crossed.resize(limit / 2, false);
	crossed[0] = true;
	for (i = 1; 4 * i * i < limit; ++i) {
		if (crossed[i])
			continue;
		for (j = 2 * i * (i + 1); 2 * j < limit; j += 2 * i + 1)
			crossed[j] = true;
	}
	return;
}

// Test de primalité
bool isprime(vector<bool> & crossed, int i) {
	if (i == 2)
		return true;
	if (i % 2 == 0)
		return false;
	return not crossed[(i - 1) / 2];
}

// Test the decimal writing
bool ismadeof(int i, vector<char> & elements) {
	vector<char> count(10, 0);
	for (; i; i /= 10)
		++count[i % 10];
	for (i = 0; i < 10; ++i)
		if (count[i] > elements[i])
			return false;
	return true;
}

// Main algorithm
int solve(vector<bool> & crossed, int upper) {
	int counter = 0;
	vector<char> elements(10, 0);
	// Digit counter
	for (int n = upper; n; n /= 10)
		++elements[n % 10];
	for (int i = 2; i < upper; ++i) {
		// Skip numbers that are not written with 'elements'
		for (int j = 1000000; j > 0;)
			if (i >= j && not ismadeof(i / j, elements)) {
				i += j;
				j = 1000000;
			} else
				j /= 10;
		// If the remaining is prime, then count it
		if (isprime(crossed, i))
			++counter;
	}
	return counter;
}

int main(void) {
	int c, n;
	string s;
	vector<bool> crossed;
	sieve(crossed, 10000000);
	for (cin >> c; c; --c) {
		cin >> s;
		sort(s.rbegin(), s.rend());
		n = fromString<int> (s);
		cout << solve(crossed, n) << endl;
	}
}
