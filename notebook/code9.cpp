/********************************************************************************
 * Composantes fortement connexes
 *
 * Calcul des composantes fortement connexes d'un graphe oriente.
 * Algorithme de Tarjan. Complexite : O(n + m)
 ********************************************************************************/
class graph {
public:
	vector<vector<int> > adj;
	vector<int> comp; // Indice de la CFC d'un sommet
	int nb_cfc;

private:
	vector<int> index; // Ordre dans lequel les sommets ont ete visites
	vector<int> lowlink; // Sert a determiner la "racine" d'une CFC
	stack<int> s; // Les sommets non classes
	int id;

	// Parcours en profondeur sur un sommet
	void tarjan(int i) {
		int j, k;
		index[i] = id;
		lowlink[i] = id;
		++id;
		s.push(i);
		for (k = 0; k < (int) adj[i].size(); ++k) {
			j = adj[i][k];
			if (index[j] == -1)
				tarjan(j);
			if (comp[j] == -1)
				lowlink[i] = min(lowlink[i], lowlink[j]);
		}
		if (lowlink[i] == index[i]) {
			do {
				j = s.top();
				s.pop();
				comp[j] = nb_cfc;
			} while (i != j);
			++nb_cfc;
		}
	}

public:
	// Calcul des CFC du graphe
	void cfc() {
		id = 0;
		nb_cfc = 0;
		comp.clear();
		index.clear();
		lowlink.clear();
		comp.resize(adj.size(), -1);
		index.resize(adj.size(), -1);
		lowlink.resize(adj.size(), -1);
		for (int i = 0; i < (int) adj.size(); ++i) {
			if (index[i] == -1)
				tarjan(i);
		}
	}
};
