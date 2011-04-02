#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct {
	int id;
	int length;
	double freq;
} song;

vector<song> my_tape;

bool song_comp(const song & s1, const song & s2) {
	double r1, r2;
	r1 = ((double) s1.length) * s2.freq;
	r2 = ((double) s2.length) * s1.freq;
	return (r1 < r2);
}

int main(void) {
	vector<song>::iterator it;
	int n;
	while (cin >> n) {
		my_tape.clear();
		for (; n; n--) {
			song new_song;
			cin >> new_song.id >> new_song.length >> new_song.freq;
			my_tape.push_back(new_song);
		}
		cin >> n;
		partial_sort(my_tape.begin(), my_tape.begin()+n, my_tape.end(), song_comp);
		cout << my_tape[n - 1].id << endl;
	}
	return 0;
}
