#include <iostream>
#include <list>
using namespace std;

/* Grafo no-dirigido */
class Graph
{
	int V; /* Número de vértices*/
	list<int> *adj; /* Array dinámico con listas de adyacencia */ 
public:
	/* Constructor / Destructor */
	Graph(int V) { this->V = V; adj = new list<int>[V]; }
	~Graph()	 { delete [] adj; }

    /* Función añadir arista */
	void addEdge(int v, int w);

	/* Imprimir resultados del coloreo de grafos Greedy */
	void greedyColoring();
};


void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v); 
}

/*  Asigna colores (empezando de 0) a todos los vertices e
    imprime la asignación de colores.
*/
void Graph::greedyColoring()
{
	int result[V];

	/* Asigna el primer color al primer vértice*/
	result[0] = 0;

	/* Inicializa los V-1 vertices restantes como sin-asignar*/ 
	for (int u = 1; u < V; u++)
		result[u] = -1; /* Sin color asignado a "u" */

    /*  Array temporal para guardar los colores disponibles.
        El verdadero valor de available[cr] significaría que el
        color cr está asignado a uno de sus vertices adyacentes
    */
	bool available[V];
	for (int cr = 0; cr < V; cr++)
		available[cr] = false;

    /* Asigna colores a los V-1 vertices restantes */
	// Assign colors to remaining V-1 vertices
	for (int u = 1; u < V; u++)
	{
		/*  Procesa todos los vertices adyacentes y marca sus
            colores como no disponibles
         */
		list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (result[*i] != -1)
				available[result[*i]] = true;

        /* Encuentra el primer color disponible */
		int cr;
		for (cr = 0; cr < V; cr++)
			if (available[cr] == false)
				break;

		result[u] = cr; /*Asigna el color encontrado*/

        /*  Reinicia los valores de vuelta a falso para la siguiente iteración*/
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (result[*i] != -1)
				available[result[*i]] = false;
	}

    /* Imprime el resultado */
	for (int u = 0; u < V; u++)
		cout << "Vertex " << u << " ---> Color "
			<< result[u] << endl;
}


int main()
{
	Graph g1(5);
	g1.addEdge(0, 1);
	g1.addEdge(0, 2);
	g1.addEdge(1, 2);
	g1.addEdge(1, 3);
	g1.addEdge(2, 3);
	g1.addEdge(3, 4);
	cout << "Coloreo del grafo 1 \n";
	g1.greedyColoring();

	Graph g2(5);
	g2.addEdge(0, 1);
	g2.addEdge(0, 2);
	g2.addEdge(1, 2);
	g2.addEdge(1, 4);
	g2.addEdge(2, 4);
	g2.addEdge(4, 3);
	cout << "\nColoreo del grafo 2 \n";
	g2.greedyColoring();

	return 0;
}
