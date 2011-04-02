#include <vector>
#include <complex>
using namespace std;

typedef complex<double> point;
typedef vector<point> poly;
point e(1000, 1000); // Un point a l'exterieur de la zone de travail


double inline det(const point & u, const point & v) {
	return imag(conj(u) * v);
}



// Teste si les points (a,b,c,d) sont cocycliques
bool cocycle(const point & a, const point & b, const point & c, const point & d) {
	// Vérifie que les points ne soient pas alignés
	if (det(c - a, c - b) == 0 || det(d - a, d - b) == 0)
		return false;
	return imag(((a - c) * (b - d)) / ((b - c) * (a - d))) == 0;
}


// Teste si les segments [a,b] et [c,d] s'intersectent
bool inline intersect(const point & a, const point & b, const point & c,
		const point & d) {
	double z = det(b - a, d - c);
	double x = det(c - a, b - a);
	double y = det(d - c, a - c);
	int sx = (x > 0 ? 1 : -1);
	int sy = (y > 0 ? 1 : -1);
	// On fait le test en n'utilsant que des entiers si possible
	return (z != 0 && x * z >= 0 && sx * x < sx * z && y * z >= 0 && sy * y
			< sy * z);
}


// Calcul le point d'intersection de deux droites
// Renvoie "true" si et seulement si le point d'intersection appartient aux deux segments (?)
bool segInter(const point & a, const point & b, const point & c,
		const point & d, point & inter) {
	double detSeg = det(b - a, d - c);
	double detABC = det(b - a, c - a);
	if (detSeg == 0)
		return false;
	inter = c - (d - c) * detABC / detSeg;
	return det(b - a, c - a) * det(b - a, d - a) <= 0 && det(d - c, a - c)
			* det(d - c, b - c) <= 0;
}


// Teste si le point a est a l'interieur du poligone p
bool is_inside(const point & a, const poly & p) {
	int i, n = p.size();
	bool tmp, b = false;
	for (i = 0; i < (int) p.size(); ++i) {
		tmp = intersect(a, e, p[i], p[(i + 1) % n]);
		b = (b != tmp);
	}
	return b;
}


// Renvoie l'aire du poligone t
double get_surface(poly & t) {
	double sum = 0;
	int i;
	for (i = 1; i + 1 < (int) t.size(); ++i) {
		sum += det(t[i] - t[0], t[i + 1] - t[0]);
	}
	return abs(sum / 2);
}
