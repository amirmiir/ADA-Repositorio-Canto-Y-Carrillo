#include <iostream>
#include <ctime>
#include <climits>
using namespace std;

//Classes
class Task
{
	private:
		int time;
	public:
		Task();
		Task(int);
		~Task();
		void Execute();	
		int GetTime();
};

Task::Task()
{
	this->time = 1;
}

Task::Task(int time)
{
	this->time = time;
}

Task::~Task()
{
}

void Task::Execute()
{
	cout<<"Tarea ejecutada||\t||"<<time<<" segundos."<<endl;
}

int Task::GetTime()
{
	return this->time;
}


//Signatures
void Schedule(Task* tasks, bool* used, Task* currentSchedule, int taskCount, int currentSize, int& bestTime, Task* bestSchedule);
int EvaluateSchedule(Task* currentSchedule, int taskCount);
void PrintArray(Task* t, int size);

//Main
int main()
{
	srand(time(NULL));
    int taskCount;
    int bestTime = INT_MAX;    
	cout << "Ingrese el número de tareas(los tiempos se elegirán aleatoriamente): ";
	cin >> taskCount;

	Task* tasks = new Task[taskCount];
	bool* used = new bool[taskCount];
    Task* currentSchedule = new Task[taskCount];
	Task* bestSchedule = new Task[taskCount];
	
	for(int i = 0; i < taskCount; i++)
	{
		tasks[i] = Task(rand()%11);
		used[i] = false;
	}
	
	PrintArray(tasks, taskCount);
	
	clock_t start = clock();
	Schedule(tasks, used, currentSchedule, taskCount, 0, bestTime, bestSchedule);
	clock_t end = clock();
	
	double elapsedTime = double(end - start) / CLOCKS_PER_SEC;
	
	cout << "El mejor tiempo total: " << bestTime << " segundos." << endl;
	cout << "El tiempo que demoró el algoritmo es: " << elapsedTime << " segundos." << endl;
	cout << "El mejor orden es: ";
	
	PrintArray(bestSchedule, taskCount);
	
	delete[] tasks;
    delete[] used;
    delete[] currentSchedule;
    
	return 0;
}

//Functions
void Schedule(Task* tasks, bool* used, Task* currentSchedule, int taskCount, int currentSize, int& bestTime, Task* bestSchedule)
{
    if (currentSize == taskCount) {
	    int totalTime = EvaluateSchedule(currentSchedule, taskCount);
	    if(totalTime < bestTime)
	    {
	    	bestTime = totalTime;
	    	for (int i = 0; i < taskCount; i++) 
	    	{
                bestSchedule[i] = currentSchedule[i];
            }
	    }
	    
        for (int i = 0; i < currentSize; i++) 
        {
			currentSchedule[i].Execute();
        }
        cout << "----" << endl;
        return;
    }
	
    for (int i = 0; i < taskCount; ++i) {
        if (!used[i]) {
            used[i] = true;
            currentSchedule[currentSize] = tasks[i];
			Schedule(tasks, used, currentSchedule, taskCount, currentSize + 1, bestTime, bestSchedule);
            used[i] = false;
        }
    }
}

int EvaluateSchedule(Task* currentSchedule, int taskCount)
{
    int totalTime = 0; 
    int finishTime = 0; 

    for (int i = 0; i < taskCount; i++)
    {
        finishTime += totalTime + currentSchedule[i].GetTime();
        totalTime += currentSchedule[i].GetTime();
    }
    
    return finishTime; 
}

void PrintArray(Task* t, int size)
{
	cout << "[ ";
	for(int i = 0; i < size - 1; i++)
	{
		cout << t[i].GetTime() << ", ";
	}
	cout << t[size-1].GetTime() << " ]" << endl;
}
