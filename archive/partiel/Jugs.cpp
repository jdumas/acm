#include <iostream>
#include <vector>
#include <string>
using namespace std;

int ca,cb,n;
bool pourainb;
vector <vector <bool> > vu;
vector <string> step;

bool parcours(int a, int b) {
	int na,nb;
	if (b == n) return true;
	if (a == n) {pourainb = true; return true;}
	if (vu[a][b]) return false;
	vu[a][b] = true;
	if (parcours(0,b))  {step.push_back("empty A"); return true;}
	if (parcours(a,0))  {step.push_back("empty B"); return true;}
	if (parcours(ca,b)) {step.push_back("fill A"); return true;}
	if (parcours(a,cb)) {step.push_back("fill B"); return true;}
	na = min(a+b,ca);
	nb = a+b-na;
	if (parcours(na,nb)) {step.push_back("pour B A"); return true;}
	nb = min(a+b,cb);
	na = a+b-nb;
	if (parcours(na,nb)) {step.push_back("pour A B"); return true;}
	return false;
}

void solve(void) {
	int i;
	step.clear();
	vu.clear();
	vu.resize(ca+1, vector <bool> (cb+1, false));
	pourainb = false;
	parcours(0,0);
	for (i = step.size(); i > 0;)
		cout << step[--i] << endl;
	if (pourainb) cout << "empty B\npour A B\n";
	cout << "success" << endl;
}

int main(void) {
	while(cin >> ca >> cb >> n)
		solve();
	return 0;
}
