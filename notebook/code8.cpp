/********************************************************************************
 * Parcours en largeur
 *
 * Implementation a l'aide de deux piles. Complexite : O(n + m)
 ********************************************************************************/

#include <vector>
#include <stack>
using namespace std;

typedef vector<vector<int> > graph;

// Renvoie la distance de la source a la cible en nombre de sauts
// L'algorithme s'arrete des que la cible est atteinte
int bfs(graph & g, int source, int target) {
	vector<bool> vu(g.size(), false);
	stack<int> current, next;
	int i, j, d = 0;
	current.push(source);
	vu[source] = true;
	while (not current.empty()) {
		i = current.top();
		current.pop();
		for (j = 0; j < (int) g[i].size(); ++j) {
			if (vu[g[i][j]]) continue;
			if (g[i][j] == target) return d;
			next.push(g[i][j]);
			vu[g[i][j]] = true;
		}
		if (current.empty()) {swap(current, next); ++d;}
	}
	return -1;
}

/********************************************************************************
 * Parcours en profondeur
 *
 * Implementation a l'aide d'une pile. Complexite : O(n + m)
 ********************************************************************************/

#include <vector>
#include <stack>
using namespace std;

typedef vector<vector<int> > graph;

// Renvoie true ssi la source et la cible sont dans la meme composante connexe
bool dfs(graph & g, int source, int target) {
	vector<bool> vu(g.size(), false);
	stack<int> current;
	int i, j;
	current.push(source);
	vu[source] = true;
	while (not current.empty()) {
		i = current.top();
		current.pop();
		for (j = 0; j < (int) g[i].size(); ++j) {
			if (vu[g[i][j]]) continue;
			if (g[i][j] == target) return true;
			current.push(g[i][j]);
			vu[g[i][j]] = true;
		}
	}
	return false;
}
