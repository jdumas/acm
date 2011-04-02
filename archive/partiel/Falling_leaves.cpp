#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector <char> nodes;

struct tree {
	char data;
	struct tree * left;
	struct tree * right;
	tree(char arg_d):
		data(arg_d), left(NULL), right(NULL) {}
};

void insert(tree * & t, char data) {
	if (t == NULL) {t = new tree(data); return;}
	if (t->data > data) insert(t->left, data);
	else insert(t->right, data);
	return;
}

void affiche(tree * t) {
	if (t == NULL) return;
	cout << t->data;
	affiche(t->left);
	affiche(t->right);
	return;
}

void compute(void) {
	int i;
	tree * t = NULL;
	for (i = nodes.size()-1; i >= 0; --i)
		insert(t, nodes[i]);
	affiche(t);
	cout << endl;
	nodes.clear();
	return;
}

int main(void) {
	string s;
	unsigned i;
	while (1) {
		cin >> s;
		if (s == "$" || s == "*") compute();
		if (s == "$") break;
		if (s == "*") continue;
		for(i=0; i < s.size(); ++i)
			nodes.push_back(s[i]);
	}
}
