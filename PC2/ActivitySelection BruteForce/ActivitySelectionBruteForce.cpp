#include <bits/stdc++.h>
using namespace std;

/* Estructura de la actividad */
struct Activity {
    int start, end;
};

/* Funcion para verificar si el subconjunto de actividades es valido */
bool isValidSet(const vector<Activity>& activities, const vector<int>& subset) {
    for (size_t i = 0; i < subset.size(); ++i) {
        for (size_t j = i + 1; j < subset.size(); ++j) {

            if (activities[subset[i]].end > activities[subset[j]].start || activities[subset[j]].end > activities[subset[i]].start) {
                return false;
            }
        }
    }
    return true;
}

/* Algoritmo de fuerza bruta para seleccionar el subconjunto maximo de actividades */
void bruteForceActivitySelection(const vector<Activity>& activities) {
    int n = activities.size();
    int maxActivities = 0;
    vector<int> bestSet;

    /* Generar todas las combinaciones posibles de actividades */
    for (int i = 0; i < (1 << n); ++i) { /* 2^n posibles subconjuntos */
        vector<int> subset;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) { /* Incluir la actividad j en el subconjunto */
                subset.push_back(j);
            }
        }

        /* Verificar si este subconjunto es valido (no tiene superposicion) */
        if (isValidSet(activities, subset) && subset.size() > maxActivities) {
            maxActivities = subset.size();
            bestSet = subset;
        }
    }

    /* Imprimir el mejor conjunto de actividades */
    cout << "Las actividades seleccionadas en el mejor subconjunto son: \n";
    for (int i : bestSet) {
        cout << "{" << activities[i].start << ", " << activities[i].end << "} ";
    }
    cout << "\nNúmero máximo de actividades: " << maxActivities << endl;
}

/* Generar actividades aleatorias */
void generateRandomActivities(vector<Activity>& arr, int n) {
    srand(time(0)); 
    for (int i = 0; i < n; i++) {
        int start = rand() % (n + 1);  /* Valor entre 0 y n */
        int finish = start + (rand() % (n / 2 + 1));  /* Valor entre start y n */
        arr.push_back({start, finish});
    }
}

int main() {
    int n;
    cout << "Ingrese el número de actividades: ";
    cin >> n;

    vector<Activity> activities; 

    generateRandomActivities(activities, n);

    cout << "Actividades generadas (inicio, fin):\n";
    for (int i = 0; i < n; i++) {
        cout << "(" << activities[i].start << ", " << activities[i].end << ")\n";
    }

    clock_t start = clock();
    bruteForceActivitySelection(activities);
    clock_t end = clock();

    double elapsedTime = double(end - start) / CLOCKS_PER_SEC;

    cout << "El algoritmo demoró " << elapsedTime << " segundos en ejecutarse." << endl;

    return 0;
}
