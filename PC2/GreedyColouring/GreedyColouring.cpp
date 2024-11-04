#include <bits/stdc++.h>
using namespace std;

#define MAX_V 20

/* Grafo no-dirigido */
class Graph {
    int V;          /* Número de vértices*/
    list<int> *adj; /* Array dinámico con listas de adyacencia */
   public:
    /* Constructor / Destructor */
    Graph(int V);
    ~Graph() {
        delete[] adj;
    }

    /* Función añadir arista */
    void addEdge(int v, int w);

    /* Imprimir resultados del coloreo de grafos Greedy */
    void greedyColoring();
};

/* Constructor que genera un grafo aleatorio */
Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];

    srand(time(0));
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (rand() % 2 == 1) /*Con una probabilidad del 50%, añade una arista*/
            {
                addEdge(i, j);
            }
        }
    }
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

/*  Asigna colores (empezando de 0) a todos los vertices e
    imprime la asignación de colores.
*/
void Graph::greedyColoring() {
    int result[V];

    /* Asigna el primer color al primer vértice*/
    result[0] = 0;

    /* Inicializa los V-1 vertices restantes como sin-asignar*/
    for (int u = 1; u < V; u++) result[u] = -1; /* Sin color asignado a "u" */

    /*  Array temporal para guardar los colores disponibles.
        El verdadero valor de available[cr] significaría que el
        color cr está asignado a uno de sus vertices adyacentes
    */
    bool available[V];
    for (int cr = 0; cr < V; cr++) available[cr] = false;

    /* Asigna colores a los V-1 vertices restantes */
    for (int u = 1; u < V; u++) {
        /*  Procesa todos los vertices adyacentes y marca sus
            colores como no disponibles
         */
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1) available[result[*i]] = true;

        /* Encuentra el primer color disponible */
        int cr;
        for (cr = 0; cr < V; cr++)
            if (available[cr] == false) break;

        result[u] = cr; /*Asigna el color encontrado*/

        /*  Reinicia los valores de vuelta a falso para la siguiente iteración*/
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1) available[result[*i]] = false;
    }

    /* Imprime el resultado */
    for (int u = 0; u < V; u++) cout << "Vértice " << u << " ---> Color " << result[u] << endl;
}

int main() {
    int V;
    cout << "Ingresa el número de vértices (máximo " << MAX_V << "): ";
    cin >> V;

    if (V > MAX_V || V < 1) {
        cout << "Número de vértices inválido." << endl;
        return 1;
    }

    Graph g(V);

    clock_t start = clock();

    cout << "Coloreo del grafo generado aleatoriamente \n";
    g.greedyColoring();

    clock_t end = clock();

    double elapsedTime = double(end - start) / CLOCKS_PER_SEC;

    cout << "El algoritmo demoró " << elapsedTime << " segundos en ejecutarse." << endl;

    return 0;
}
