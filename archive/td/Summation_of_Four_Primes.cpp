#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

#define NMAX 10000000

// Crible d'Eratosthènes
void sieve(vector<bool> & crossed, int limit) {
	int i,j;
	crossed.resize(limit / 2, false);
	crossed[0] = true;
	for (i = 1; 4*i*i < limit; ++i) {
		if (crossed[i]) continue;
		for (j = 2*i*(i+1); 2*j < limit; j += 2*i+1)
			crossed[j] = true;
	}
	return;
}

// Test de primalité
bool isprime(vector<bool> & crossed, int i) {
	if (i == 2) return true;
	if (i % 2 == 0) return false;
	return not crossed[(i-1)/2];
}

// Peut-on écrire n = p1 + p2 avec p1, p2 premiers ?
int goldbach(vector<bool> & crossed, vector<int> & prime, int n) {
	int i;
	for (i=0; i < (int) prime.size() && prime[i] < n; ++i) {
		if (isprime(crossed, n-prime[i]))
			return prime[i];
	}
	return 0;
}

// Peut-on écrire n = p1 + p2 + p3 + p4 avec p1, p2, p3, p4 premiers ?
void sum_of_four(vector<bool> & crossed, vector<int> & prime, int n) {
	int a,b,c;
	if (n % 2 == 0) {
		a = 2, b = 2;
		c = goldbach(crossed, prime, n - 4);
	} else {
		a = 2, b = 3;
		c = goldbach(crossed, prime, n - 5);
	}
	if (c == 0) cout << "Impossible." << endl;
	else cout << a << " " << b << " " << c << " " << (n-a-b-c) << endl;
	return;
}

int main(void) {
	vector<bool> crossed;
	vector<int> prime;
	int n;
	// Précalcul
	sieve(crossed, NMAX);
	prime.push_back(2);
	for (int i = 0; i < (int) crossed.size(); ++i) {
		if (crossed[i]) continue;
		prime.push_back(2*i+1);
	}
	// Lecture des entrées
	while(cin >> n)
		sum_of_four(crossed, prime, n);
	return 0;
}
