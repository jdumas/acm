/********************************************************************************
 * Algorithme d'Edmonds-Karp
 *
 * Recherche d'un flot maximum. Complexite : O(n*m^2)
 ********************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class graph {
public:
	int t; // Number of teams
	int p; // Number of problems
	int current_flow; // Value of the current flow
	vector<vector<int> > adj; // Liste d'adjacence
	vector<vector<int> > capa; // Matrice des capacites de liens
	vector<vector<int> > flow; // Matrice des valeurs du flot
	graph(void) {}

	// Build the graph
	graph(int t, int p) :
		t(t), p(p),
		current_flow(0),
		adj(t + p + 2),
		capa(t + p + 2, vector<int> (t + p + 2, 0)),
		flow(t + p + 2, vector<int> (t + p + 2, 0))
	{
		// From source to teams
		for (int i = 1; i <= t; ++i) {
			adj[0].push_back(i);
			adj[i].push_back(0);
		}
		// From teams to problems
		for (int i = 1; i <= t; ++i) {
			for (int j = 1; j <= p; ++j) {
				adj[i].push_back(j + t);
				adj[j + t].push_back(i);
			}
		}
		// From problems to sink
		for (int j = 1; j <= p; ++j) {
			adj[t + p + 1].push_back(j + t);
			adj[j + t].push_back(t + p + 1);
		}
	}
private:
	vector<int> pere;

	int cost(int x, int y) {
		return capa[x][y] - flow[x][y];
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
				if (cost(x, y) <= 0)
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
		c = cost(x, y);
		while (pere[x] != x) {
			y = x;
			x = pere[x];
			c = min(c, cost(x, y));
		}
		return c;
	}

	// Augmenter le flot le long du chemin
	void augmenter(int target, int c) {
		int x, y;
		y = target;
		x = pere[target];
		while (x != y) {
			flow[x][y] += c;
			flow[y][x] -= c;
			y = x;
			x = pere[x];
		}
		return;
	}

	// Modifie le flot sur le chemin 0 → i → j+t → t+p+1 par la valeur c
	void relacher(int i, int j, int c) {
		flow[0][i] += c;
		flow[i][0] -= c;
		flow[i][j + t] += c;
		flow[j + t][i] -= c;
		flow[j + t][t + p + 1] += c;
		flow[t + p + 1][j + t] -= c;
	}

public:
	// Calcul d'un flot maximum
	void max_flow(void) {
		int c;
		while (true) {
			parcours(0, t + p + 1);
			if (pere[t + p + 1] == -1)
				break;
			c = cout_residuel(t + p + 1);
			current_flow += c;
			augmenter(t + p + 1, c);
		}
		return;
	}

	// On tente de réduire la capacité de l'arête (i,j+t)
	void toggle(int i, int j) {
		if (flow[i][j + t] == 0)
			capa[i][j + t] = 0;
		else {
			// Le flot max actuel utilise l'arête (i,j+t)
			int old_flow = current_flow;
			relacher(i, j, -1);
			current_flow -= 1;
			capa[i][j + t] = 0;
			max_flow();
			if (current_flow != old_flow) {
				// Alors il est nécessaire d'utiliser l'arête (i,j+t)
				capa[i][j + t] = 1;
				max_flow();
			}
		}
	}
};


int main(void) {
	int t, p, c;
	int st, sp;
	bool b = false;
	while (true) {
		cin >> t >> p;
		if (t == 0 && p == 0)
			break;
		else if (b)
			cout << endl;
		else
			b = true;
		graph g(t, p);
		st = 0;
		sp = 0;
		// Capa' from source to teams
		for (int i = 1; i <= t; ++i) {
			cin >> c;
			st += c;
			g.capa[0][i] = c;
		}
		// Capa' from teams to problems
		for (int i = 1; i <= t; ++i) {
			for (int j = 1; j <= p; ++j) {
				g.capa[i][j + t] = 1;
			}
		}
		// Capa' from problems to sink
		for (int j = 1; j <= p; ++j) {
			cin >> c;
			sp += c;
			g.capa[j + t][t + p + 1] = c;
		}
		// If total differs then it is impossible
		if (st != sp) {
			cout << "Impossible" << endl;
			continue;
		}
		// Else compute the max flow
		g.max_flow();
		if (g.current_flow != st) {
			cout << "Impossible" << endl;
			continue;
		}
		// Try to toggle the flow on the edge so that the solution became the first one in lexical order
		for (int i = 1; i <= t; ++i) {
			for (int j = 1; j <= p; ++j) {
				g.toggle(i, j);
			}
		}
		// Then output the solution
		for (int i = 1; i <= t; ++i) {
			for (int j = 1; j <= p; ++j) {
				cout << (g.flow[i][j + t] == 1 ? "Y" : "N");
			}
			cout << endl;
		}
	}
}
