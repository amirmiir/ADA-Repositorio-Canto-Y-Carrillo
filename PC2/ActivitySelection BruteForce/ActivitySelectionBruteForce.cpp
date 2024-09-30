#include <bits/stdc++.h>
using namespace std;

/*  Estructura de la actividad */
struct activity{

    int start, end;
};

/*
    Función que seleciona un conjunto maximo de actividades que pueden ser ejecutadas,
    dado que solo una actividad puede ejecutarse a la vez en todo momento.
*/ 
void solve(int n, vector<activity> actvty){

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int x, y;
    for (auto x: actvty){
        /*  Dado que ordenamos por tiempo de finalización that que insertaremos
            actividades en una cola-de-prioridad con un tiempo de fin e inicio.
        */
        pq.push({x.end, x.start});
    }

    cout << "Las actividades se eligen en el siguiente orden: ";
    /*  Siempre seleccionaremos la actividad con el menor tiempo de finalización */
    x = 0;

    auto current = pq.top();
    auto start = current.second;
    auto end = current.first;

    pq.pop();

    cout << "{" << start << "," << end << "} ";

    /*  Para seleccionar del resto de las actividades */
    while (!pq.empty()){
    
        current = pq.top();
        pq.pop();

        /* 
            Una actividad será seleccionada si esta tiene un tiempo
            de inicio mayor que la de el tiempo de fin de la actividad
            anterior.
        */ 
        if (current.second >= end){
        
            start = current.second;
            end = current.first;

            cout << "{" << start << "," << end << "} ";
        }
    }
}


int main(){

    int n = 6;
    vector<activity> actvty = {{1, 2}, {4, 4}, {5, 10}, {9, 10}, {7, 8}, {2, 4}};
    solve(n, actvty);
}