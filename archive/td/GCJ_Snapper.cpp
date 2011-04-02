#include <iostream>
using namespace std;

int main(void) {
	int t,n,k,i;
	bool b;
	cin >> t;
	for(i=1; i <= t; ++i) {
		cin >> n >> k;
		b = (k & ((1 << n) - 1)) == ((1 << n) - 1);
		cout << "Case #" << i << ": " << (b ? "ON" : "OFF") << endl;
	}
}
