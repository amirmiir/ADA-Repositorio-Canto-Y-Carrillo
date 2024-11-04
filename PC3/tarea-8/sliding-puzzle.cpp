#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

#define N 3 // Dimensión del puzzle 3x3

// Estructura para almacenar el estado del puzzle
struct Nodo {
    vector<vector<int>> puzzle; // Configuración del puzzle
    int x, y;                   // Posición del espacio vacío
    int costo;                  // Costo heurístico
    int nivel;                  // Nivel del nodo en el árbol de búsqueda
    string historia;            // Historial de movimientos realizados
};

// Comparador para ordenar nodos en la cola de prioridad
struct Comparador {
    bool operator()(const Nodo &a, const Nodo &b) {
        return (a.costo + a.nivel) > (b.costo + b.nivel);
    }
};

// Coordenadas para los movimientos: arriba, abajo, izquierda, derecha
int movX[] = {1, 0, -1, 0};
int movY[] = {0, -1, 0, 1};
string direcciones[] = {"Abajo", "Izquierda", "Arriba", "Derecha"};

// Función para calcular el costo heurístico (distancia de Manhattan)
int calcularHeuristica(const vector<vector<int>> &puzzle, const vector<vector<int>> &objetivo);

// Función para verificar si las coordenadas están dentro del límite
bool esValido(int x, int y);

// Función que imprime el estado actual del puzzle
void imprimirPuzzle(const vector<vector<int>> &puzzle);
// Función principal que resuelve el puzzle usando Branch and Bound
void resolverPuzzle(const vector<vector<int>> &inicial, const vector<vector<int>> &objetivo,
                    int x, int y);

// Función para ingresar un puzzle personalizado
vector<vector<int>> ingresarPuzzle();

// Función para obtener la posición del espacio vacío en el puzzle
pair<int, int> obtenerPosicionEspacio(const vector<vector<int>> &puzzle);

void menu();

int main() {
    menu();
    return 0;
}

/*

    Funciones

*/
void menu() {
    int opcion;
    vector<vector<int>> objetivo = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    cout << "Seleccione una opción:\n";
    cout << "1. Puzzle predeterminado\n";
    cout << "2. Ingresar puzzle manualmente\n";
    cout << "Opción: ";
    cin >> opcion;

    vector<vector<int>> inicial;
    pair<int, int> posicionEspacio;

    if (opcion == 1) {
        inicial = {{1, 2, 3}, {5, 6, 0}, {7, 8, 4}};
        posicionEspacio = obtenerPosicionEspacio(inicial);
    } else if (opcion == 2) {
        inicial = ingresarPuzzle();
        posicionEspacio = obtenerPosicionEspacio(inicial);
    } else {
        cout << "Opción inválida." << endl;
        return;
    }

    cout << "Puzzle inicial:\n";
    imprimirPuzzle(inicial);
    resolverPuzzle(inicial, objetivo, posicionEspacio.first, posicionEspacio.second);
}

int calcularHeuristica(const vector<vector<int>> &puzzle,
                       const vector<vector<int>> &objetivo) {
    int costo = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] && puzzle[i][j] != objetivo[i][j]) {
                costo++;
            }
        }
    }
    return costo;
}

bool esValido(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void imprimirPuzzle(const vector<vector<int>> &puzzle) {
    for (const auto &fila : puzzle) {
        for (int num : fila) {
            if (num == 0) cout << "  ";
            else cout << num << " ";
        }
        cout << endl;
    }
}

void resolverPuzzle(const vector<vector<int>> &inicial, const vector<vector<int>> &objetivo,
                    int x, int y) {
    priority_queue<Nodo, vector<Nodo>, Comparador> cola;
    set<vector<vector<int>>> visitados;

    Nodo nodoInicial = {inicial, x, y, calcularHeuristica(inicial, objetivo), 0, ""};
    cola.push(nodoInicial);
    visitados.insert(inicial);

    while (!cola.empty()) {
        Nodo actual = cola.top();
        cola.pop();

        // Si el nodo actual es la solución
        if (actual.costo == 0) {
            cout << "Puzzle resuelto en " << actual.nivel << " movimientos." << endl;
            cout << "Secuencia de movimientos: " << actual.historia << endl;
            return;
        }

        // Ramificar el nodo actual en las cuatro direcciones
        for (int i = 0; i < 4; i++) {
            int nuevoX = actual.x + movX[i];
            int nuevoY = actual.y + movY[i];

            // Verificar si la posición es válida
            if (esValido(nuevoX, nuevoY)) {
                vector<vector<int>> nuevoPuzzle = actual.puzzle;
                swap(nuevoPuzzle[actual.x][actual.y], nuevoPuzzle[nuevoX][nuevoY]);

                // Si el nuevo estado no ha sido visitado
                if (visitados.find(nuevoPuzzle) == visitados.end()) {
                    visitados.insert(nuevoPuzzle);

                    Nodo nuevoNodo = {
                        nuevoPuzzle,      nuevoX,
                        nuevoY,           calcularHeuristica(nuevoPuzzle, objetivo),
                        actual.nivel + 1, actual.historia + " " + direcciones[i]};
                    cola.push(nuevoNodo);
                }
            }
        }
    }
    cout << "No se encontró solución para el puzzle." << endl;
}

vector<vector<int>> ingresarPuzzle() {
    vector<vector<int>> puzzle(N, vector<int>(N));
    cout << "Ingrese el puzzle 3x3 (usa 0 para el espacio vacío):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> puzzle[i][j];
        }
    }
    return puzzle;
}

pair<int, int> obtenerPosicionEspacio(const vector<vector<int>> &puzzle) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] == 0) {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // No debería suceder si el puzzle es válido
}