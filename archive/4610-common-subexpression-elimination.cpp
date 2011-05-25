/*
 * 4610-common-subexpression-elimination.cpp
 *
 * Regionals 2009 :: Europe - Northwestern
 *
 * http://livearchive.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=362&page=show_problem&problem=2611
 */

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define forn(i, n) for (int i = 0; i < (n); ++i)
#define foreach(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

typedef pair<int, pair<int, int> > key;

struct Node {
	Node() :
		ptr(-1), label(0), left(-1), right(-1) {
	}
	Node(int label, int left = -1, int right = -1) :
		ptr(-1), label(label), left(left), right(right) {
	}
	int ptr;
	int label;
	int left, right;

	inline key get(vector<Node> & tree) const {
		int a = tree[left].ptr == -1 ? left : tree[left].ptr;
		int b = tree[right].ptr == -1 ? right : tree[right].ptr;
		return make_pair(label, make_pair(a, b));
	}
};

vector<int> index;
vector<Node> tree;
map<int, int> leaves;
map<key, int> links;

int toBase10(string & s, int & i) {
	int acc = 0, o = 1;
	for (; i < (int) s.size() && s[i] >= 'a' && s[i] <= 'z'; ++i) {
		acc = acc + o * (s[i] - 'a' + 1);
		o *= 27;
	}
	return acc;
}

string toBase26(int i) {
	string s;
	for (; i; i /= 27)
		s.push_back(i % 27 + 'a' - 1);
	return s;
}

void parse(string & s, int & i) {
	int x;
	x = tree.size();
	tree.push_back(Node(toBase10(s, i)));

	if (s[i] == '(') {
		// Inner node
		tree[x].left = tree.size();
		parse(s, ++i);
		tree[x].right = tree.size();
		parse(s, ++i);
		++i;

		key id = tree[x].get(tree);
		pair<map<key, int>::iterator, bool> rep;
		rep = links.insert(make_pair(id, x));
		if (not rep.second) {
			tree.resize(x + 1);
			tree[x].ptr = rep.first->second;
		}
	} else {
		// Leaf
		pair<map<int, int>::iterator, bool> rep;
		rep = leaves.insert(make_pair(tree[x].label, x));
		if (not rep.second)
			tree[x].ptr = rep.first->second;
	}
}

void display(int x, int & num) {
	if (tree[x].ptr != -1)
		cout << index[tree[x].ptr];
	else {
		cout << toBase26(tree[x].label);
		index[x] = ++num;
		if (tree[x].left != -1) {
			cout << "(";
			display(tree[x].left, num);
			cout << ",";
			display(tree[x].right, num);
			cout << ")";
		}
	}
}

int main(void) {
	int c;
	for (cin >> c; c; --c) {
		int i = 0, num = 0;

		string s;
		cin >> s;
		parse(s, i);
		index.resize(tree.size(), 0);
		display(0, num);
		cout << endl;

		index.clear();
		tree.clear();
		leaves.clear();
		links.clear();
	}
	return 0;
}
