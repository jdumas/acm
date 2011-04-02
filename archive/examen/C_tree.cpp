#include <iostream>
#include <string>
#include <vector>
using namespace std;

string pre, ino, pos;

void compute(int i1, int i2, int j1, int j2) {
	int d;
	if (i1 >= i2) return;
	for(d = 0; ino[j1 + d] != pre[i1]; ++d);
	compute(i1 + 1, i1 + d + 1, j1, j1 + d);
	compute(i1 + d + 1, i2, j1 + d + 1, j2);
	pos.push_back(pre[i1]);
	return;
}

int main(void) {
	while (cin >> pre >> ino) {
		pos.clear();
		compute(0,pre.size(),0, ino.size());
		cout << pos << endl;
	}
	return 0;
}
