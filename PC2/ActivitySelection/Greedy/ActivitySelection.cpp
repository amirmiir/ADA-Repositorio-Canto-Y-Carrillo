#include <bits/stdc++.h>
using namespace std;

struct Activity {
    int start, finish;
};

bool activityCompare(Activity s1, Activity s2)
{
    return (s1.finish < s2.finish);
}

void printMaxActivities(Activity arr[], int n)
{

    sort(arr, arr + n, activityCompare);

    cout << "Las siguientes actividades fueron escogidas :\n";

    int i = 0;
    cout << "(" << arr[i].start << ", " << arr[i].finish
         << ")";

    for (int j = 1; j < n; j++) {
        if (arr[j].start >= arr[i].finish) {
            cout << ", (" << arr[j].start << ", "
                 << arr[j].finish << ")";
            i = j;
        }
    }
    
    cout << endl;
}

void generateRandomActivities(Activity arr[], int n)
{
    srand(time(0)); 

    for (int i = 0; i < n; i++) {
        int start = rand() % n/1+1; 
        int finish = start + (rand() % n/2+1) + 1; 
        arr[i] = { start, finish };
    }
}

int main()
{
    int n;
    cout << "Ingrese el número de actividades: ";
    cin >> n;

    Activity* arr = new Activity[n]; 

    generateRandomActivities(arr, n);

    cout << "Actividades generadas (inicio, fin):\n";
    for (int i = 0; i < n; i++) {
        cout << "(" << arr[i].start << ", " << arr[i].finish << ")\n";
    }
	
	clock_t start = clock();
	printMaxActivities(arr, n);
	clock_t end = clock();
	
	double elapsedTime = double(end - start)/CLOCKS_PER_SEC;
	
	cout << "El algoritmo demoró " << elapsedTime << "segundos en ejecutarse." << endl;
    return 0;
}

