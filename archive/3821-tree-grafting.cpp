/*
 * 3821 - Tree Grafting.cpp
 *
 * http://acmicpc-live-archive.uva.es/nuevoportal/data/problem.php?p=3821
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void transform(const string & name, int & h1, int & h2) {
	vector<int> height(2), last(2);
	int current = 2, level1 = 1, level2 = 1;
	height[0] = 0;
	height[1] = 1;
	last[0] = 0;
	last[1] = 1;
	h1 = 1;
	h2 = 1;

	string::const_iterator it;
	for (it = name.begin() + 1; it != name.end(); ++it) {
		if (*it == 'd') {
			++level1;
			if (*(it - 1) == 'u')
				level2 = height[last[level1]] + 1;
			else
				++level2;
			height.push_back(level2);
			h1 = max(h1, level1);
			h2 = max(h2, level2);
			last.resize(h1 + 1);
			last[level1] = current;
			++current;
		} else if (*it == 'u') {
			--level1;
			level2 = height[last[level1]];
		}
	}
}

int main(void) {
	string name;
	int h1, h2;
	for (int i = 1;; ++i) {
		cin >> name;
		if (name == "#")
			break;
		transform(name, h1, h2);
		printf("Tree %d: %d => %d\n", i, h1, h2);
	}
}
