#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

struct edge {
	int target;    // Le voisin associé
	int a; int b;  // Le ratio d'échange
	edge(int arg_t, int arg_a, int arg_b) :
		target(arg_t), a(arg_a), b(arg_b) {
	}
};
// Simplifications syntaxiques
typedef vector<edge> voisins;
typedef map<string, int> id_map;

id_map ident;                // Associe à un objet un numéro unique
vector<bool> vu(60, false);  // Marque un sommet déjà visité
vector<voisins> graph(60);   // Associe à un sommet ses voisins (= une liste)

int dest_vertex;  // Le sommet cible dans le parcours
int rep_m, rep_n; // Permet de récupérer la réponse
int counter = 0;

// Après un parcours remet les sommets visités à zéro
void clean(void) {
	vector<bool>::iterator it;
	for (int i = 0; i < counter; i++)
		vu[i] = false;
	return;
}

// Remplace un couple (x,y) par (px,py) premiers entre eux
void normalize(int &x,int &y) {
	int m = x, n = y;
	while (n) {
		m %= n;
		swap(m,n);
	}
	x /= m;
	y /= m;
	return;
}

// Exploration en profondeur, à partir de cur_vertex,
// avec un ratio d'échange avec la source égal à cur_m/cur_n
bool explore(int cur_vertex, int cur_m, int cur_n) {
	if (cur_vertex == dest_vertex) {
		rep_m = cur_m;
		rep_n = cur_n;
		return true;
	}
	vu[cur_vertex] = true;
	voisins::iterator it;
	for(it = graph[cur_vertex].begin(); it != graph[cur_vertex].end(); it++) {
		if (vu[it->target])
			continue;
		int new_m = cur_m * it->a;
		int new_n = cur_n * it->b;
		normalize(new_m, new_n);
		if (explore(it->target, new_m, new_n))
			return true;
	}
	return false;
}

// Prendre en compte une nouvelle affirmation (!)
void make_assert(void) {
	int m, n;
	char c;
	string item_a, item_b;
	pair<id_map::iterator, bool> it_a, it_b;
	cin >> m >> item_a >> c >> n >> item_b;
	// Associer un numéro unique à un objet si nécessaire
	it_a = ident.insert(make_pair(item_a, counter));
	if (it_a.second)
		counter++;
	it_b = ident.insert(make_pair(item_b, counter));
	if (it_b.second)
		counter++;
	int ida = it_a.first->second, idb = it_b.first->second;
	// Ajouter le ratio au graphe
	normalize(m, n);
	graph[ida].push_back(edge(idb, m, n));
	graph[idb].push_back(edge(ida, n, m));
	return;
}

// Output le ratio correspondant à la question posée (?)
void make_query(void) {
	char c;
	string item_a, item_b;
	int ida,idb;
	cin >> item_a >> c >> item_b;
	ida = ident.find(item_a)->second;
	idb = ident.find(item_b)->second;
	// Prépare l'exploration
	clean();
	dest_vertex = idb;
	rep_m = 1;
	rep_n = 1;
	// Affichage du résultat
	if (explore(ida, 1, 1))
		cout << rep_m << " " << item_a << " = " << rep_n << " " << item_b << endl;
	else
		cout << "? " << item_a << " = " << "? " << item_b << endl;
	return;
}

int main(void) {
	char c;
	while (1) {
		cin >> c;
		switch (c) {
		case '.':
			return 0;
		case '?':
			make_query();
			break;
		case '!':
			make_assert();
			break;
		}
	}
}
