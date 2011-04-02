#include <cstdio>
#include <iostream>
#include <map>
using namespace std;

map<string, pair<string, int> > most_probable;
map<string, int> freq;

char r[] = "22233344455566677778889999";

int main(void) {
	int i, k, n, proba;
	string temp, prefix;
	string::iterator it;
	map<string, int>::iterator it_freq;
	map<string, pair<string, int> >::iterator it_word;
	pair<map<string, int>::iterator, bool> res_freq;
	pair<map<string, pair<string, int> >::iterator, bool> res_word;
	cin >> n;
	for (k = 1; k <= n; k++) {
		most_probable.clear();
		freq.clear();
		cin >> i;
		while (i) {
			temp.clear();
			prefix.clear();
			cin >> temp >> proba;
			for (it = temp.begin(); it < temp.end(); it++) {
				prefix.push_back(*it);
				res_freq = freq.insert(make_pair(prefix, proba));
				if (!res_freq.second) {
					res_freq.first->second += proba;
				}
			}
			i--;
		}
		for (it_freq = freq.begin(); it_freq != freq.end(); it_freq++) {
			temp.clear();
			prefix = it_freq->first;
			for (it = prefix.begin(); it < prefix.end(); it++) {
				temp.push_back(r[*it - 'a']);
			}
			res_word = most_probable.insert(make_pair(temp, *it_freq));
			if (!res_word.second) {
				if (it_freq->second > res_word.first->second.second) {
					res_word.first->second = *it_freq;
				}
			}
		}
		cin >> i;
		cout << "Scenario #" << k << ':' << endl;
		while (i) {
			cin >> temp;
			prefix.clear();
			for (it = temp.begin(); it < temp.end(); it++) {
				if (*it == '1')
					break;
				prefix.push_back(*it);
				it_word = most_probable.find(prefix);
				if (it_word != most_probable.end()) {
					cout << it_word->second.first << endl;
				} else {
					cout << "MANUALLY" << endl;
				}
			}
			cout << endl;
			i--;
		}
		cout << endl;
	}
	return 0;
}
