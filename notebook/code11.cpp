// Exponentiation modulaire rapide : y = (x ^ n) % m
int mod_pow(int x, int n, int m) {
	int y = 1;
	while (n != 0) {
		if ((n & 1) == 1)
			y = (y * x) % m;
		x = (x * x) % m;
		n = n >> 1;
	}
	return y;
}

// Si p est premier, renvoie y tel que x*y = 1 [p].
// Utilise le petit theoreme de fermat qui dit que x^(p-1) = 1 [p] si p premier.
int inv_mod(int x, int p) {
	return mod_pow(x, p - 2, p);
}

// Remplace un couple (x,y) par (px,py) premiers entre eux, avec m = pgcd(x,y)
void normalize(int &x, int &y) {
	int m = x, n = y;
	while (n) {
		m %= n;
		swap(m, n);
	}
	x /= m;
	y /= m;
	return;
}

// Calcule (u,v) tel que a*u + b*v = r, et renvoie r = pgcd(a,b).
int bezout(int &a, int &b, int &u, int &v) {
	int r = a, r1 = b;
	int q, rs, us, vs;
	int u1, v1;
	u  = 1, v  = 0;
	u1 = 0, v1 = 1;
	while (r1) {
		q = r / r1;
		rs = r; us = u; vs = v;
		r = r1; u = u1; v = v1;
		r1 = rs - q * r1;
		u1 = us - q * u1;
		v1 = vs - q * v1;
	}
	return r;
}





// Coefficients binomiaux
int binom(int k, int n) {
	int i, res = 1;
	for (i = 1; i <= k; ++i)
		res = (n - k + i) * res / i;
	return res;
}

// Test de primalite
bool isprime(int n) {
	if (n == 0 || n == 1)
		return false;
	else if (n == 2 || n == 3 || n == 5 || n == 7)
		return true;
	else if (n % 2 == 0 || n % 3 == 0)
		return false;
	else {
		for (int i = 5; i * i <= n; i += 6)
			if (n % i == 0 || n % (i + 2) == 0)
				return false;
		return true;
	}
}

/********************************************************************************
 * Crible d'Eratosthenes
 *
 * Et test de primalite avec precalcul des nombres premiers.
 ********************************************************************************/

#include <vector>
using namespace std;

// Crible d'Eratosthenes
void sieve(vector<bool> & crossed, int limit) {
	int i,j;
	crossed.clear();
	crossed.resize(limit / 2, false);
	crossed[0] = true;
	for (i = 1; 4*i*i < limit; ++i) {
		if (crossed[i]) continue;
		for (j = 2*i*(i+1); 2*j < limit; j += 2*i+1)
			crossed[j] = true;
	}
	return;
}

// Test de primalite
bool isprime(vector<bool> & crossed, int i) {
	if (i == 2) return true;
	if (i % 2 == 0) return false;
	return not crossed[(i-1)/2];
}
