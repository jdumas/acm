#include <iostream>
#include <string>
using namespace std;

bool is_sub(string & s, string & t) {
	unsigned i=0,j;
	for (j = 0; i < s.size() && j < t.size(); ++j)
		if (s[i] == t[j]) ++i;
	return (i >= s.size());
}

int main(void) {
	string s,t;
	while (cin >> s >> t)
		cout << (is_sub(s,t) ? "Yes" : "No") << endl;
	return 0;
}
