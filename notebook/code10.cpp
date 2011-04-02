/********************************************************************************
 * Effeuillage de graphe
 *
 * Effeuillage de graphe oriente, on enleve les sommets de degre entrant egal a 1
 * Complexite : O(n+m)
 ********************************************************************************/

#include <vector>
#include <list>
using namespace std;

void effeuille(vector<vector<int> > & adj, vector<int> & order) {
	int i, j, k, index = 0;
	vector<bool> vu(adj.size(), false);
	vector<int>  deg(adj.size(), 0);
	list<int> visit;
	// On calcule le degre entrant de chaque sommet
	for (i = 0; i < (int) adj.size(); ++i)
		for (k = 0; k < (int) adj[i].size(); ++k)
			++deg[adj[i][k]];
	// On commence par les sommets de degre entrant nul
	for (i = 0; i < (int) adj.size(); ++i)
		if (deg[i] == 1) {
			vu[i] = true;
			visit.push_back(i);
		}
	// On effeuille
	while (not visit.empty()) {
		i = visit.front();
		visit.pop_front();
		// Appliquer une operation sur "i"
		order[i] = index;
		++index;
		for (k = 0; k < (int) adj[i].size(); ++k) {
			j = adj[i][k];
			if (vu[j]) continue; // Sommet deja visite
			// On retire "i", donc on decremente le degre entrant de "j"
			--deg[j];
			// Si "j" devient une feuille
			if (deg[j] == 1) {
				vu[j] = true;
				visit.push_back(j);
			}
		}
	}
	return;
}
