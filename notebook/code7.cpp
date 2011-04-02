/********************************************************************************
 * Couplage maximum.
 *
 * Recherche d'un couplage maximum dans le cas d'un graphe biparti.
 * Complexite : O(n*m)
 ********************************************************************************/

#include <vector>
using namespace std;

class bigraph {
public:
	vector<vector<int> > adj_left;
	vector<int> match_left, match_right;
	int nb_coupled_edges;
	bigraph(void) {
	}
	bigraph(int p, int q) {
		adj_left.resize(p);
		match_left.resize(p, -1);
		match_right.resize(q, -1);
		nb_coupled_edges = 0;
	}
	void reset(void) {
		int p = match_left.size();
		int q = match_right.size();
		// Clear
		match_left.clear();
		match_right.clear();
		// Resize
		match_left.resize(p, -1);
		match_right.resize(q, -1);
		nb_coupled_edges = 0;
	}

private:
	vector<bool> vu_left;

	// Parcours en profondeur pour trouver un chemin augmentant
	bool parcours(int x) {
		int i, y, z;
		if (x == -1)
			return true; // Sommet non sature : on s'arrete
		if (vu_left[x])
			return false; // Sommet deja explore
		vu_left[x] = true;
		for (i = 0; i < (int) adj_left[x].size(); ++i) {
			y = adj_left[x][i];
			z = match_right[y];
			if (parcours(z)) {
				match_right[y] = x;
				match_left[x] = y;
				return true;
			}
		}
		return false;
	}

	// Recherche d'un chemin augmentant
	bool find_path(void) {
		int i;
		vu_left.clear();
		vu_left.resize(adj_left.size(), false);
		for (i = 0; i < (int) adj_left.size(); ++i) {
			if (match_left[i] == -1 && parcours(i))
				return true;
		}
		return false;
	}

public:
	// Couplage glouton
	void greedy_matching(void) {
		int i, j, k;
		for (i = 0; i < (int) adj_left.size(); ++i) {
			for (k = 0; k < (int) adj_left[i].size(); ++k) {
				j = adj_left[i][k];
				if (match_left[i] == -1 && match_right[j] == -1) {
					match_left[i] = j;
					match_right[j] = i;
					++nb_coupled_edges;
				}
			}
		}
	}

	// Calcul d'un couplage maximum
	void couplage_max(void) {
		while (true) {
			if (find_path())
				++nb_coupled_edges;
			else
				break;
		}
		return;
	}

};
