/********************************************************************************
 * Algorithme d'Edmonds-Karp
 *
 * Recherche d'un flot maximum. Complexite : O(n*m^2)
 ********************************************************************************/

#include <vector>
#include <queue>
using namespace std;

class graph {
public:
	vector<vector<int> > adj;  // Liste d'adjacence
	vector<vector<int> > capa; // Matrice des capacites de liens
	vector<vector<int> > flot; // Matrice des valeurs du flot
	graph(void) {}
	graph(int n) {
		adj.resize(n);
		capa.resize(n, vector<int> (n, 0));
		flot.resize(n, vector<int> (n, 0));
	}
	void reset(void) {
		flot.clear();
		flot.resize(adj.size(), vector<int> (adj.size(), 0));
	}
private:
	vector<int> pere;

	int cout(int x, int y) {
		return capa[x][y] - flot[x][y];
	}

	// Parcours en largeur conditionnel
	void parcours(int source, int target) {
		int x, y, i;
		queue<int> file;
		pere.clear();
		pere.resize(adj.size(), -1);
		file.push(source);
		pere[source] = source;
		while (!file.empty()) {
			x = file.front();
			file.pop();
			for (i = 0; i < (int) adj[x].size(); ++i) {
				y = adj[x][i];
				if (pere[y] != -1)
					continue;
				if (cout(x, y) <= 0)
					continue;
				pere[y] = x;
				file.push(y);
				if (y == target)
					return;
			}
		}
		return;
	}

	// Calcul du cout residuel le long d'un chemin
	int cout_residuel(int target) {
		int x, y, c;
		y = target;
		x = pere[target];
		c = cout(x, y);
		while (pere[x] != x) {
			y = x;
			x = pere[x];
			c = min(c, cout(x, y));
		}
		return c;
	}

	// Augmenter le flot le long du chemin
	void augmenter(int target, int c) {
		int x, y;
		y = target;
		x = pere[target];
		while (x != y) {
			flot[x][y] += c;
			flot[y][x] -= c;
			y = x;
			x = pere[x];
		}
		return;
	}
public:
	// Calcul d'un flot maximum
	int flot_max(int source, int target) {
		int c, s = 0;
		while (true) {
			parcours(source, target);
			if (pere[target] == -1)
				break;
			c = cout_residuel(target);
			s += c;
			augmenter(target, c);
		}
		return s;
	}

};
