#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdlib> 
using namespace std;

class Task
{
private:
    int time;
    int weight;
public:
    Task();
    Task(int, int);
    ~Task();
    void Execute();	
    int GetTime();
    int GetWeight();
};

Task::Task() : time(1), weight(1) {}

Task::Task(int time, int weight) : time(time), weight(weight) {}

Task::~Task() {}

void Task::Execute()
{
    cout << "Tarea con peso " << weight << " ejecutada ||\t|| " << time << " segundos." << endl;
}

int Task::GetTime()
{
    return this->time;
}

int Task::GetWeight()
{
    return this->weight;
}

void scheduleTasks(Task* tasks, int numTasks, int maxTime);
void PrintTasks(Task* tasks, int numTasks);

int main()
{
    int numTasks; 
    int maxTime;
    
    cout << "Ingrese el número de tareas: " << endl;
    cin >> numTasks;
    cout << "Ingrese el tiempo máximo para realizarlas: " << endl;
    cin >> maxTime;
    
    Task* tasks = new Task[numTasks];
	
    srand(static_cast<unsigned>(time(0)));
	
    for (int i = 0; i < numTasks; i++)
    {
        int time = rand() % 11 + 1 ;   
        int weight = rand() % 21 + 1 ;  
        tasks[i] = Task(time, weight);
    }
	
	PrintTasks(tasks, numTasks);
	
	clock_t start = clock();
    scheduleTasks(tasks, numTasks, maxTime);
	clock_t end = clock();
	
	double elapsedTime = double(end - start) / CLOCKS_PER_SEC;

    cout << "Tiempo de ejecución del algoritmo DP: " << elapsedTime << " segundos." << endl;

    delete[] tasks;
    return 0;
}

void scheduleTasks(Task* tasks, int numTasks, int maxTime)
{
    int* dp = new int[maxTime + 1]();
    int* selected = new int[maxTime + 1]();
    
    for(int i = 0; i < numTasks; i++)
    {
    	selected[i] = -1;
    }

    for (int i = 0; i < numTasks; i++)
    {
        for (int j = maxTime; j >= tasks[i].GetTime(); j--)
        {
            if (dp[j] < dp[j - tasks[i].GetTime()] + tasks[i].GetWeight())
            {
                dp[j] = dp[j - tasks[i].GetTime()] + tasks[i].GetWeight();
                selected[j] = i; 
            }
        }
    }

    cout << "Máximo peso de tareas programadas: " << dp[maxTime] << endl;
    cout << "Tareas seleccionadas:" << endl;

    int timeRemaining = maxTime;
    while (timeRemaining > 0 && selected[timeRemaining] != -1)
    {
        int taskIndex = selected[timeRemaining];
        tasks[taskIndex].Execute();
        timeRemaining -= tasks[taskIndex].GetTime();
    }

    delete[] dp;
    delete[] selected;
}

void PrintTasks(Task* tasks, int numTasks) {
    cout << "Lista de tareas generadas:" << endl;
    for (int i = 0; i < numTasks; i++) {
        cout << "Tarea " << i + 1 << ": Tiempo = " << tasks[i].GetTime() 
             << " segundos, Peso = " << tasks[i].GetWeight() << endl;
    }
}



