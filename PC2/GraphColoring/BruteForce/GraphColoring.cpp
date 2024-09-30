#include <bits/stdc++.h>
using namespace std;

void printSolution(int color[], int V);
#define MAX_V 20

bool isSafe(int v, bool graph[MAX_V][MAX_V], int color[], int c, int V)
{
    for (int i = 0; i < V; i++)
    	//Verifica si los vértices con los que está conectado
		//(graph[v][i]!=0) tienen el mismo color.
        if (graph[v][i] && c == color[i])
            return false;

    return true;
}

bool allColorsUsed(int color[], int nColors, int V) {
    bool usedColors[MAX_V] = {false};
    for (int i = 0; i < V; i++) {
        usedColors[color[i]] = true;
    }
    for (int i = 1; i <= nColors; i++) {
        if (!usedColors[i]) {
            return false;
        }
    }
    return true;
}

bool graphColoringUtil(bool graph[MAX_V][MAX_V], int m, int color[], int v, int V)
{

    //Caso base: todos los vértices están coloreados
    if (v == V)
        return true;
	//recursividad con backtracking
    for (int c = 1; c <= m; c++) {


        if (isSafe(v, graph, color, c, V)) {
            color[v] = c;

            if (graphColoringUtil(graph, m, color, v + 1, V)
                == true)
                if(allColorsUsed(color, m, V))  return true;

            color[v] = 0;
        }
    }

    return false;
}

bool graphColoring(bool graph[MAX_V][MAX_V], int m, int V)
{

    //Se inicializa en cero para indicar que ningún vértice
    //tiene asignado un color
    int color[MAX_V];
    for (int i = 0; i < V; i++)
        color[i] = 0;

    if (graphColoringUtil(graph, m, color, 0, V) == false) {
        cout << "No existe la solución." << endl;
        return false;
    }

    printSolution(color, V);
    return true;
}


void printSolution(int color[], int V)
{
    cout << "La solución existe." << endl;
    for (int i = 0; i < V; i++)
        cout << "V" << i << " color: " << color[i] << " " << endl;

    cout << "\n";
}

int main()
{
	int V;
    int nColors = 3;
    
	cout << "Ingresa el número de vértices: (máximo " << MAX_V << " vértices): ";
    cin >> V;
    if (V > MAX_V || V < 1) {
        cout << "Número de vértices inválido." << endl;
        return 1;
    }
    
    cout << "Ingresa el número de colores: ";
    cin >> nColors;

	bool graph[MAX_V][MAX_V] = {false};
	
	srand(time(NULL));
	
	for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            graph[i][j] = graph[j][i] = rand() % 2; 
        }
    }


	clock_t start = clock();
    graphColoring(graph, nColors, V);
    clock_t end = clock();
    
    double elapsedTime = double(end - start)/CLOCKS_PER_SEC;
    
    cout << "El algoritmo demoró " << elapsedTime << "segundos en ejecutarse.";
    
    return 0;
}

