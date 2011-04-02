#include <iostream>
#include <complex>
#include <vector>
using namespace std;

typedef complex<double> point;
typedef vector<point> poly;
typedef vector<poly> islands;
typedef pair<point, point> segment;
typedef vector<segment> submarines;

double inline det(const point & u, const point & v) {
	return imag(conj(u)*v);
}

bool inline interserct(const point& a, const point& b, const point& c, const point& d) {
	double h1, h2;
	h2 = det(b-a, d-c);
	if (h2 == 0.)
		return false;
	h1 = det(c-a, b-a);
	if ((h1 / h2) >= 1 || (h1 / h2) < 0)
		return false;
	h1 = det(d-c, a-c);
	if ((h1 / h2) >= 1 || (h1 / h2) < 0)
		return false;
	return true;
}

bool is_inside(const point & a, const poly & p) {
	int i,n=p.size(),k=0;
	point s, e (1001,1001);
	double d;
	bool tmp, nb_inter = true;
	/* Manière propre, mais peu efficace,
	de trouver un "bon" point en dehors du poly */
	/*for (i = 0; i < n; i++) {
		d = det(e-a, p[i]-a);
		if (d == 0.) {
			e.real()++;
			i = 0;
		}
	}*/
	for (i = 0; i < n; i++) {
		tmp = interserct(a,e,p[i], p[(i+1) % n]);
		nb_inter = (nb_inter != tmp);
		if (tmp) k++;
	}
	cout << nb_inter;
	cout << k << endl;
	return nb_inter;
}

unsigned test_island(const segment & m, const poly & p) {
	unsigned i,n=p.size();
	bool tmp;
	for (i = 0; i < n; i++) {
		tmp = interserct(m.first,m.second,p[i], p[(i+1) % n]);
		if (tmp)
			cout << "ga !" << endl;
		if (tmp)
			return 2; // Partially on land
	}
	tmp = is_inside(m.first, p);
	if (tmp)
		return 3; // Entirely on land
	return 1; // Still in water
}

unsigned where_is_my_submarine(const segment & m, const islands & l) {
	unsigned i, tmp;
	for (i = 0; i < l.size(); i++) {
		tmp = test_island(m, l[i]);
		if (tmp > 1)
			return tmp;
	}
	return 1;
}

int main(void) {
	double x1,y1,x2,y2;
	unsigned n,k;
	point tmp1, tmp2;
	poly tmp_island;
	islands my_world;
	segment tmp_sub;
	submarines my_submarines;
	for (cin >> n; n; n--) {
		cin >> x1 >> y1 >> x2 >> y2;
		tmp1 = point (x1,y1);
		tmp2 = point (x2,y2);
		tmp_sub = segment (tmp1, tmp2);
		my_submarines.push_back(tmp_sub);
	}
	for (cin >> n; n; n--) {
		tmp_island.clear();
		for (cin >> k; k; k--) {
			cin >> x1 >> y1;
			tmp1 = point (x1,y1);
			tmp_island.push_back(tmp1);
		}
		my_world.push_back(tmp_island);
	}
	for (n = 0; n < my_submarines.size();) {
		k = where_is_my_submarine(my_submarines[n], my_world);
		n++;
		switch (k) {
		case 1:
			cout << "Submarine " << n << " is still in water." << endl;
			break;
		case 2:
			cout << "Submarine " << n << " is partially on land." << endl;
			break;
		default:
			cout << "Submarine " << n << " is completely on land." << endl;
		}
	}
	return 0;
}
