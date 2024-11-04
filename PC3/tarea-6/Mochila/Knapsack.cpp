#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double BOUND(double p, double w, int k, double M, const std::vector<double>& W, const std::vector<double>& P, int n) {
    double b = p;  //bound
    double c = w;  

    for (int i = k + 1; i < n; i++) {
        c += W[i];
        if (c < M) {
            b += P[i]; 
        } else {
            b += (1 - (c - M) / W[i]) * P[i];
            return b;
        }
    }
    return b;  
}


void Knapsack(double M, int n, const std::vector<double>& W, const std::vector<double>& P, double& fw, double& fp, std::vector<int>& X) {
    std::vector<int> Y(n, 0);  
    double cw = 0, cp = 0;     
    fp = -1;                   
    int k = 0;                 

    while (true) {
        while (k < n && cw + W[k] <= M) {
            cw += W[k];
            cp += P[k];
            Y[k] = 1;
            k++;
        }
        if (k >= n) {
            if (cp > fp) {  
                fp = cp;
                fw = cw;
                X = Y;
            }
            k = n - 1;  
        } else {
            Y[k] = 0;  
        }

        while (BOUND(cp, cw, k, M, W, P, n) <= fp) {
            while (k >= 0 && Y[k] != 1) {
                k--;
            }
            if (k < 0) return;
            Y[k] = 0;
            cw -= W[k];
            cp -= P[k];
        }
        k++;
    }
}

int main()
{
	vector<int> X;
	vector<double> W = {3, 2, 1};
	vector<double> P = {5, 3, 4};
	double fw, fp;
	
	Knapsack(5, 3, W, P, fw, fp, X);
	cout << "La lista de objetos elegidos para maximizar beneficio es la siguiente:\n";
	
	for(int i = 0; i < 3; i++)
	{
		cout << X[i] << " ";
	}
	
	cout << "\nLa ganancia maximizada es: " << fp <<endl;
	return 0;
}
