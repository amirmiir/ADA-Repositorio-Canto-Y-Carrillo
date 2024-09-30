#include <bits/stdc++.h>
using namespace std;

/*  Estructura de la actividad */
struct Activity {
    int start, end;
};

bool activityCompare(Activity s1, Activity s2)
{
    return (s1.end < s2.end);
}

/*
    Función que selecciona un conjunto máximo de actividades que pueden ser ejecutadas,
    dado que solo una actividad puede ejecutarse a la vez en todo momento.
*/ 
void activitySelectionBacktracking(int n, vector<Activity>& actvty) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (auto x : actvty) {
        // Insertar actividades en la cola de prioridad con fin y comienzo
        pq.push({x.end, x.start});
    }

    cout << "Las actividades se eligen en el siguiente orden: ";

    // Seleccionamos la primera actividad
    auto current = pq.top();
    auto start = current.second;
    auto end = current.first;
    pq.pop();

    cout << "{" << start << "," << end << "} ";

    // Seleccionamos del resto de las actividades
    while (!pq.empty()) {
        current = pq.top();
        pq.pop();

        /*Seleccionamos actividad si su inicio es mayor al final de la anterior*/
        if (current.second >= end) {
            start = current.second;
            end = current.first;
            cout << "{" << start << "," << end << "} ";
        }
    }
    cout << endl;
}

void generateRandomActivities(vector<Activity>& arr, int n) {
    srand(time(0)); 
    for (int i = 0; i < n; i++) {
        int start = rand() % (n + 1);  /*Valor entre 0 y n*/ 
        int finish = start + (rand() % (n / 2 + 1));  /*Valor entre start y n*/
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
    activitySelectionBacktracking(n, activities);
    clock_t end = clock();
    
    double elapsedTime = double(end - start)/CLOCKS_PER_SEC;
    
    cout << "El algoritmo demoró " << elapsedTime << " segundos en ejecutarse." << endl;

    return 0;
}
